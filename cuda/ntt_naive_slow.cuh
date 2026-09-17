#include <algorithm>
#include <memory.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <cuda_runtime_api.h>
#include <cuda/cmath>
#include <vector>

#include "../include/mod_t.hpp"

//make sure you have CUDA_LOG_FILE enviroment variable set to a text file
//then the driver will save more verbose error messages there
#define CUDA_CHECK(expr_to_check) do {            \
    cudaError_t result  = expr_to_check;          \
    if(result != cudaSuccess)                     \
    {                                             \
        fprintf(stderr,                           \
                "CUDA Runtime Error: %s:%i:%d = %s\n", \
                __FILE__,                         \
                __LINE__,                         \
                result,\
                cudaGetErrorString(result));      \
    }                                             \
} while(0)

template <int M>
__global__ void ntt_naive_slow_cuda(const mod_t<M>* A, mod_t<M>* C, const mod_t<M> omega, const int n){
    auto workIndex {threadIdx.x + blockIdx.x * blockDim.x};

    if (workIndex < n){
        for (std::size_t i {0}; i < n; ++i) {
            C[workIndex] += A[i] * omega.exp(static_cast<int>(workIndex * i));        
        }
    }
}

// param n is the length of the vector, idk might be btter option to include it
template <int RootOfUnity, int M>
std::vector<mod_t<M>> ntt_naive_slow_cuda_wrapper(const int n){
    
    const mod_t<M> omega {RootOfUnity};

    const auto length {n * sizeof(mod_t<M>)};
    
    mod_t<M>* A {nullptr};
    mod_t<M>* C {nullptr};

    mod_t<M>* devA {nullptr};
    mod_t<M>* devC {nullptr};

    CUDA_CHECK(cudaMallocHost(&A, length));
    CUDA_CHECK(cudaMallocHost(&C, length));

    fillAllocatedArray(A, n);

    CUDA_CHECK(cudaMalloc(&devA, length));
    CUDA_CHECK(cudaMalloc(&devC, length));

    CUDA_CHECK(cudaMemcpy(devA, A, length, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemset(devC, 0, length));

    constexpr int threads {256};

    //this is basically (n + threads - 1) / threads
    const int blocks {cuda::ceil_div(n, threads)};

    ntt_naive_slow_cuda<M><<<blocks, threads>>>(devA, devC, omega, n);

    //need this because <<< doesnt return cudaError_t
    CUDA_CHECK(cudaGetLastError());

    CUDA_CHECK(cudaDeviceSynchronize());

    CUDA_CHECK(cudaMemcpy(C, devC, length, cudaMemcpyDeviceToHost));

    for (int i = 0; i < n; ++i) {
        std::cout << C[i] << ' ';
    }

    std::cout << '\n';

    std::vector<mod_t<M>> result {C, C + n};

    //cleanup
    CUDA_CHECK(cudaFree(devA));
    CUDA_CHECK(cudaFree(devC));
    CUDA_CHECK(cudaFreeHost(A));
    CUDA_CHECK(cudaFreeHost(C));

    return result;
    
}
template <int M>
void fillAllocatedArray(mod_t<M>* a, int len){

    //std::iota(a, a + len, mod_t<M>{1});

    for (std::size_t i {0}; i < len; ++i) {
        mod_t<M> temp {static_cast<int>(i) + 1};
        a[i] = temp;
    }

}