//
// Created by oshikuru on 20. 10. 2020..
//

#include "catch.hpp"
#include <vec2.h>
#include <vec3.h>
#include <vec4.h>

TEST_CASE( "vec2 initialization", "[vec2]" ) {
    mds::vec2uc v1(2);
    REQUIRE( v1.r == 2 );
    REQUIRE( v1.g == 2 );

    v1 = { 1, 2 };
    REQUIRE( v1.r == 1 );
    REQUIRE( v1.g == 2 );

    uint8_t v[] = { 4, 5 };
    mds::vec2uc& v2 = mds::to_vec2(v);
    mds::vec2uc* v3 = mds::to_vec2(v);

    REQUIRE( v2.r == 4 );
    REQUIRE( v2.g == 5 );
    REQUIRE( v3->r == 4 );
    REQUIRE( v3->g == 5 );
}

TEST_CASE( "vec2 operations", "[vec2]" ) {
    mds::vec2uc v1(2);
    mds::vec2uc v2{ 1, 2 };
    mds::vec2ul v3 { 2 };

    REQUIRE(v1 == v1);
    REQUIRE(v1 != v2);
    REQUIRE(v2 == v2);
    REQUIRE(v2 != v1);

    REQUIRE( mds::vec2uc{v1 + v2} == mds::vec2uc{ 3, 4 } );
    REQUIRE( mds::vec2uc{v1 - v2} == mds::vec2uc{ 1, 0 } );
    REQUIRE( mds::vec2uc{v1 * v2} == mds::vec2uc{ 2, 4 } );
    REQUIRE( mds::vec2uc{v1 / v2} == mds::vec2uc{ 2, 1 } );
    REQUIRE( v3 + mds::vec2c{ -1, -1 } == mds::vec2ul{ 1, 1 } );
}

TEST_CASE( "vec2 math", "[vec2]" ) {
    mds::vec2c v2{ 1, -2 };

    REQUIRE(mds::abs(v2) == mds::vec2c{1, 2});
}

TEST_CASE( "vec3 initialization", "[vec3]" ) {
    mds::vec3uc v1(2);
    REQUIRE( v1.r == 2 );
    REQUIRE( v1.g == 2 );
    REQUIRE( v1.b == 2 );

    v1 = { 1, 2, 3 };
    REQUIRE( v1.r == 1 );
    REQUIRE( v1.g == 2 );
    REQUIRE( v1.b == 3 );

    uint8_t v[] = { 4, 5, 6 };
    mds::vec3uc& v2 = mds::to_vec3(v);
    mds::vec3uc* v3 = mds::to_vec3(v);

    REQUIRE( v2.r == 4 );
    REQUIRE( v2.g == 5 );
    REQUIRE( v2.b == 6 );
    REQUIRE( v3->r == 4 );
    REQUIRE( v3->g == 5 );
    REQUIRE( v3->b == 6 );
}

TEST_CASE( "vec3 operations", "[vec3]" ) {
    mds::vec3uc v1(2);
    mds::vec3uc v2{ 1, 2, 3 };

    REQUIRE(v1 == v1);
    REQUIRE(v1 != v2);
    REQUIRE(v2 == v2);
    REQUIRE(v2 != v1);

    REQUIRE( mds::vec3uc{v1 + v2} == mds::vec3uc{ 3, 4, 5 } );
    REQUIRE( mds::vec3uc{v1 - v2} == mds::vec3uc{ 1, 0, uint8_t(-1) } );
    REQUIRE( mds::vec3uc{v1 * v2} == mds::vec3uc{ 2, 4, 6 } );
    REQUIRE( mds::vec3uc{v1 / v2} == mds::vec3uc{ 2, 1, 0 } );
}

TEST_CASE( "vec3 math", "[vec3]" ) {
    mds::vec3c v2{ 1, -2, 3 };

    REQUIRE(mds::abs(v2) == mds::vec3c{1, 2, 3});
}

TEST_CASE( "vec4 initialization", "[vec4]" ) {
    mds::vec4uc v1(2);
    REQUIRE( v1.r == 2 );
    REQUIRE( v1.g == 2 );
    REQUIRE( v1.b == 2 );
    REQUIRE( v1.a == 2 );

    v1 = { 1, 2, 3, 4 };
    REQUIRE( v1.r == 1 );
    REQUIRE( v1.g == 2 );
    REQUIRE( v1.b == 3 );
    REQUIRE( v1.a == 4 );

    v1 = mds::vec3uc{ 1, 2, 3 };
    REQUIRE( v1.r == 1 );
    REQUIRE( v1.g == 2 );
    REQUIRE( v1.b == 3 );
    REQUIRE( v1.a == 0 );

    v1 = {mds::vec3uc{ 1, 2, 3 }, 4};
    REQUIRE( v1.r == 1 );
    REQUIRE( v1.g == 2 );
    REQUIRE( v1.b == 3 );
    REQUIRE( v1.a == 4 );

    uint8_t v[] = { 4, 5, 6, 7 };
    mds::vec4uc& v2 = mds::to_vec4(v);
    mds::vec4uc* v3 = mds::to_vec4(v);

    REQUIRE( v2.r == 4 );
    REQUIRE( v2.g == 5 );
    REQUIRE( v2.b == 6 );
    REQUIRE( v2.a == 7 );
    REQUIRE( v3->r == 4 );
    REQUIRE( v3->g == 5 );
    REQUIRE( v3->b == 6 );
    REQUIRE( v3->a == 7 );
}

TEST_CASE( "vec4 operations", "[vec4]" ) {
    mds::vec4uc v1(2);
    mds::vec4uc v2{ 1, 2, 3, 4 };

    REQUIRE(v1 == v1);
    REQUIRE(v1 != v2);
    REQUIRE(v2 == v2);
    REQUIRE(v2 != v1);

    REQUIRE( mds::vec4uc{v1 + v2} == mds::vec4uc{ 3, 4, 5, 6 } );
    REQUIRE( mds::vec4uc{v1 - v2} == mds::vec4uc{ 1, 0, uint8_t(-1), uint8_t(-2) } );
    REQUIRE( mds::vec4uc{v1 * v2} == mds::vec4uc{ 2, 4, 6, 8 } );
    REQUIRE( mds::vec4uc{v1 / v2} == mds::vec4uc{ 2, 1, 0, 0 } );
}

TEST_CASE( "vec4 math", "[vec4]" ) {
    mds::vec4c v2{ 1, -2, 3, -4 };

    REQUIRE(mds::abs(v2) == mds::vec4c{1, 2, 3, 4});
}

TEST_CASE( "vec swizzle", "[vec]" ) {
    mds::vec3c v1{1, -2, 3};
    mds::vec4c v2{ 1, -2, 3, -4 };

    mds::vec3c v3 = v1.xxx;
    mds::vec4c v4 = v2.bgra;
    mds::vec3c v5 = mds::vec3c(v2.zwx).zxy;

    mds::vec2i v6 = {3, 2};

    REQUIRE(v3 == mds::vec3c{1});
    REQUIRE(v4 == mds::vec4c{3, -2, 1, -4});
    REQUIRE(v5 == mds::vec3c{1, 3, -4});
    REQUIRE((v6 = v6.yx) == mds::vec2i{2, 3});
}