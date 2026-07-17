#ifndef NTT_SLOWMULT_HPP
#define NTT_SLOWMULT_HPP

#include <array>
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <vector>
#include "mod_t.hpp"
#include "ntt_naive_slow.hpp"
#include "intt_naive_slow.hpp"

//to multiply polynomials with the help of NTT
//1. pad both vectors with zeroes to double the size
//2. NTT(A)
//3. NTT(B)
//4. pointwise multiplication
//5. inverse NTT(result)
//6. keep first 2N-1 coeffs where N is the size of A and B

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

//to multiply polynomials with the help of NTT
//1. pad both vectors with zeroes to double the size
//2. NTT(A)
//3. NTT(B)
//4. pointwise multiplication
//5. inverse NTT(result)
//6. keep first 2N-1 coeffs where N is the size of A and B
//need to calc nearest power of 2, take log2(x) and round up and raise 2 to that pow 


inline std::size_t next_power_of_two(std::size_t x) {
    std::size_t result = 1;

    while (result < x) {
        result *= 2;
    }

    return result;
}

template<int RootOfUnity, int M>
std::vector<mod_t<M>>
ntt_naive_slow_multiply(const std::vector<mod_t<M>>& a,
                        const std::vector<mod_t<M>>& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("need matching size vectors");
    }

    if (a.empty()) {
        throw std::invalid_argument("input vectors must not be empty");
    }

    const std::size_t N {a.size()};
    const std::size_t result_size {2 * N - 1};
    const std::size_t L {next_power_of_two(result_size)};

    std::vector<mod_t<M>> padded_a(L, mod_t<M>{});
    std::vector<mod_t<M>> padded_b(L, mod_t<M>{});

    for (std::size_t i = 0; i < N; ++i) {
        padded_a[i] = a[i];
        padded_b[i] = b[i];
    }

    auto A = ntt_naive_slow<RootOfUnity, M>(padded_a);
    auto B = ntt_naive_slow<RootOfUnity, M>(padded_b);

    std::vector<mod_t<M>> C(L, mod_t<M>{});

    for (std::size_t i = 0; i < L; ++i) {
        C[i] = A[i] * B[i];
    }

    auto full_result = intt_naive_slow<RootOfUnity, M>(C);

    std::vector<mod_t<M>> result(result_size, mod_t<M>{});

    for (std::size_t i = 0; i < result_size; ++i) {
        result[i] = full_result[i];
    }

    return result;
}
#endif // NTT_SLOWMULT_HPP