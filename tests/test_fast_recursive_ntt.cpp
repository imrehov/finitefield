#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../src/doctest.hpp"

#include "../include/fast_recursive_ntt.hpp"


TEST_CASE("recursive NTT works for size 4 modulo 17") {
    std::vector<mod_t<17>> a{
        mod_t<17>{1},
        mod_t<17>{2},
        mod_t<17>{3},
        mod_t<17>{4}
    };

    auto result = fast_recursive_ntt<17>(
        a,
        mod_t<17>{4}
    );

    std::vector<mod_t<17>> expected{
        mod_t<17>{10},
        mod_t<17>{7},
        mod_t<17>{15},
        mod_t<17>{6}
    };

    CHECK(result == expected);
}


TEST_CASE("recursive NTT of constant polynomial gives same value everywhere") {
    std::vector<mod_t<17>> a{
        mod_t<17>{3},
        mod_t<17>{0},
        mod_t<17>{0},
        mod_t<17>{0}
    };

    auto result = fast_recursive_ntt<17>(
        a,
        mod_t<17>{4}
    );

    std::vector<mod_t<17>> expected{
        mod_t<17>{3},
        mod_t<17>{3},
        mod_t<17>{3},
        mod_t<17>{3}
    };

    CHECK(result == expected);
}


TEST_CASE("recursive NTT of x gives powers of root of unity") {
    std::vector<mod_t<17>> a{
        mod_t<17>{0},
        mod_t<17>{1},
        mod_t<17>{0},
        mod_t<17>{0}
    };

    auto result = fast_recursive_ntt<17>(
        a,
        mod_t<17>{4}
    );

    std::vector<mod_t<17>> expected{
        mod_t<17>{1},
        mod_t<17>{4},
        mod_t<17>{16},
        mod_t<17>{13}
    };

    CHECK(result == expected);
}


TEST_CASE("recursive NTT of all ones collapses to first coefficient") {
    std::vector<mod_t<17>> a{
        mod_t<17>{1},
        mod_t<17>{1},
        mod_t<17>{1},
        mod_t<17>{1}
    };

    auto result = fast_recursive_ntt<17>(
        a,
        mod_t<17>{4}
    );

    std::vector<mod_t<17>> expected{
        mod_t<17>{4},
        mod_t<17>{0},
        mod_t<17>{0},
        mod_t<17>{0}
    };

    CHECK(result == expected);
}


TEST_CASE("recursive NTT works for size 2 modulo 17") {
    std::vector<mod_t<17>> a{
        mod_t<17>{3},
        mod_t<17>{7}
    };

    // -1 mod 17 = 16, primitive 2nd root of unity
    auto result = fast_recursive_ntt<17>(
        a,
        mod_t<17>{16}
    );

    std::vector<mod_t<17>> expected{
        mod_t<17>{10},
        mod_t<17>{13}
    };

    CHECK(result == expected);
}


TEST_CASE("recursive NTT works for size 1") {
    std::vector<mod_t<17>> a{
        mod_t<17>{7}
    };

    auto result = fast_recursive_ntt<17>(
        a,
        mod_t<17>{1}
    );

    std::vector<mod_t<17>> expected{
        mod_t<17>{7}
    };

    CHECK(result == expected);
}