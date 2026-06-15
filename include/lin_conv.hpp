#ifndef LIN_CONV_HPP
#define LIN_CONV_HPP

#include <array>
#include <cstddef>

//y[k] = sum_i^k a[i] * b[k - i]
template<typename T, std::size_t N>
std::array<T, 2 * N - 1> lin_conv(const std::array<T, N> &a, const std::array<T, N> &b) {
    
    std::array<T, 2 * N - 1> result{};

    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            result[i + j] += a[i] * b[j];
        }
    }

    return result;
};

#endif //LIN_CONV_HPP