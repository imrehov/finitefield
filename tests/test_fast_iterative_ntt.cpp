#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../src/doctest.hpp"

#include "../include/fast_iterative_ntt.hpp"
#include "../include/fast_recursive_ntt.hpp"


TEST_CASE("iterative NTT works for size 4 modulo 17") {
    std::vector<mod_t<17>> a{
        mod_t<17>{1},
        mod_t<17>{2},
        mod_t<17>{3},
        mod_t<17>{4}
    };

    fast_iterative_ntt<4, 17>(a);

    std::vector<mod_t<17>> expected{
        mod_t<17>{10},
        mod_t<17>{7},
        mod_t<17>{15},
        mod_t<17>{6}
    };

    CHECK(a == expected);
}


TEST_CASE("iterative NTT of constant polynomial gives same value everywhere") {
    std::vector<mod_t<17>> a{
        mod_t<17>{3},
        mod_t<17>{0},
        mod_t<17>{0},
        mod_t<17>{0}
    };

    fast_iterative_ntt<4, 17>(a);

    std::vector<mod_t<17>> expected{
        mod_t<17>{3},
        mod_t<17>{3},
        mod_t<17>{3},
        mod_t<17>{3}
    };

    CHECK(a == expected);
}


TEST_CASE("iterative NTT of x gives powers of root of unity") {
    std::vector<mod_t<17>> a{
        mod_t<17>{0},
        mod_t<17>{1},
        mod_t<17>{0},
        mod_t<17>{0}
    };

    fast_iterative_ntt<4, 17>(a);

    std::vector<mod_t<17>> expected{
        mod_t<17>{1},
        mod_t<17>{4},
        mod_t<17>{16},
        mod_t<17>{13}
    };

    CHECK(a == expected);
}


TEST_CASE("iterative NTT of all ones collapses to first coefficient") {
    std::vector<mod_t<17>> a{
        mod_t<17>{1},
        mod_t<17>{1},
        mod_t<17>{1},
        mod_t<17>{1}
    };

    fast_iterative_ntt<4, 17>(a);

    std::vector<mod_t<17>> expected{
        mod_t<17>{4},
        mod_t<17>{0},
        mod_t<17>{0},
        mod_t<17>{0}
    };

    CHECK(a == expected);
}


TEST_CASE("iterative NTT works for size 2 modulo 17") {
    std::vector<mod_t<17>> a{
        mod_t<17>{3},
        mod_t<17>{7}
    };

    // 16 == -1 mod 17, primitive 2nd root
    fast_iterative_ntt<16, 17>(a);

    std::vector<mod_t<17>> expected{
        mod_t<17>{10},
        mod_t<17>{13}
    };

    CHECK(a == expected);
}


TEST_CASE("iterative NTT works for size 1") {
    std::vector<mod_t<17>> a{
        mod_t<17>{7}
    };

    fast_iterative_ntt<1, 17>(a);

    std::vector<mod_t<17>> expected{
        mod_t<17>{7}
    };

    CHECK(a == expected);
}


TEST_CASE("iterative NTT works for size 8 modulo 17") {
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
    fast_iterative_ntt<2, 17>(a);

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

TEST_CASE("iterative NTT matches recursive NTT") {
    std::vector<mod_t<17>> input{
        mod_t<17>{1},
        mod_t<17>{2},
        mod_t<17>{3},
        mod_t<17>{4},
        mod_t<17>{5},
        mod_t<17>{6},
        mod_t<17>{7},
        mod_t<17>{8}
    };

    auto recursive =
        fast_recursive_ntt<17>(input, mod_t<17>{2});

    auto iterative = input;
    fast_iterative_ntt<2, 17>(iterative);

    CHECK(iterative == recursive);
}