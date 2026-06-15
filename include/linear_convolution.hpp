#pragma once

#include <array>
#include <cstddef>

template<typename T, std::size_t N>
std::array<T, 2 * N - 1> lin_conv(const std::array<T, N>& a,
                                  const std::array<T, N>& b) {
    std::array<T, 2 * N - 1> result{};

    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            result[i + j] += a[i] * b[j];
        }
    }

    return result;
}