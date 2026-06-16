cmake_minimum_required(VERSION 3.20)

project(finitefield LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(finitefield INTERFACE)
target_include_directories(finitefield INTERFACE include)

add_executable(test_mod_t tests/test_mod_t.cpp)
add_executable(test_lin_conv tests/test_lin_conv.cpp)
add_executable(test_cyc_conv tests/test_cyc_conv.cpp)
add_executable(test_ncyc_conv tests/test_ncyc_conv.cpp)
add_executable(test_ntt_naive_slow tests/test_ntt_naive_slow.cpp)
add_executable(test_intt_naive_slow tests/test_intt_naive_slow.cpp)

target_include_directories(test_mod_t PRIVATE src)
target_include_directories(test_lin_conv PRIVATE src)
target_include_directories(test_cyc_conv PRIVATE src)
target_include_directories(test_ncyc_conv PRIVATE src)
target_include_directories(test_ntt_naive_slow PRIVATE src)
target_include_directories(test_intt_naive_slow PRIVATE src)

target_link_libraries(test_mod_t PRIVATE finitefield)
target_link_libraries(test_lin_conv PRIVATE finitefield)
target_link_libraries(test_cyc_conv PRIVATE finitefield)
target_link_libraries(test_ncyc_conv PRIVATE finitefield)
target_link_libraries(test_ntt_naive_slow PRIVATE finitefield)
target_link_libraries(test_intt_naive_slow PRIVATE finitefield)

enable_testing()

add_test(NAME test_mod_t COMMAND test_mod_t)
add_test(NAME test_lin_conv COMMAND test_lin_conv)
add_test(NAME test_cyc_conv COMMAND test_cyc_conv)
add_test(NAME test_ncyc_conv COMMAND test_ncyc_conv)
add_test(NAME test_ntt_naive_slow COMMAND test_ntt_naive_slow)
add_test(NAME test_intt_naive_slow COMMAND test_intt_naive_slow)