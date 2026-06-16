#include <array>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../src/doctest.hpp"

#include "../include/ntt_naive_slow.hpp"
#include "../include/intt_naive_slow.hpp"

TEST_CASE("inverse NTT reverses forward NTT") {
    std::array<mod_t<17>, 4> a{
        mod_t<17>{1},
        mod_t<17>{2},
        mod_t<17>{3},
        mod_t<17>{4}
    };

    auto transformed = ntt_naive_slow<4, 17, 4>(a);
    auto recovered = intt_naive_slow<4, 17, 4>(transformed);

    CHECK(recovered == a);
}

TEST_CASE("inverse NTT works for known transformed vector") {
    std::array<mod_t<17>, 4> transformed{
        mod_t<17>{10},
        mod_t<17>{7},
        mod_t<17>{15},
        mod_t<17>{6}
    };

    auto recovered = intt_naive_slow<4, 17, 4>(transformed);

    std::array<mod_t<17>, 4> expected{
        mod_t<17>{1},
        mod_t<17>{2},
        mod_t<17>{3},
        mod_t<17>{4}
    };

    CHECK(recovered == expected);
}