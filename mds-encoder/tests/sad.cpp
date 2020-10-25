//
// Created by oshikuru on 21. 10. 2020..
//

#include "catch.hpp"
#include <sad.h>
#include <cstring>

TEST_CASE( "SAD algorithm is valid", "[sad]" ) {

    SECTION("sad is valid for both block filled with zero") {
        mds::blocks3x8x8 blocks1;
        mds::blocks3x8x8 blocks2;
        memset(&blocks1, 0, sizeof(blocks1));
        memset(&blocks2, 0, sizeof(blocks2));
        REQUIRE(mds::encoder::sad(blocks1, blocks2) == 0);
    }

    SECTION("SAD is valid for one block filled with UINT8_MAX and other with zero") {
        mds::blocks3x8x8 blocks1;
        mds::blocks3x8x8 blocks2;

        std::vector<int16_t> values(3 * 8 * 8, UINT8_MAX);
        memcpy(&blocks1, values.data(), sizeof(blocks1));
        memset(&blocks2, 0, sizeof(blocks2));
        REQUIRE(mds::encoder::sad(blocks1, blocks2) == 3 * 8 * 8 * UINT8_MAX);
        REQUIRE(mds::encoder::sad(blocks2, blocks1) == 3 * 8 * 8 * UINT8_MAX);
    }

    SECTION("SAD is valid for one block filled with UINT8_MAX and other two with zero") {
        mds::rgb_image ref(8, 8);
        mds::rgb_image search(8,8);

        mds::block_iterator8x8 ref_blocks[] = {
            mds::block_iterator8x8(ref),
            mds::block_iterator8x8(ref)
        };
        mds::block_iterator8x8 search_blocks[] = {
                mds::block_iterator8x8(search),
                mds::block_iterator8x8(search)
        };
        uint16_t results[2];

        std::vector<uint8_t> values(3 * 8 * 8, UINT8_MAX);
        memcpy(ref.data(), values.data(), 3 * 8 * 8);
        memset(search.data(), 0, 3 * 8 * 8);
        mds::encoder::sad(ref_blocks[0], search_blocks, results, 2);
        REQUIRE(results[0] == 3 * 8 * 8 * UINT8_MAX);
        REQUIRE(results[1] == 3 * 8 * 8 * UINT8_MAX);
        mds::encoder::sad(search_blocks[0], ref_blocks, results, 2);
        REQUIRE(results[0] == 3 * 8 * 8 * UINT8_MAX);
        REQUIRE(results[1] == 3 * 8 * 8 * UINT8_MAX);
    }
}