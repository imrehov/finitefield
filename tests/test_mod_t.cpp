#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../src/doctest.hpp"

#include "../include/mod_t.hpp"

TEST_CASE("mod_t normalizes positive values") {
    mod_t<7> a(10);

    CHECK(a.get_remainder() == 3);
}

TEST_CASE("mod_t normalizes negative values") {
    mod_t<7> a(-1);

    CHECK(a.get_remainder() == 6);
}

TEST_CASE("mod_t addition wraps around") {
    mod_t<7> a(3);
    mod_t<7> b(6);

    auto c = a + b;

    CHECK(c.get_remainder() == 2);
}

TEST_CASE("mod_t multiplication wraps around") {
    mod_t<7> a(3);
    mod_t<7> b(5);

    auto c = a * b;

    CHECK(c.get_remainder() == 1); // 15 mod 7 = 1
}

TEST_CASE("mod_t subtraction wraps around") {
    mod_t<7> a(3);
    mod_t<7> b(5);

    auto c = a - b;

    CHECK(c.get_remainder() == 5); // -2 mod 7 = 5
}

TEST_CASE("mod_t reciprocal works") {
    mod_t<7> a(3);
    mod_t<7> inv;

    bool ok = a.reciprocal(inv);

    CHECK(ok);
    CHECK(inv.get_remainder() == 5); // 3 * 5 = 15 = 1 mod 7
}

TEST_CASE("mod_t division works") {
    mod_t<7> a(4);
    mod_t<7> b(3);

    auto c = a / b;

    CHECK(c.get_remainder() == 6); // 4 / 3 = 4 * 5 = 20 = 6 mod 7
}

TEST_CASE("mod_t exponentiation works") {
    mod_t<7> a(3);

    CHECK(a.exp(0).get_remainder() == 1);
    CHECK(a.exp(1).get_remainder() == 3);
    CHECK(a.exp(2).get_remainder() == 2); // 9 mod 7 = 2
    CHECK(a.exp(4).get_remainder() == 4); // 81 mod 7 = 4
}