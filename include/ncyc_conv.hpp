#ifndef NCYC_CONV_HPP
#define NCYC_CONV_HPP

#include <array>
#include <cstddef>

//if the power wraps around it gets minus, because we start from x^n = -1
template<typename T, std::size_t N>
std::array<T, N> ncyc_conv(const std::array<T, N> &a, const std::array<T, N> &b) {
    
    std::array<T, N> result{};

    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            if (i + j < N) {
                result[i + j] += a[i] * b[j];
            }
            else {
                result[i + j - N] -= a[i] * b[j];
            }
        }
    }

    return result;
};

#endif //NCYC_CONV_HPP