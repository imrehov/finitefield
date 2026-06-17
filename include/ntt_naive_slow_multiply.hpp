#ifndef NTT_SLOWMULT_HPP
#define NTT_SLOWMULT_HPP


#include "mod_t.hpp"
#include <cstddef>
#include <vector>

template<int RootOfUnity, int M>
std::vector<mod_t<M>> ntt_naive_slow(std::vector<mod_t<M>> &a,std::vector<mod_t<M>> &b){
    for (std::size_t i = a.size(); i < a.size() * 2; ++i) {
        //not sure if its correct to use vec here
        //maybe if i use vec here i should just rewrite everything to vec??
    }
};

#endif //NTT_SLOWMULT_HPP