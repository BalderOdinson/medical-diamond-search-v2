//
// Created by oshikuru on 24. 10. 2020..
//


#include "catch.hpp"
#include <decoder.h>
#include <cstring>

TEST_CASE( "decoder is valid", "[decoder]" ) {

    SECTION("motion decoder is valid") {
        auto [header, referent_image] = mds::load_bitmap_image("/home/oshikuru/Git/mds/scripts/test/Cat_Eye/1.bmp");
        for (int i = 2; i <= 460; ++i)
        {
            auto motions = mds::load("/home/oshikuru/Git/mds/scripts/output/Cat_Eye/encoded/" + std::to_string(i) + ".mds");

            referent_image = mds::decoder::decode_motion_vector8x8(referent_image, motions);

            mds::write_to_bitmap_image(referent_image, header.data(), "/home/oshikuru/Git/mds/scripts/output/Cat_Eye/decoded/" + std::to_string(i) + ".bmp");
        }
    }
}