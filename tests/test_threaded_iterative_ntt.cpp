#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../src/doctest.hpp"

#include "../include/fast_iterative_ntt.hpp"
#include "../include/threaded_iterative_ntt.hpp"


TEST_CASE("threaded iterative NTT works for size 4 modulo 17") {
    std::vector<mod_t<17>> a{
        mod_t<17>{1},
        mod_t<17>{2},
        mod_t<17>{3},
        mod_t<17>{4}
    };

    threaded_iterative_ntt<4, 17>(a);

    std::vector<mod_t<17>> expected{
        mod_t<17>{10},
        mod_t<17>{7},
        mod_t<17>{15},
        mod_t<17>{6}
    };

    CHECK(a == expected);
}


TEST_CASE("threaded iterative NTT works for size 8 modulo 17") {
    std::vector<mod_t<17>> a{
        mod_t<17>{1},
        mod_t<17>{2},
        mod_t<17>{3},
        mod_t<17>{4},
        mod_t<17>{5},
        mod_t<17>{6},
        mod_t<17>{7},
        mod_t<17>{8}
    };

    // 2 is a primitive 8th root modulo 17
    threaded_iterative_ntt<2, 17>(a);

    std::vector<mod_t<17>> expected{
        mod_t<17>{2},
        mod_t<17>{8},
        mod_t<17>{14},
        mod_t<17>{6},
        mod_t<17>{13},
        mod_t<17>{3},
        mod_t<17>{12},
        mod_t<17>{1}
    };

    CHECK(a == expected);
}


TEST_CASE("threaded iterative NTT of all ones collapses to first coefficient") {
    std::vector<mod_t<17>> a{
        mod_t<17>{1},
        mod_t<17>{1},
        mod_t<17>{1},
        mod_t<17>{1},
        mod_t<17>{1},
        mod_t<17>{1},
        mod_t<17>{1},
        mod_t<17>{1}
    };

    threaded_iterative_ntt<2, 17>(a);

    std::vector<mod_t<17>> expected{
        mod_t<17>{8},
        mod_t<17>{0},
        mod_t<17>{0},
        mod_t<17>{0},
        mod_t<17>{0},
        mod_t<17>{0},
        mod_t<17>{0},
        mod_t<17>{0}
    };

    CHECK(a == expected);
}


TEST_CASE("threaded iterative NTT matches single threaded iterative NTT") {
    std::vector<mod_t<17>> input{
        mod_t<17>{1},
        mod_t<17>{5},
        mod_t<17>{3},
        mod_t<17>{9},
        mod_t<17>{2},
        mod_t<17>{7},
        mod_t<17>{4},
        mod_t<17>{6}
    };

    auto single_threaded = input;
    auto multi_threaded = input;

    fast_iterative_ntt<2, 17>(single_threaded);
    threaded_iterative_ntt<2, 17>(multi_threaded);

    CHECK(multi_threaded == single_threaded);
}


TEST_CASE("threaded iterative NTT matches single threaded for size 16") {
    std::vector<mod_t<17>> input{
        mod_t<17>{1},
        mod_t<17>{2},
        mod_t<17>{3},
        mod_t<17>{4},
        mod_t<17>{5},
        mod_t<17>{6},
        mod_t<17>{7},
        mod_t<17>{8},
        mod_t<17>{9},
        mod_t<17>{10},
        mod_t<17>{11},
        mod_t<17>{12},
        mod_t<17>{13},
        mod_t<17>{14},
        mod_t<17>{15},
        mod_t<17>{16}
    };

    auto single_threaded = input;
    auto multi_threaded = input;

    // 3 is a primitive 16th root modulo 17
    fast_iterative_ntt<3, 17>(single_threaded);
    threaded_iterative_ntt<3, 17>(multi_threaded);

    CHECK(multi_threaded == single_threaded);
}

TEST_CASE("threaded iterative NTT gives stable result across repeated runs") {
    std::vector<mod_t<17>> input{
        mod_t<17>{1},
        mod_t<17>{2},
        mod_t<17>{3},
        mod_t<17>{4},
        mod_t<17>{5},
        mod_t<17>{6},
        mod_t<17>{7},
        mod_t<17>{8},
        mod_t<17>{9},
        mod_t<17>{10},
        mod_t<17>{11},
        mod_t<17>{12},
        mod_t<17>{13},
        mod_t<17>{14},
        mod_t<17>{15},
        mod_t<17>{16}
    };

    auto expected = input;
    fast_iterative_ntt<3, 17>(expected);

    for (int run = 0; run < 100; ++run) {
        auto actual = input;

        threaded_iterative_ntt<3, 17>(actual);

        CHECK(actual == expected);
    }
}