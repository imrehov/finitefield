cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(finitefield LANGUAGES CXX)

find_package(Threads REQUIRED)


add_library(finitefield INTERFACE)

target_include_directories(
    finitefield
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(
    finitefield
    INTERFACE
        cxx_std_20
)

if (BUILD_BENCHMARKS)
    function(add_benchmark benchmark_name)
    add_executable(
            ${benchmark_name}
            benchmarks/${benchmark_name}.cpp
        )

        target_link_libraries(
            ${benchmark_name}
            PRIVATE
                finitefield
        )

        target_include_directories(
            ${benchmark_name}
            PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/misc
        )

        target_link_libraries(
            ${benchmark_name}
            PRIVATE
                Threads::Threads
        )

    endfunction()

    add_benchmark(benchmark_threaded_ntt)
    add_benchmark(benchmark_singlethread_iter_ntt)
    add_benchmark(benchmark_singlethread_rec_ntt)
    add_benchmark(benchmark_singlethread_naive_ntt)

endif()


include(CTest)

if(BUILD_TESTING)

    function(add_finitefield_test test_name)
        add_executable(
            ${test_name}
            tests/${test_name}.cpp
        )

        target_include_directories(
            ${test_name}
            PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

        target_link_libraries(
            ${test_name}
            PRIVATE
                finitefield
        )

        add_test(
            NAME ${test_name}
            COMMAND ${test_name}
        )
    endfunction()


    add_finitefield_test(test_mod_t)
    add_finitefield_test(test_lin_conv)
    add_finitefield_test(test_cyc_conv)
    add_finitefield_test(test_ncyc_conv)
    add_finitefield_test(test_ntt_naive_slow)
    add_finitefield_test(test_intt_naive_slow)
    add_finitefield_test(test_poly_eval)
    add_finitefield_test(test_ntt_naive_slow_multiply)
    add_finitefield_test(test_fast_recursive_ntt)
    add_finitefield_test(test_fast_iterative_ntt)
    add_finitefield_test(test_threaded_iterative_ntt)

endif()