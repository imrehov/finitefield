#ifndef T_I_NTT
#define T_I_NTT

#include "mod_t.hpp"
#include <algorithm>
#include <utility>
#include <vector>
#include <cstddef>
#include <thread>

//inverse can be toggled on but forward ntt by default
template<int RootOfUnity, int M>
void threaded_iterative_ntt(std::vector<mod_t<M>>& a, bool invert=false){
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

    if (invert) {
        mod_t<M> omega_inv{0};

        if (!omega.reciprocal(omega_inv)) {
            throw std::domain_error("Root of unity is not invertible");
        }

        omega = omega_inv;
    }

    //we have log2a.size() stages, len = how big is 1 independent ntt block on each stage
    //stage loop
    for (std::size_t len {2}; len <= a.size(); len <<= 1) {
        
        // if n=32 then we have 32/2 16 blocks, with 2 items per block -> 16 threads with 2 items per thread
        auto number_of_blocks {a.size() / len};

        //calc to see how many threads, my cpu has 24, not using hardwareconcurrency because it can return 0
        auto number_of_threads {std::min(number_of_blocks, std::size_t {24})};

        //calulates the correct  root -> if  N = 8, and len = 2 wlen = omega^(8/2) = omega^4 primitive 2nd root ... ->len = 8 omega^(8/8) = omega primitive 8th root
        mod_t<M> wlen {omega.exp(static_cast<int>(a.size() / len))};

        //reserve room for threads, doesnt launch
        std::vector<std::jthread> threads;
        threads.reserve(number_of_threads);

        //worker loop
        for (std::size_t l {0}; l < number_of_threads; ++l){

            threads.emplace_back(
                [&, l](){

                        //calc what belongs to the worker                                
                        std::size_t block_begin{l * number_of_blocks / number_of_threads};

                        //exclusive end
                        std::size_t block_end{(l + 1) * number_of_blocks / number_of_threads};

                        //convert block number to array index
                        for (std::size_t i {block_begin * len}; i < (block_end * len); i += len) {
                        
                            //separate twiddle facto for every block
                            mod_t<M> w{1};
                            
                            //butterfly loop stays the same as single thread
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
            );
        }
        
    }

    if (invert) {
        mod_t<M> n{
            static_cast<int>(a.size())
        };

        mod_t<M> n_inv{0};

        if (!n.reciprocal(n_inv)) {
            throw std::domain_error(
                "NTT size is not invertible modulo M"
            );
        }

        for (auto& x : a) {
            x *= n_inv;
        }
    }
}

#endif //T_I_NTT