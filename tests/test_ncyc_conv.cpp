#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../src/doctest.hpp"

#include "../include/ncyc_conv.hpp"

#include <array>

TEST_CASE("ncyc convolution works for the example") {
    std::array<int, 4> a{1, 2, 3, 4};
    std::array<int, 4> b{5, 6, 7, 8};

    auto result = ncyc_conv(a, b);

    std::array<int, 4> expected{-56, -36, 2, 60};

    CHECK(result == expected);
}

TEST_CASE("ncyc convolution works with size 1") {
    std::array<int, 1> a{3};
    std::array<int, 1> b{5};

    auto result = ncyc_conv(a, b);

    std::array<int, 1> expected{15};

    CHECK(result == expected);
}

TEST_CASE("ncyc convolution handles simple wraparound") {
    std::array<int, 2> a{1, 2};
    std::array<int, 2> b{3, 4};

    auto result = ncyc_conv(a, b);

    // Linear result would be:
    // [3, 10, 8]
    //
    // Since n = 2, x^2 = -1
    // so 8x^2 becomes -8.
    //
    // result = [3 - 8, 10] = [-5, 10]

    std::array<int, 2> expected{-5, 10};

    CHECK(result == expected);
}

TEST_CASE("ncyc convolution works with zeros") {
    std::array<int, 3> a{1, 0, 2};
    std::array<int, 3> b{0, 3, 0};

    auto result = ncyc_conv(a, b);

    // Products:
    // 1 * 3x = 3x
    // 2x^2 * 3x = 6x^3
    //
    // Since n = 3, x^3 = -1
    // so 6x^3 = -6.
    //
    // result = -6 + 3x

    std::array<int, 3> expected{-6, 3, 0};

    CHECK(result == expected);
}

TEST_CASE("ncyc convolution with identity polynomial") {
    std::array<int, 4> a{1, 0, 0, 0};
    std::array<int, 4> b{5, 6, 7, 8};

    auto result = ncyc_conv(a, b);

    CHECK(result == b);
}