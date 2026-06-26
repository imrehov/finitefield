#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../src/doctest.hpp"

#include "../include/ntt_naive_slow_multiply.hpp"

#include <array>


TEST_CASE("NTT multiplication matches known linear convolution modulo 17") {
    std::array<mod_t<17>, 4> a{
        mod_t<17>{1},
        mod_t<17>{2},
        mod_t<17>{3},
        mod_t<17>{4}
    };

    std::array<mod_t<17>, 4> b{
        mod_t<17>{5},
        mod_t<17>{6},
        mod_t<17>{7},
        mod_t<17>{8}
    };

    auto result = ntt_naive_slow_multiply<9, 17, 4, 8>(a, b);

    std::array<mod_t<17>, 7> expected{
        mod_t<17>{5},   // 5
        mod_t<17>{16},  // 16
        mod_t<17>{34},  // 34 mod 17 = 0
        mod_t<17>{60},  // 60 mod 17 = 9
        mod_t<17>{61},  // 61 mod 17 = 10
        mod_t<17>{52},  // 52 mod 17 = 1
        mod_t<17>{32}   // 32 mod 17 = 15
    };

    CHECK(result == expected);
}