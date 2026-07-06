#include <array>
#include <exception>
#include <stdexcept>
#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../src/doctest.hpp"

#include "../include/lin_conv.hpp"

TEST_CASE("linear convolution works for the example") {
    std::array<int, 4> a{1, 2, 3, 4};
    std::array<int, 4> b{5, 6, 7, 8};

    auto result = lin_conv(a, b);

    std::array<int, 7> expected{5, 16, 34, 60, 61, 52, 32};

    CHECK(result == expected);
}

TEST_CASE("linear convolution works with size 1") {
    std::array<int, 1> a{3};
    std::array<int, 1> b{5};

    auto result = lin_conv(a, b);

    std::array<int, 1> expected{15};

    CHECK(result == expected);
}

TEST_CASE("linear convolution works with zeros") {
    std::array<int, 3> a{1, 0, 2};
    std::array<int, 3> b{0, 3, 0};

    auto result = lin_conv(a, b);

    std::array<int, 5> expected{0, 3, 0, 6, 0};

    CHECK(result == expected);
}

TEST_CASE("linear convolution size") {
    std::array<int, 4> a = {1,2, 3,4};
    std::array<int, 4> b = {5, 6, 7, 8};

    auto result = lin_conv(a, b);

    CHECK(result.size() == 7);
}

TEST_CASE("lin conv vector 1") {
    std::vector<int> a = { 1, 2, 3, 4};
    std::vector<int> b = { 5, 6, 7, 8};

    auto result = lin_conv(a, b);

    std::vector<int> expected{5, 16, 34, 60, 61, 52, 32};

    CHECK(result == expected);
}

TEST_CASE("lin conv vector 2 empty") {
    std::vector<int> a = { 0, 0, 0, 0};
    std::vector<int> b = { 0, 0, 0, 0};

    auto result = lin_conv(a, b);

    std::vector<int> expected{0,0,0,0,0,0,0};

    CHECK(result == expected);
}

TEST_CASE("lin conv vector exception size") {
    std::vector<int> a = { 0, 0, 0, 0, 0};
    std::vector<int> b = { 0, 0, 0, 0};

    CHECK_THROWS_AS(lin_conv(a, b), std::invalid_argument);
}