#include "../include/threaded_iterative_ntt.hpp"
#include "../misc/timer.hpp"

#include <vector>
#include <iostream>

int main()
{
    constexpr int M = 998244353;
    constexpr int Root = 565042129;

    std::vector<mod_t<M>> a(1 << 20);

    for (std::size_t i = 0; i < a.size(); ++i) {
        a[i] = mod_t<M>{static_cast<int>(i % M)};
    }

    {
        Timer timer;
        threaded_iterative_ntt<Root, M>(a);
    }

    std::cout << a.front() << '\n';

    return 0;
}