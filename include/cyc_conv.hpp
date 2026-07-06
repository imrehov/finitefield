#ifndef CYC_CONV_HPP
#define CYC_CONV_HPP

#include <array>
#include <cstddef>
#include <stdexcept>
#include <vector>

// y[k] = sum_i a[i] * b[(k - i) mod N]
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

template<typename T>
std::vector<T> cyc_conv(const std::vector<T> &a, const std::vector<T> &b) {
    
    if (a.size() != b.size()) {
        throw std::invalid_argument("cyclic convolution needs equal sizes");
    }

    std::size_t N = a.size();

    //initialize a result vector with N elements already so we dont have to add them in the loop
    std::vector<T> result(N, T{});

    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            result[(i + j) % N] += a[i] * b[j];
        }
    }

    return result;
};

#endif //CYC_CONV_HPP