#include <array>
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
