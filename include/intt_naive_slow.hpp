#ifndef INTT_HPP
#define INTT_HPP

#include "mod_t.hpp"
#include <array>
#include <cstddef>

//the only thing that changes is that we need to multiply the sum with n^-1 and take omega^-k * j
template<int RootOfUnity, int M, std::size_t N>
std::array<mod_t<M>, N> intt_naive_slow(const std::array<mod_t<M>, N>& a) {
    std::array<mod_t<M>, N> result{};

    mod_t<M> omega{RootOfUnity};

    //cant use -k because unsigned
    mod_t<M> omega_inv = omega.exp(-1);

    mod_t<M> n_inv = mod_t<M>{static_cast<int>(N)}.exp(-1);

    for (std::size_t k = 0; k < N; ++k) {
        result[k] = mod_t<M>{0};

        for (std::size_t j = 0; j < N; ++j) {
            result[k] += a[j] * omega_inv.exp(static_cast<int>(j * k));
        }
        //need to multiply with the n^-1 scaling factor
        result[k] *= n_inv;
    }

    return result;
}

#endif // INTT_HPP