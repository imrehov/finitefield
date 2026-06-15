#ifndef CYC_CONV_HPP
#define CYC_CONV_HPP

#include <array>
#include <cstddef>

//y[k % N] = sum_i^k a[i] * b[k - i]
template<typename T, std::size_t N>
std::array<T, N> cyc_conv(const std::array<T, N> &a, const std::array<T, N> &b) {
    
    std::array<T, N> result{};

    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            result[(i + j) % N] += a[i] * b[j];
        }
    }

    return result;
};

#endif //CYC_CONV_HPP