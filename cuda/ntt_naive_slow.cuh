#include <memory.h>
#include <cstdlib>
#include <ctime>

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
__global__ void ntt_naive_slow_cuda(const mod_t<M>* A, mod_t<M>* C, const mod_t<M> omega, const std::size_t n){
    auto workIndex {threadIdx.x + blockIdx.x * blockDim.x};

    if (workIndex < n){
        for (std::size_t i {0}; i < n; ++i) {
            C[workIndex] += A[i] * omega.exp(static_cast<int>(workIndex * i));        
        }
    }
}

// param n is the length of the vector, idk might be btter option to include it
template <int RootOfUnity, int M>
std::vector<mod_t<M>> ntt_naive_slow_cuda_wrapper(const std::vector<mod_t<M>>& a){
    
    //cannot do static_assert because vector.empty() is runtime
    if (a.empty()) {
        throw std::invalid_argument("input vector is empty");
    }

    const mod_t<M> omega {RootOfUnity};

    const std::size_t n{a.size()};
    //needed bcs cuda allocation/copy size is calcd in bytes
    const std::size_t bytes{n * sizeof(mod_t<M>)};
    
    const mod_t<M>* A{a.data()};

    mod_t<M>* devA {nullptr};
    mod_t<M>* devC {nullptr};

    CUDA_CHECK(cudaMalloc(&devA, bytes));
    CUDA_CHECK(cudaMalloc(&devC, bytes));

    CUDA_CHECK(cudaMemcpy(devA, A, bytes, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemset(devC, 0, bytes));

    constexpr std::size_t threads {256};

    //this is basically (n + threads - 1) / threads
    const std::size_t blocks {cuda::ceil_div(bytes, threads)};

    ntt_naive_slow_cuda<M><<<blocks, threads>>>(devA, devC, omega, n);

    //need this because <<< doesnt return cudaError_t
    CUDA_CHECK(cudaGetLastError());

    CUDA_CHECK(cudaDeviceSynchronize());

    std::vector<mod_t<M>> result_vec(n);

    CUDA_CHECK(cudaMemcpy(result_vec.data(), devC, bytes, cudaMemcpyDeviceToHost));

    //cleanup
    CUDA_CHECK(cudaFree(devA));
    CUDA_CHECK(cudaFree(devC));

    return result_vec;
    
}

template <int M>
void fillAllocatedArray(mod_t<M>* a, int len){

    //std::iota(a, a + len, mod_t<M>{1});

    for (std::size_t i {0}; i < len; ++i) {
        mod_t<M> temp {static_cast<int>(i) + 1};
        a[i] = temp;
    }

}