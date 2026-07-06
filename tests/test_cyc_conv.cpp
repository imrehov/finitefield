#include <array>
#include <stdexcept>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../src/doctest.hpp"

#include "../include/cyc_conv.hpp"

TEST_CASE("cyclic convolution works for the example") {
    std::array<int, 4> a{1, 2, 3, 4};
    std::array<int, 4> b{5, 6, 7, 8};

    auto result = cyc_conv(a, b);

    std::array<int, 4> expected{66, 68, 66, 60};

    CHECK(result == expected);
}

TEST_CASE("cyclic convolution works with size 1") {
    std::array<int, 1> a{3};
    std::array<int, 1> b{5};

    auto result = cyc_conv(a, b);

    std::array<int, 1> expected{15};

    CHECK(result == expected);
}

TEST_CASE("cyc conv vector 1") {
    std::vector<int> a{1, 2, 3, 4};
    std::vector<int> b{5, 6, 7, 8};

    auto result = cyc_conv(a, b);

    std::vector<int> expected{
        66, // 1*5 + 2*8 + 3*7 + 4*6
        68, // 1*6 + 2*5 + 3*8 + 4*7
        66, // 1*7 + 2*6 + 3*5 + 4*8
        60  // 1*8 + 2*7 + 3*6 + 4*5
    };

    CHECK(result == expected);
}

TEST_CASE("cyc conv vector empty") {
    std::vector<int> a{0, 0, 0, 0};
    std::vector<int> b{0, 0, 0, 0};

    auto result = cyc_conv(a, b);

    std::vector<int> expected{
        0, // 1*5 + 2*8 + 3*7 + 4*6
        0, // 1*6 + 2*5 + 3*8 + 4*7
        0, // 1*7 + 2*6 + 3*5 + 4*8
        0  // 1*8 + 2*7 + 3*6 + 4*5
    };

    CHECK(result == expected);
}

TEST_CASE("cyc conv vector diff size") {
    std::vector<int> a{0, 0, 0, 0, 0};
    std::vector<int> b{0, 0, 0, 0};

    CHECK_THROWS_AS(cyc_conv(a, b), std::invalid_argument);
}

