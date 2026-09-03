#ifndef F_I_NTT_HPP
#define F_I_NTT_HPP

#include "mod_t.hpp"
#include <vector>
#include <cstddef>

template<int RootOfUnity, int M>
void fast_iterative_ntt(std::vector<mod_t<M>>& a){
    if (a.size() <= 1) {
        return;
    }

    mod_t<M> omega {RootOfUnity};

    for (std::size_t len = 2; len <= a.size(); len <<= 1) {
        
        //calulates the correct  root -> if  N = 8, and len = 2 wlen = omega^(8/2) = omega^4 primitive 2nd root ... ->len = 8 omega^(8/8) = omega primitive 8th root
        mod_t<M> wlen {omega.exp(static_cast<int>(a.size() / len))};

        for (std::size_t i = 0; i < a.size(); i += len) {
            
            mod_t<M> w{1};
            
            for (std::size_t j = 0; j < len / 2; j++) {
                auto u = a[i + j];
                auto v = a[i + j + len / 2] * w;
                
                //butterfly
                a[i + j] = u + v;
                a[i + j + len/2] = u - v;
                
                w *= wlen;
            }
        }
    }
}
#endif // F_I_NTT_HPP