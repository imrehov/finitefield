#!/usr/bin/env bash

rm -rf build-ci-test

cmake -S . -B build-ci-test \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_TESTING=ON \
    -DBUILD_BENCHMARKS=OFF \
    -DENABLE_CUDA=ON

cmake --build build-ci-test --parallel

ctest --test-dir build-ci-test --output-on-failure