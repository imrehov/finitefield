
#include "mod_t.hpp"
#include <array>
#include <cstddef>
#include <vector>

//evaulate a polynomial from vector representation at x
template<int M, std::size_t N>
int poly_eval(std::array<mod_t<M>, N> &a, int x){

    int result = a[0].get_remainder();

    for (std::size_t i = 1; i < N; i++) {
        result = (result * x + a[i].get_remainder()) % M;
    }

    return result;
}

template<int M>
int poly_eval(std::vector<mod_t<M>> &a, int x){

    const std::size_t N = a.size();

    int result = a[0].get_remainder();

    for (std::size_t i = 1; i < N; i++) {
        result = (result * x + a[i].get_remainder()) % M;
    }

    return result;
}