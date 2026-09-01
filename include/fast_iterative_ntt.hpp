#ifndef F_I_NTT_HPP
#define F_I_NTT_HPP

#include "mod_t.hpp"
#include <vector>
#include <cstddef>

template<int RootOfUnity, int M>
std::vector<mod_t<M>> fast_iterative_ntt(const std::vector<mod_t<M>>& a) {
    
    std::vector<mod_t<M>> result{a};

    const std::size_t n {a.size()};

    mod_t<M> omega{RootOfUnity};

    

    return result;
}

#endif // F_I_NTT_HPP