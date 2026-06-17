#include <array>
#include <cmath>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../src/doctest.hpp"

#include "../include/poly_eval.hpp"

TEST_CASE("evaluating basic polynomial"){
    // this is x^3 + 2x^2 + 3x + 4
    std::array<mod_t<10>, 4> a{
        mod_t<10>{1},
        mod_t<10>{2},
        mod_t<10>{3},
        mod_t<10>{4}
    };

    //substitute x = 2 into the above
    auto result = poly_eval(a, 2);

    int expected = (8 + 8 + 6 + 4) % 10;

    CHECK(result == expected);
}