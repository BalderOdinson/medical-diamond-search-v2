//
// Created by oshikuru on 21. 10. 2020..
//

#include "catch.hpp"
#include <vector.h>

TEST_CASE("vec256 allocation", "[vec256]")
{
    mds::vec256<int32_t> r({1, 2, 3, 4, 5, 6, 7, 8});

    REQUIRE(alignof(r) == 32);
    REQUIRE(sizeof(r) == 32);
    REQUIRE(r[0] == 1);
    REQUIRE(r[1] == 2);
    REQUIRE(r[2] == 3);
    REQUIRE(r[3] == 4);
    REQUIRE(r[4] == 5);
    REQUIRE(r[5] == 6);
    REQUIRE(r[6] == 7);
    REQUIRE(r[7] == 8);
}

TEST_CASE("vec256 construction", "[vec256]")
{
    mds::vec256<uint32_t> v1({1, 2, 3, 4, 5, 6, 7, 8});
    mds::vec256<int32_t> v2 = v1;

    REQUIRE(v2[0] == 1);
    REQUIRE(v2[1] == 2);
    REQUIRE(v2[2] == 3);
    REQUIRE(v2[3] == 4);
    REQUIRE(v2[4] == 5);
    REQUIRE(v2[5] == 6);
    REQUIRE(v2[6] == 7);
    REQUIRE(v2[7] == 8);
}

TEST_CASE("vec256 operations", "[vec256]")
{
    mds::vec256<uint32_t> v1({1, 2, 3, 4, 5, 6, 7, 8});
    mds::vec256<int32_t> v2(2);

    SECTION("vec256 result is valid type") {
        mds::vec256<int16_t> vt1;
        mds::vec256<uint16_t> vt2;

        REQUIRE(std::is_same_v<decltype(vt1 + vt2), mds::vec256<uint16_t>>);
        REQUIRE(std::is_same_v<decltype(vt1 + vt1), mds::vec256<int16_t>>);
    }

    SECTION("vec256 addition is valid")
    {
        auto v3 = v1 + v2;
        REQUIRE(std::is_same_v<decltype(v3), mds::vec256<decltype(uint32_t{} + int32_t{})>>);

        for (int i = 0; i < 8; ++i)
            REQUIRE(v3[i] == (i + 1) + 2u);
    }

    SECTION("vec256 subtraction is valid")
    {
        auto v3 = v1 - v2;
        REQUIRE(std::is_same_v<decltype(v3), mds::vec256<decltype(uint32_t{} - int32_t{})>>);

        for (int i = 0; i < 8; ++i)
            REQUIRE(v3[i] == (i + 1) - 2u);
    }

    SECTION("vec256 multiplication is valid")
    {
        auto v3 = v1 * v2;
        REQUIRE(std::is_same_v<decltype(v3), mds::vec256<decltype(uint32_t{} * int32_t{})>>);

        for (int i = 0; i < 8; ++i)
            REQUIRE(v3[i] == (i + 1) * 2u);
    }

    SECTION("vec256 divide is valid")
    {
        auto v3 = v1 / v2;
        REQUIRE(std::is_same_v<decltype(v3), mds::vec256<decltype(uint32_t{} / int32_t{})>>);

        for (int i = 0; i < 8; ++i)
            REQUIRE(v3[i] == (i + 1) / 2u);
    }
}
