cmake_minimum_required(VERSION 3.20)

project(finitefield LANGUAGES CXX)


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

endif()