#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "mod_t.hpp"
#include <vector>

#include "../src/doctest.hpp"

#include "../cuda/ntt_naive_slow.cuh"
#include "../include/ntt_naive_slow.hpp"

TEST_CASE("CUDA naive NTT matches CPU naive NTT")
{
    constexpr int M = 17;
    constexpr int Root = 4;
    constexpr int N = 4;

    auto cuda_result = ntt_naive_slow_cuda_wrapper<Root, M>(N);

    std::vector<mod_t<17>> input{1, 2, 3, 4};
    auto cpu_result = ntt_naive_slow<Root, M>(input);

    CHECK(cuda_result == cpu_result);
}