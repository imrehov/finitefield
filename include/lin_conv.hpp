#ifndef LIN_CONV_HPP
#define LIN_CONV_HPP

#include <array>
#include <cstddef>
#include <stdexcept>
#include <vector>

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

//y[k] = sum_i^k a[i] * b[k - i]
template<typename T>
std::vector<T> lin_conv(const std::vector<T> &a, const std::vector<T> &b) {

    if (a.size() != b.size()){
        throw std::invalid_argument("lin conv needs equal sizes");
    }
    
    const std::size_t N = a.size();

    std::vector<T> result(2 * N - 1, T{});

    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            result[i + j] += a[i] * b[j];
        }
    }

    return result;
};

#endif //LIN_CONV_HPP