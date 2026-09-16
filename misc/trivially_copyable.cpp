#include <type_traits>

#include "../include/mod_t.hpp"

//this compiles so i can cudamemcpy mod_t
static_assert(
    std::is_trivially_copyable_v<mod_t<998244353>>
);