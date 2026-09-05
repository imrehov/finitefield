#include "../include/fast_recursive_ntt.hpp"
#include "../include/mod_t.hpp"
#include "../misc/timer.hpp"

#include <vector>

int main()
{
    constexpr int M = 998244353;
    constexpr int Root = 565042129;

    std::vector<mod_t<M>> a(1 << 20);

    for (std::size_t i = 0; i < a.size(); ++i) {
        a[i] = mod_t<M>{static_cast<int>(i % M)};
    }

    std::vector<mod_t<M>> result;

    {
        Timer timer;
        result = fast_recursive_ntt<M>(a, mod_t<M>{Root});
    }

    std::cout << result.front() << '\n';

    return 0;
}