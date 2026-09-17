#include <__clang_cuda_runtime_wrapper.h>
#include <cuda_runtime_api.h>
#include <memory.h>
#include <cstdlib>
#include <ctime>
#include <stdio.h>

#include "../include/mod_t.hpp"


__global__ void ntt_naive_slow_cuda(){

}

// param n is the length of the vector, idk might be btter option to include it
template <int RootOfUnity, int M>
void ntt_naive_slow_cuda_wrapper(int n){
    mod_t<M>* A {nullptr};
    mod_t<M>* B {nullptr};
    mod_t<M>* C {nullptr};

    mod_t<M>* devA {nullptr};
    mod_t<M>* devB {nullptr};
    mod_t<M>* devC {nullptr};

    cudaMallocHost(&A, n * sizeof(mod_t<M>));
    cudaMallocHost(&B, n * sizeof(mod_t<M>));
    cudaMallocHost(&C, n * sizeof(mod_t<M>));
}

int main(){

    return 0;
}