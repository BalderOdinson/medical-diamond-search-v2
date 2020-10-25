//
// Created by oshikuru on 22. 10. 2020..
//

#ifndef MDS_MDS_H
#define MDS_MDS_H

#include <mds-core/motionvector.h>
#include <mds-core/blockiterator.h>
#include <array>
#include "sad.h"

namespace mds::encoder
{
    constexpr size_t CenterBlockIndex = 0;
    constexpr uint8_t SmallDiamondSize = 5;
    constexpr uint8_t LargeDiamondSize = 9;
    constexpr uint8_t MdsIterations = 3;
    const vec2c Up = {0, -1};
    const vec2c Down = {0, 1};
    const vec2c Left = {-1, 0};
    const vec2c Right = {1, 0};
    const vec2c UpX2 = {0, -2};
    const vec2c DownX2 = {0, 2};
    const vec2c LeftX2 = {-2, 0};
    const vec2c RightX2 = {2, 0};
    const vec2c UpRight = {1, -1};
    const vec2c UpLeft = {-1, -1};
    const vec2c DownRight = {1, 1};
    const vec2c DownLeft = {-1, 1};

    template<uint8_t BlockWidth = 8, uint8_t BlockHeight = 8>
    void large_diamond(block_iterator<BlockWidth, BlockHeight> *search_window,
                       block_iterator<BlockWidth, BlockHeight> &&center, size_t &size)
    {
        size = 1;
        search_window[CenterBlockIndex] = std::move(center);
        if (auto up = center + UpX2) search_window[size++] = up;
        if (auto upright = center + UpRight) search_window[size++] = upright;
        if (auto right = center + RightX2) search_window[size++] = right;
        if (auto downright = center + DownRight) search_window[size++] = downright;
        if (auto down = center + DownX2) search_window[size++] = down;
        if (auto downleft = center + DownLeft) search_window[size++] = downleft;
        if (auto left = center + LeftX2) search_window[size++] = left;
        if (auto upleft = center + UpLeft) search_window[size++] = upleft;
    }

    template<uint8_t BlockWidth = 8, uint8_t BlockHeight = 8>
    void small_diamond(block_iterator<BlockWidth, BlockHeight> *search_window,
                       block_iterator<BlockWidth, BlockHeight> &&center, size_t &size)
    {
        size = 1;
        search_window[CenterBlockIndex] = std::move(center);
        if (auto up = center + Up) search_window[size++] = up;
        if (auto right = center + Right) search_window[size++] = right;
        if (auto down = center + Down) search_window[size++] = down;
        if (auto left = center + Left) search_window[size++] = left;
    }

    template<uint8_t BlockWidth = 8, uint8_t BlockHeight = 8>
    std::pair<vec2i, vec2us> find_mbd(
            const block_iterator<BlockWidth, BlockHeight> &referent_block,
            const block_iterator<BlockWidth, BlockHeight> *search_blocks,
            size_t search_blocks_count)
    {
        vec2i min = {-1, -1};

        uint16_t values[LargeDiamondSize] = {std::numeric_limits<uint16_t>::max()};

        sad(referent_block, search_blocks, values, search_blocks_count);

        for (size_t i = 0; i < search_blocks_count; ++i)
        {
            if (min.x < 0 || values[i] <= values[min.x]) (min = min.yx).x = i;
            else if (min.y < 0 || values[i] < values[min.y]) min.y = i;
        }

        return {min, {values[min.x], values[min.y]}};
    }

    template<typename T, uint8_t BlockWidth = 8, uint8_t BlockHeight = 8>
    vec2c mds_per_block(const block_iterator<BlockWidth, BlockHeight> &referent_block,
                        block_iterator<BlockWidth, BlockHeight> search_block,
                        T &threshold)
    {
        float t = fminf(threshold, 100.f) / 100.f;
        size_t search_window_size = 0;
        block_iterator<BlockWidth, BlockHeight> search_window[LargeDiamondSize];
        const auto initial_search_block = search_block;

        // The initial search pattern is centered at the origin of the search window, and block distortion is calculated with SAD algorithm
        // for 9 checking points, one center point and eight points that surround the center, composing a diamond shape
        // (at points with absolute Manhattan distance equals 2). Initial threshold is T=10%.
        large_diamond(search_window, std::move(search_block), search_window_size);
        auto[mbd_idx, mbd_value] = find_mbd(referent_block, search_window, search_window_size);

        for (uint8_t i = 0; i < MdsIterations; ++i)
        {
            // Step 1:
            // If (minimum block distortion (MBD) point is more than T lower than second minimum AND is located at the center position):
            if (mbd_idx.x == CenterBlockIndex && mbd_value.x / float(mbd_value.y) < t)
            {
                // find minimum block distortion at points with absolute Manhattan distance equals to 0 or 1 from the current center
                small_diamond(search_window, std::move(search_window[CenterBlockIndex]), search_window_size);
                std::tie(mbd_idx, mbd_value) = find_mbd(referent_block, search_window, search_window_size);
                // MBD point found in this step is the final solution of the motion vector which points to the best matching block
                return search_window[mbd_idx.x] - initial_search_block;
            }

            // Step 2:
            // If (MBD is more than T lower than second minimum but is NOT located at the center position):
            if (mbd_value.x / float(mbd_value.y) <= t)
            {
                auto flipped_search_center =
                        search_window[mbd_idx.x] + (search_window[mbd_idx.x] - search_window[CenterBlockIndex]);
                // block with new MBD becomes new center point
                if (flipped_search_center)
                {
                    search_window[CenterBlockIndex] = std::move(search_window[mbd_idx.x]);
                    search_window[CenterBlockIndex + 1] = std::move(flipped_search_center);
                    search_window_size = 2;

                    mbd_idx.x = CenterBlockIndex;
                    // find MBD either in that point or in the point which is flipped position of previous center
                    auto flipped_mbd_value = sad(*referent_block, *search_window[CenterBlockIndex + 1]);
                    if (flipped_mbd_value < mbd_value.x)
                    {
                        (mbd_idx = mbd_idx.yx).x = CenterBlockIndex + 1;
                        (mbd_value = mbd_value.yx).x = flipped_mbd_value;
                    }
                    else
                    {
                        mbd_idx.y = CenterBlockIndex + 1;
                        mbd_value.y = flipped_mbd_value;
                    }
                }
            }
            // If (MBD point is less than T lower than second minimum):
            if (mbd_value.x / float(mbd_value.y) > t)
            {
                // consider first two minimums and calculate BD for points that are on flipped positions of previous center regarding this minimums
                auto first_min_block = std::move(search_window[mbd_idx.x]);
                auto second_min_block = std::move(search_window[mbd_idx.y]);
                auto flipped_first_min_block = first_min_block + (first_min_block - search_window[CenterBlockIndex]);
                auto flipped_second_min_block = second_min_block + (second_min_block - search_window[CenterBlockIndex]);
                search_window_size = 1;

                if (mbd_idx.x != CenterBlockIndex && flipped_first_min_block)
                {
                    search_window[search_window_size] = std::move(first_min_block);
                    search_window[search_window_size + 1] = std::move(flipped_first_min_block);
                    mbd_idx.x = search_window_size;
                    search_window_size += 2;
                    auto new_value = sad(*referent_block, *search_window[search_window_size - 1]);
                    auto new_idx = search_window_size - 1;

                    if (new_value < mbd_value.x)
                    {
                        (mbd_value = mbd_value.yx).x = new_value;
                        (mbd_idx = mbd_idx.yx).x = new_idx;
                    }
                    else if (new_value < mbd_value.y)
                    {
                        mbd_value.y = new_value;
                        mbd_idx.y = new_idx;
                    }
                }

                if (mbd_idx.y != CenterBlockIndex && flipped_second_min_block)
                {
                    search_window[search_window_size] = std::move(second_min_block);
                    search_window[search_window_size + 1] = std::move(flipped_second_min_block);
                    mbd_idx.y = search_window_size;
                    search_window_size += 2;
                    auto new_value = sad(*referent_block, *search_window[search_window_size - 1]);
                    auto new_idx = search_window_size - 1;

                    if (new_value < mbd_value.x)
                    {
                        (mbd_value = mbd_value.yx).x = new_value;
                        (mbd_idx = mbd_idx.yx).x = new_idx;
                    }
                    else if (new_value < mbd_value.y)
                    {
                        mbd_value.y = new_value;
                        mbd_idx.y = new_idx;
                    }
                }
            }
        }

        // Raise threshold for 5%
        if (t < 1.f) threshold += 5;
        // MBD point found in this step is the final solution of the motion vector which points to the best matching block
        return search_window[mbd_idx.x] - initial_search_block;
    }

    std::vector<motion_vector> mds_full8x8(const rgb_image &referent_img, const rgb_image &search_img);
    std::vector<motion_vector> mds_full16x16(const rgb_image &referent_img, const rgb_image &search_img);
}


#endif //MDS_MDS_H
