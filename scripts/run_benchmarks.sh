#!/usr/bin/env bash

RUNS=100

THREADED="../build-release/./benchmark_threaded_ntt"
SINGLE_ITER="../build-release/./benchmark_singlethread_iter_ntt"
SINGLE_REC="../build-release/./benchmark_singlethread_rec_ntt"

cd scripts/

rm -f benchmark_results/*_results.txt

for ((i = 1; i <= RUNS; i++)); do
    echo "Run $i/$RUNS"

    echo "===== RUN $i =====" >> benchmark_results/threaded_results.txt
    "$THREADED" >> benchmark_results/threaded_results.txt

    echo "===== RUN $i =====" >> benchmark_results/iter_results.txt
    "$SINGLE_ITER" >> benchmark_results/iter_results.txt

    echo "===== RUN $i =====" >> benchmark_results/rec_results.txt
    "$SINGLE_REC" >> benchmark_results/rec_results.txt

done

cd ..

echo "Done."