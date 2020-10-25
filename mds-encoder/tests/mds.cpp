//
// Created by oshikuru on 24. 10. 2020..
//

#include "catch.hpp"
#include <sad.h>
#include <cstring>
#include <mds-encoder/mds.h>
#include <chrono>

TEST_CASE( "find MBD algorithm is valid", "[mds]" ) {
    std::vector<uint8_t> referent_image_data = {
            1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
            2, 9, 2, 9, 2, 9, 2, 9, 2, 9,
            3, 8, 3, 8, 3, 8, 3, 8, 3, 8,
            4, 7, 4, 7, 4, 7, 4, 7, 4, 7,
            5, 6, 5, 6, 5, 6, 5, 6, 5, 6,
            6, 5, 6, 5, 6, 5, 6, 5, 6, 5,
            7, 4, 7, 4, 7, 4, 7, 4, 7, 4,
            8, 3, 8, 3, 8, 3, 8, 3, 8, 3,
            9, 2, 9, 2, 9, 2, 9, 2, 9, 2,
            0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
    };

    std::vector<uint8_t> search_image_data = {
            8, 2, 9, 2, 9, 2, 9, 2, 9, 2,
            8, 3, 8, 3, 8, 3, 8, 3, 8, 3,
            7, 4, 7, 4, 7, 4, 7, 4, 7, 4,
            6, 5, 6, 5, 6, 5, 6, 5, 6, 5,
            5, 6, 5, 6, 5, 6, 5, 6, 5, 6,
            4, 7, 4, 7, 4, 7, 4, 7, 4, 7,
            3, 8, 3, 8, 3, 8, 3, 8, 3, 8,
            2, 9, 2, 9, 2, 9, 2, 9, 2, 9,
            1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
            0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
    };

    std::vector<uint8_t> referent_image_data_rgb(10 * 10 * 3);
    std::vector<uint8_t> search_image_data_rgb(10 * 10 * 3);

    struct gen{
        gen(std::vector<uint8_t> d) : d(std::move(d)) {}
        std::vector<uint8_t> d;
        size_t current{};

        int operator()() {return d[(current++) / 3];}
    };

    std::generate(referent_image_data_rgb.begin(), referent_image_data_rgb.end(), gen(referent_image_data));
    std::generate(search_image_data_rgb.begin(), search_image_data_rgb.end(), gen(search_image_data));

    mds::rgb_image referent_img(10, 10);
    mds::rgb_image search_img(10, 10);

    memcpy(referent_img.data(), referent_image_data_rgb.data(), 10 * 10 * 3);
    memcpy(search_img.data(), search_image_data_rgb.data(), 10 * 10 * 3);

    auto referent_block = mds::block_iterator8x8(referent_img, mds::vec2i{ 1, 1 });

    mds::block_iterator8x8 search_window[] = {
            mds::block_iterator8x8(referent_block, search_img),
            mds::block_iterator8x8(referent_block, search_img) + mds::encoder::Up,
            mds::block_iterator8x8(referent_block, search_img) + mds::encoder::UpRight,
            mds::block_iterator8x8(referent_block, search_img) + mds::encoder::Right,
            mds::block_iterator8x8(referent_block, search_img) + mds::encoder::DownRight,
            mds::block_iterator8x8(referent_block, search_img) + mds::encoder::Down,
            mds::block_iterator8x8(referent_block, search_img) + mds::encoder::DownLeft,
            mds::block_iterator8x8(referent_block, search_img) + mds::encoder::Left,
            mds::block_iterator8x8(referent_block, search_img) + mds::encoder::UpLeft,
    };

    auto [mbd_idx, mbd_value] = mds::encoder::find_mbd(referent_block, search_window, 9);

    REQUIRE(mbd_idx.x == 2);
    REQUIRE(mbd_idx.y == 8);
    REQUIRE(mbd_value.x == 0);
    REQUIRE(mbd_value.y == 3);
}

TEST_CASE("mds block algorithm is valid", "[mds]") {
    std::vector<uint8_t> referent_image_data = {
            63, 110,  95, 133,  18, 145,  79, 203,  86,  68, 216,  83, 110, 238, 227, 187,
            248, 194,  52, 179,  37,  95, 118, 182,  79, 186,  47, 108, 114, 181, 231,  30,
            90, 200,  94, 136,   2, 110, 193, 253, 201,   1,  21,  98,  45, 208, 128, 136,
            223, 197, 134, 188, 189, 105, 247,  73,  93,   5, 237,   9, 217, 141,  79,  46,
            131, 130, 200,  80, 174, 178, 116, 252,  44, 197,  90, 206, 156, 140, 117, 194,
            182, 202, 199,  67,  81, 165, 190, 154,  65, 133,  80,  18, 232, 98,  66,  79,
            99, 228, 115, 153,  25,  46, 204, 232, 197, 146, 185,  45,  24, 37, 145, 111,
            31, 248, 172, 129, 199, 139, 128, 166,  99,  16, 141,  59, 115, 198,  22, 123,
            40, 122, 237, 172, 135, 242, 233, 223, 216, 221, 187, 132, 157, 215, 151, 178,
            43,  12,  44,  69,  61, 155, 109,  46,  78, 216, 110, 104,  90, 158, 162,  32,
            17, 146, 177, 133,  48,  24, 184,  70,  47, 185,  88, 141,  58, 183, 158,  26,
            116,  71, 143, 203, 144,  49, 135, 242,  72,  40,  65, 187,  87, 4,  87, 143,
            12, 113,  99,  13,   7, 205, 125, 231, 139, 241, 253, 233,  85, 103,  14, 103,
            134,  12, 213, 157,  73,  45,  70, 155,  68, 178, 216,  56,  45, 114,  18,  80,
            13, 116,  70, 147,  88, 235,   1, 223, 250, 173, 195,   5,  22, 171,  55,  29,
            96, 230, 161, 254, 132, 202, 191, 160, 182, 175, 188, 192,  91, 143, 136, 148
    };

    std::vector<uint8_t> search_image_data = {
            193,  42,  52,  87,   8, 232,  59, 155,  51, 109,  68, 151,  50, 72,  41, 114,
            182, 171, 146, 224,   3, 206, 134, 161,   5,  21, 172, 238,  15, 35,  72, 251,
            119, 222, 183, 181,  83,  55, 215, 210, 227,  98,  82,  24,  74, 26, 248, 132,
            112, 123, 240,  34,  58, 229, 185,  72, 136, 239, 144, 156, 144, 98, 117,  47,
            109,  65,  47, 253, 225,  89, 185,   1,  59,  20,  78, 209, 197, 116, 195,  66,
            157, 118,  62, 190,  79, 107,  55, 252, 157, 253,  72, 108, 235, 112, 204,  16,
            230,  98,  65, 105, 187,  69, 174, 178, 116, 252,  44, 197,  90, 206, 110,  81,
            95, 142,  58, 162, 193, 117,  81, 165, 190, 154,  65, 133,  80, 18, 144,   3,
            93, 103, 101,  45, 119, 115,  25,  46, 204, 232, 197, 146, 185, 45, 239,  70,
            32,  18, 131, 173,   5,  74, 199, 139, 128, 166,  99,  16, 141, 59, 133, 185,
            81, 207, 222,  78, 213,  45, 135, 242, 233, 223, 216, 221, 187, 132,  19,  20,
            169, 254, 117, 113, 229,  29,  61, 155, 109,  46,  78, 216, 110, 104, 235,  29,
            82,  90,   3,  78, 113, 236,  48,  24, 184,  70,  47, 185,  88, 141,  62, 138,
            136, 172, 144, 144, 173, 234, 144,  49, 135, 242,  72,  40,  65, 187,  44, 216,
            44, 100, 158, 188, 120, 128, 106, 148, 126,  84,  84, 171,  31, 181,  66,  86,
            231, 244, 112,  51, 164,  26,  93, 139,  71, 121, 112,  86, 153, 44,   9, 170
    };

    std::vector<uint8_t> referent_image_data_rgb(16 * 16 * 3);
    std::vector<uint8_t> search_image_data_rgb(16 * 16 * 3);

    struct gen{
        gen(std::vector<uint8_t> d) : d(std::move(d)) {}
        std::vector<uint8_t> d;
        size_t current{};

        int operator()() {return d[(current++) / 3];}
    };

    std::generate(referent_image_data_rgb.begin(), referent_image_data_rgb.end(), gen(referent_image_data));
    std::generate(search_image_data_rgb.begin(), search_image_data_rgb.end(), gen(search_image_data));

    mds::rgb_image referent_img(16, 16);
    mds::rgb_image search_img(16, 16);

    memcpy(referent_img.data(), referent_image_data_rgb.data(), 16 * 16 * 3);
    memcpy(search_img.data(), search_image_data_rgb.data(), 16 * 16 * 3);

    auto referent_block = mds::block_iterator8x8(referent_img, mds::vec2i{ 4, 4 });
    auto search_block = mds::block_iterator8x8(search_img, mds::vec2i{ 4, 4 });

    uint8_t threshold = 10;

    auto motion_vec = mds::encoder::mds_per_block(referent_block, search_block, threshold);

    REQUIRE(motion_vec == mds::vec2c{2, 2});
}

TEST_CASE("mds full is valid", "[mds]") {

}