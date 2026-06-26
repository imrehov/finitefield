#ifndef NTT_SLOWMULT_HPP
#define NTT_SLOWMULT_HPP

#include <array>
#include <cstddef>
#include "mod_t.hpp"
#include "ntt_naive_slow.hpp"
#include "intt_naive_slow.hpp"

/*
to multiply polynomials with the help of NTT
1. pad both vectors with zeroes to double the size
2. NTT(A)
3. NTT(B)
4. pointwise multiplication
5. inverse NTT(result)
6. keep first 2N-1 coeffs where N is the size of A and B
*/

// N is size of A and B input vectors, L is the size of the output(power of 2)
template<int RootOfUnity, int M, std::size_t N, std::size_t L>
std::array<mod_t<M>, 2 * N - 1>
ntt_naive_slow_multiply(const std::array<mod_t<M>, N>& a,
                        const std::array<mod_t<M>, N>& b) {
    static_assert(L >= 2 * N - 1, "NTT size must fit multiplication result");

    std::array<mod_t<M>, L> padded_a{};
    std::array<mod_t<M>, L> padded_b{};

    for (std::size_t i = 0; i < N; ++i) {
        padded_a[i] = a[i];
        padded_b[i] = b[i];
    }

    auto A = ntt_naive_slow<RootOfUnity, M, L>(padded_a);
    auto B = ntt_naive_slow<RootOfUnity, M, L>(padded_b);

    std::array<mod_t<M>, L> C{};

    for (std::size_t i = 0; i < L; ++i) {
        C[i] = A[i] * B[i];
    }

    auto full_result = intt_naive_slow<RootOfUnity, M, L>(C);

    std::array<mod_t<M>, 2 * N - 1> result{};

    for (std::size_t i = 0; i < 2 * N - 1; ++i) {
        result[i] = full_result[i];
    }

    return result;
}

#endif // NTT_SLOWMULT_HPP