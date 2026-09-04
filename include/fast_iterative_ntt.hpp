#ifndef F_I_NTT_HPP
#define F_I_NTT_HPP

#include "mod_t.hpp"
#include <utility>
#include <vector>
#include <cstddef>

template<int RootOfUnity, int M>
void fast_iterative_ntt(std::vector<mod_t<M>>& a){
    if (a.size() <= 1) {
        return;
    }

    //bit reversal, because iterative version starts from the bottom up
    for (std::size_t i {1}, j {0}; i < a.size(); ++i){
        
        //calculate the maximum bit representation: if size is 8 >> 1 = 4 -> in binary: 1000 >>1 = 100 (max is 111)
        //starts at the highest bit used by size 8
        std::size_t bit {a.size() >> 1};

        /*
        this is basically incrementing in binary: starting from the most significant bit

        check & for j and bit -> first iteration:
        000
        &
        100
        ___
        000

        if condition is true: then shift bit from 100 to 010
        but in the first iteration its false -> never executes inner loop and bit >>=1 does not happen either -> bit remains 100
        */
        for (; j & bit; bit >>= 1){  
            // XOR - exclusive or      
            j ^= bit;
        }
        /*
        XOR again:
        000
        XOR
        100
        ___
        100 -> j = 4
        */
        j ^= bit;

        // need this condition, otherwise it swaps everything twice and they end up in the same place
        // first iter:
        // j = 4 i < 4 -> swap happens
        if (i < j){
            std::swap(a[i], a[j]);
        }
    }

    mod_t<M> omega {RootOfUnity};

    //we have log2a.size() stages
    for (std::size_t len {2}; len <= a.size(); len <<= 1) {
        
        //calulates the correct  root -> if  N = 8, and len = 2 wlen = omega^(8/2) = omega^4 primitive 2nd root ... ->len = 8 omega^(8/8) = omega primitive 8th root
        mod_t<M> wlen {omega.exp(static_cast<int>(a.size() / len))};

        for (std::size_t i {0}; i < a.size(); i += len) {
            
            mod_t<M> w{1};
            
            for (std::size_t j {0}; j < len / 2; j++) {
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