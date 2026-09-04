#ifndef RNTT_HPP
#define RNTT_HPP

#include "mod_t.hpp"
#include <vector>
#include <cstddef>

//to do inverse do invert=true
template<int M>
std::vector<mod_t<M>> fast_recursive_ntt(const std::vector<mod_t<M>>& a, mod_t<M> omega, bool invert=false){
    if (a.size() <= 1) {
        return a;
    }

    if (invert) {
        mod_t<M> omega_inv{0};

        if (!omega.reciprocal(omega_inv)) {
            throw std::domain_error("Root of unity is not invertible");
        }

        omega = omega_inv;
    }

    //split even and odd indexes in every recursive call,  thats why it can be nlogn, there are always n/2 butterflies on every level
    // and there are log2n levels -> O(nlogn)
    std::vector<mod_t<M>> even;
    std::vector<mod_t<M>> odd;

    even.reserve(a.size() / 2);
    odd.reserve(a.size() / 2);

    for (std::size_t i {0}; i < a.size() / 2; ++i) {
        even.push_back(a[2 * i]);
        odd.push_back(a[2 * i + 1]);
    }

    // every level needs omega^2
    mod_t<M> omega_squared {omega * omega};

    even = fast_recursive_ntt<M>(even, omega_squared);
    odd  = fast_recursive_ntt<M>(odd, omega_squared);

    std::vector<mod_t<M>> result(a.size());

    mod_t<M> w{1};

    for (std::size_t k {0}; k < a.size() / 2; ++k) {
        auto t = w * odd[k];

        result[k] = even[k] + t;

        result[k + a.size() / 2] = even[k] - t;

        w *= omega;
    }

    if (invert) {
        mod_t<M> n{static_cast<int>(a.size())};

        mod_t<M> n_inv{0};

        if (!n.reciprocal(n_inv)) {
            throw std::domain_error("NTT size is not invertible");
        }

        for (auto& x : result) {
            x *= n_inv;
        }
    }
    
    return result;
}
#endif // RNTT_HPP