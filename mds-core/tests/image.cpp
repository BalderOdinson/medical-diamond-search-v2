//
// Created by oshikuru on 22. 10. 2020..
//

#include "catch.hpp"
#include <rgbimage.h>
#include <cstring>

TEST_CASE( "allocate image", "[rgb_image]" ) {
    SECTION("can memcpy to image") {
        mds::rgb_image img(40,40);
        std::vector<uint8_t> data(40 * 40 * 3);
        std::iota(data.begin(), data.end(), 0);

        memcpy(img.data(), data.data(), 40 * 40 * 3);

        REQUIRE(img[0] == mds::vec3uc(0, 1, 2));
        REQUIRE(img[50] == mds::vec3uc(150, 151, 152));
        REQUIRE(img[1599] == mds::vec3uc(4797, 4798, 4799));
    }
}

TEST_CASE( "can load image from file", "[rgb_image]" ) {
    SECTION("loaded image is valid") {
        auto [header, img] = mds::load_bitmap_image("/home/oshikuru/Git/mds/input/Cat_Eye/1.bmp");

        REQUIRE(img.width() == 1920);
        REQUIRE(img.height() == 1080);

        mds::write_to_bitmap_image(img, header.data(), "temp.bmp");
        auto [header1, img1] = mds::load_bitmap_image("temp.bmp");

        REQUIRE(img[0] == img1[0]);
        REQUIRE(img[20] == img1[20]);
        REQUIRE(img[15460] == img1[15460]);
        REQUIRE(img[1920 * 1080 - 1] == img1[1920 * 1080 - 1]);

        // clean up
        remove("temp.bmp");
    }
}