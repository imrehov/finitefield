#include <__clang_cuda_runtime_wrapper.h>
#include <cuda_runtime_api.h>
#include <memory.h>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <stdio.h>
#include <cuda/cmath>

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

    fillAllocatedArray(A);
    fillAllocatedArray(B);

    cudaMalloc(&devA, n * sizeof(mod_t<M>));
    cudaMalloc(&devB, n * sizeof(mod_t<M>));
    cudaMalloc(&devC, n * sizeof(mod_t<M>));

    cudaMemcpy(devA, A, n * sizeof(mod_t<M>), cudaMemcpyHostToDevice);
    cudaMemcpy(devB, B, n * sizeof(mod_t<M>), cudaMemcpyHostToDevice);
    cudaMemset(devC, 0, n * sizeof(mod_t<M>));

    int threads {256};
    //TODO where is this from
    int blocks {cuda::ceil_div(n, threads)};

    //TODO finish
}
template <int M>
void fillAllocatedArray(mod_t<M>* a, int len){
    std::iota(std::begin(a), std::end(a), 1);

}

int main(){

    return 0;
}