//
// Created by oshikuru on 21. 10. 2020..
//

#include "catch.hpp"
#include <block.h>
#include <cstring>


TEST_CASE( "block allocation", "[block]" ) {
    mds::block<int32_t, 8, 8> r;

    SECTION("block size is valid") {
        REQUIRE(sizeof(mds::block8x8) == 8 * 8 * sizeof(int16_t));
    }

    SECTION("can memcpy to block") {
        std::vector<int32_t> data(8 * 8);
        std::iota(data.begin(), data.end(), 0);
        memcpy(r.data(), data.data(), sizeof(int32_t) * 8 * 8);

        REQUIRE(r[{0, 0}] == 0);
        REQUIRE(r[{5, 3}] == 5 * 8 + 3);
        REQUIRE(r[{7, 0}] == 7 * 8);
        REQUIRE(r[{7, 7}] == 7 * 8 + 7);
    }

    SECTION("can add vec256 in channel") {
        std::vector<int32_t> data(8 * 8);
        std::iota(data.begin(), data.end(), 0);
        memcpy(r.data(), data.data(), sizeof(int32_t) * 8 * 8);

        r[0] += r[0];
        REQUIRE(r[{0, 1}] == 2);
        REQUIRE(r[{0, 4}] == 8);
        REQUIRE(r[{0, 7}] == 14);
    }
}