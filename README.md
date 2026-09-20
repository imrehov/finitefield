# finitefield
![CMake Build & Test](https://github.com/YOUR_GITHUB_USERNAME/finitefield/actions/workflows/cmake.yml/badge.svg)

A modern C++20 / CUDA project exploring finite-field arithmetic and high-performance implementations of the Number Theoretic Transform (NTT).

The goal of the project is to build the same core algorithms in progressively more optimized forms and compare their correctness, performance, and parallelization strategies across CPU and GPU implementations.

## Current status

This project is actively under development.

Implemented so far:

- Modular arithmetic over finite fields
- Naive O(N²) NTT
- Recursive radix-2 NTT
- Iterative in-place radix-2 NTT
- Multithreaded CPU NTT using C++20 `std::jthread`
- Initial CUDA implementation of the naive NTT
- CPU vs CUDA correctness tests
- Unit testing with doctest / CTest
- Benchmarking of CPU implementations

Currently working on:

- Iterative CUDA NTT
- GPU-oriented butterfly parallelization
- CPU vs GPU benchmarking
- CUDA profiling and memory optimization

## Motivation

The project is primarily focused on learning and experimenting with:

- modern C++20
- parallel programming
- CUDA
- finite-field arithmetic
- performance optimization
- cache and memory behavior
- multithreading
- GPU execution models