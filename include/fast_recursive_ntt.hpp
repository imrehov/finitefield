#ifndef RNTT_HPP
#define RNTT_HPP

#include "mod_t.hpp"
#include <array>
#include <cstddef>

template<int RootOfUnity, int M, std::size_t N>
std::array<mod_t<M>, N> ntt_naive_slow(const std::array<mod_t<M>, N> &a) {
    std::array<mod_t<M>, N> result{};

    mod_t<M> omega{RootOfUnity};

    for (std::size_t k = 0; k < N; ++k) {
        result[k] = mod_t<M>{0};

        for (std::size_t j = 0; j < N; ++j) {
            result[k] += a[j] * omega.exp(static_cast<int>(j * k));
        }
    }

    return result;
}

#endif // RNTT_HPP