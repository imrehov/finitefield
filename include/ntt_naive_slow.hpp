#ifndef NTT_HPP
#define NTT_HPP

#include "mod_t.hpp"
#include <array>
#include <cstddef>
#include <vector>

template<int RootOfUnity, int M, std::size_t N>
std::array<mod_t<M>, N> ntt_naive_slow(const std::array<mod_t<M>, N> &a) {
    std::array<mod_t<M>, N> result{};

    mod_t<M> omega{RootOfUnity};

    for (std::size_t k {0}; k < N; ++k) {
        result[k] = mod_t<M>{0};

        for (std::size_t j = 0; j < N; ++j) {
            result[k] += a[j] * omega.exp(static_cast<int>(j * k));
        }
    }

    return result;
}

template<int RootOfUnity, int M>
std::vector<mod_t<M>> ntt_naive_slow(const std::vector<mod_t<M>> &a) {
    
    const std::size_t N = a.size();
    
    std::vector<mod_t<M>> result(N, mod_t<M>{0});

    mod_t<M> omega{RootOfUnity};

    for (std::size_t k {0}; k < N; ++k) {

        for (std::size_t j {0}; j < N; ++j) {
            result[k] += a[j] * omega.exp(static_cast<int>(j * k));
        }
    }

    return result;
}

#endif // NTT_HPP