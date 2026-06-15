#include <array>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../src/doctest.hpp"

#include "../include/ntt_naive_slow.hpp"

TEST_CASE("naive NTT works for size 4 modulo 17") {
    std::array<mod_t<17>, 4> a{
        mod_t<17>{1},
        mod_t<17>{2},
        mod_t<17>{3},
        mod_t<17>{4}
    };

    auto result = ntt_naive_slow<4, 17, 4>(a);

    std::array<mod_t<17>, 4> expected{
        mod_t<17>{10},
        mod_t<17>{7},
        mod_t<17>{15},
        mod_t<17>{6}
    };

    CHECK(result == expected);
}

TEST_CASE("naive NTT of constant polynomial gives same value everywhere") {
    std::array<mod_t<17>, 4> a{
        mod_t<17>{3},
        mod_t<17>{0},
        mod_t<17>{0},
        mod_t<17>{0}
    };

    auto result = ntt_naive_slow<4, 17, 4>(a);

    std::array<mod_t<17>, 4> expected{
        mod_t<17>{3},
        mod_t<17>{3},
        mod_t<17>{3},
        mod_t<17>{3}
    };

    CHECK(result == expected);
}

TEST_CASE("naive NTT of x gives powers of root of unity") {
    std::array<mod_t<17>, 4> a{
        mod_t<17>{0},
        mod_t<17>{1},
        mod_t<17>{0},
        mod_t<17>{0}
    };

    auto result = ntt_naive_slow<4, 17, 4>(a);

    std::array<mod_t<17>, 4> expected{
        mod_t<17>{1},
        mod_t<17>{4},
        mod_t<17>{16},
        mod_t<17>{13}
    };

    CHECK(result == expected);
}

TEST_CASE("naive NTT of all ones collapses to first coefficient") {
    std::array<mod_t<17>, 4> a{
        mod_t<17>{1},
        mod_t<17>{1},
        mod_t<17>{1},
        mod_t<17>{1}
    };

    auto result = ntt_naive_slow<4, 17, 4>(a);

    std::array<mod_t<17>, 4> expected{
        mod_t<17>{4},
        mod_t<17>{0},
        mod_t<17>{0},
        mod_t<17>{0}
    };

    CHECK(result == expected);
}