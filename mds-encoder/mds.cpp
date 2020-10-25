//
// Created by oshikuru on 22. 10. 2020..
//

#include "mds.h"

constexpr size_t BlockWidth8x8 = 8;
constexpr size_t BlockWidth16x16 = 16;
constexpr size_t NumOfPixels8x8 = 64;
constexpr size_t NumOfPixels16x16 = 256;

#if defined(_OPENMP)
#include <atomic>
using threshold_t = std::atomic_uint8_t;
using motion_size_t = std::atomic_size_t;
#else
using threshold_t = uint8_t;
using motion_size_t = size_t;
#endif

std::vector<mds::motion_vector>
mds::encoder::mds_full8x8(const mds::rgb_image &referent_img, const mds::rgb_image &search_img)
{
    size_t blocks_count = (referent_img.width() * referent_img.height()) / NumOfPixels8x8;
    size_t block_width = referent_img.width() / BlockWidth8x8;

    threshold_t threshold = 10;
    motion_size_t motions_count = 0;
    mds::motion_vector motions[blocks_count];

#pragma omp parallel for
    for (size_t i = 0; i < blocks_count; ++i)
    {
        block_iterator8x8 referent_block(referent_img, i);
        block_iterator8x8 search_block(search_img, i);
        auto motion = mds_per_block(referent_block, search_block, threshold);
        if (motion != vec2c{0})
        {
            motions[motions_count++] = {
                .block = {uint8_t(i % block_width), uint8_t(i / block_width) },
                .direction = motion
            };
        }
    }

    return std::vector<motion_vector>(motions, motions + motions_count);
}

std::vector<mds::motion_vector>
mds::encoder::mds_full16x16(const mds::rgb_image &referent_img, const mds::rgb_image &search_img)
{
    size_t blocks_count = (referent_img.width() * referent_img.height()) / NumOfPixels16x16;
    size_t block_width = referent_img.width() / BlockWidth16x16;

    uint8_t threshold = 10;
    size_t motions_count = 0;
    mds::motion_vector motions[blocks_count];

#pragma omp parallel for
    for (size_t i = 0; i < blocks_count; ++i)
    {
        block_iterator16x16 referent_block(referent_img, i);
        block_iterator16x16 search_block(search_img, i);
        auto motion = mds_per_block(referent_block, search_block, threshold);
        if (motion != vec2c{0})
        {
            motions[motions_count++] = {
                    .block = {uint8_t(i % block_width), uint8_t(i / block_width) },
                    .direction = motion
            };
        }
    }

    return std::vector<motion_vector>(motions, motions + motions_count);
}
