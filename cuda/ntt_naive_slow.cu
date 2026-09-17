#include <memory.h>
#include <cstdlib>
#include <ctime>
#include <numeric>

#include <cuda_runtime_api.h>
#include <cuda/cmath>

#include "../include/mod_t.hpp"

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
void ntt_naive_slow_cuda_wrapper(const int n){
    
    constexpr mod_t<M> omega {RootOfUnity};

    const auto length {n * sizeof(mod_t<M>)};
    
    mod_t<M>* A {nullptr};
    mod_t<M>* C {nullptr};

    mod_t<M>* devA {nullptr};
    mod_t<M>* devC {nullptr};

    cudaMallocHost(&A, length);
    cudaMallocHost(&C, length);

    fillAllocatedArray(A, n);

    cudaMalloc(&devA, length);

    cudaMalloc(&devC, length);

    cudaMemcpy(devA, A, length, cudaMemcpyHostToDevice);
    cudaMemset(devC, 0, length);

    constexpr int threads {256};

    //this is basically (n + threads - 1) / threads
    const int blocks {cuda::ceil_div(n, threads)};

    ntt_naive_slow_cuda<M><<<blocks, threads>>>(devA, devC, n);

    cudaDeviceSynchronize();

    cudaMemcpy(C, devC, length, cudaMemcpyDeviceToHost);

    //cleanup
    cudaFree(devA);
    cudaFree(devC);
    cudaFreeHost(A);
    cudaFreeHost(C);

    
}
template <int M>
void fillAllocatedArray(mod_t<M>* a, int len){
    std::iota(a, a + len, mod_t<M>{1});

}

int main(){

    return 0;
}