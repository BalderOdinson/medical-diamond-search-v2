//
// Created by oshikuru on 23. 10. 2020..
//

#include "catch.hpp"
#include <rgbimage.h>
#include <blockiterator.h>
#include <cstring>

TEST_CASE( "block_iterator is valid", "[block_iterator]" ) {
    struct {
        int current{0};
        int operator()() {return (current++) / 3;}
    } image_generator;
    mds::rgb_image img(40,40);
    std::vector<uint8_t> data(40 * 40 * 3);
    std::generate(data.begin(), data.end(), image_generator);
    memcpy(img.data(), data.data(), 40 * 40 * 3);

    SECTION("dereferenced block iterator is valid") {
        const mds::block_iterator8x8 iter(img);

        auto blocks = *iter;

        REQUIRE(blocks.r[{0, 0}] == 0);
        REQUIRE(blocks.g[{1, 0}] == 40);
        REQUIRE(blocks.b[{4, 4}] == uint8_t(40 * 4 + 4));
        REQUIRE(blocks.r[{7, 7}] == uint8_t(40 * 7 + 7));
    }
    SECTION("block iterator comparison is valid") {
        mds::block_iterator8x8 iter1(img);
        mds::block_iterator8x8 iter2(img);
        mds::block_iterator8x8 iter3(img, 5);
        mds::block_iterator8x8 iter4(img, 5);

        REQUIRE(iter1 == iter2);
        REQUIRE(iter3 == iter4);
        REQUIRE(iter1 < iter3);
        REQUIRE(iter4 > iter2);
        REQUIRE(iter1 <= iter2);
        REQUIRE(iter3 >= iter4);
    }

    SECTION("block iterator arithmetic is valid") {
        mds::block_iterator8x8 iter1(img);
        auto iter2 = iter1 + 6;
        auto iter3 = iter2 - 6;
        auto iter4 = iter2 - mds::vec2i{1, 1};
        auto iter5 = iter2 + 6 - mds::vec2i{1, 1};
        auto iter6 = iter2 - mds::vec2i{1, 1} + 6;

        REQUIRE(iter1 == iter3);
        REQUIRE(iter5 == iter6);
        REQUIRE(iter2 - iter4 == mds::vec2i{1, 1});

        auto blocks = *iter2;

        REQUIRE(blocks.r[{0, 0}] == uint8_t(40 * (8 + 0) + 8 + 0));
        REQUIRE(blocks.g[{1, 0}] == uint8_t(40 * (8 + 1) + 8 + 0));
        REQUIRE(blocks.b[{4, 4}] == uint8_t(40 * (8 + 4) + 8 + 4));
        REQUIRE(blocks.r[{7, 7}] == uint8_t(40 * (8 + 7) + 8 + 7));

        REQUIRE(iter4->r[{0, 0}] == uint8_t(40 * (7 + 0) + 7 + 0));
        REQUIRE(iter4->g[{1, 0}] == uint8_t(40 * (7 + 1) + 7 + 0));
        REQUIRE(iter4->b[{4, 4}] == uint8_t(40 * (7 + 4) + 7 + 4));
        REQUIRE(iter4->r[{7, 7}] == uint8_t(40 * (7 + 7) + 7 + 7));
    }

    SECTION("block iterator valid check is valid") {
        mds::block_iterator8x8 valid_iter(img);
        auto invalid_iter = valid_iter + 26;

        REQUIRE(valid_iter);
        REQUIRE(!invalid_iter);
    }
}