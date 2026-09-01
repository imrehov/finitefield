#ifndef RNTT_HPP
#define RNTT_HPP

#include "mod_t.hpp"
#include <vector>
#include <cstddef>

template<int M>
std::vector<mod_t<M>> fast_recursive_ntt(
    const std::vector<mod_t<M>>& a,
    mod_t<M> omega){
    if (a.size() <= 1) {
        return a;
    }

    std::vector<mod_t<M>> even;
    std::vector<mod_t<M>> odd;

    even.reserve(a.size() / 2);
    odd.reserve(a.size() / 2);

    for (std::size_t i = 0; i < a.size() / 2; ++i) {
        even.push_back(a[2 * i]);
        odd.push_back(a[2 * i + 1]);
    }

    // every level needs omega^2
    mod_t<M> omega_squared = omega * omega;

    even = fast_recursive_ntt<M>(even, omega_squared);
    odd  = fast_recursive_ntt<M>(odd, omega_squared);

    std::vector<mod_t<M>> result(a.size());

    mod_t<M> w{1};

    for (std::size_t k = 0; k < a.size() / 2; ++k) {
        auto t = w * odd[k];

        result[k] = even[k] + t;

        result[k + a.size() / 2] = even[k] - t;

        w *= omega;
    }
    
    return result;
}
#endif // RNTT_HPP