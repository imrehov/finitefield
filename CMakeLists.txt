cmake_minimum_required(VERSION 3.20)

project(finitefield LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(finitefield INTERFACE)
target_include_directories(finitefield INTERFACE include)

add_executable(test_mod_t tests/test_mod_t.cpp)
add_executable(test_lin_conv tests/test_lin_conv.cpp)
add_executable(test_cyc_conv tests/test_cyc_conv.cpp)

target_include_directories(test_mod_t PRIVATE src)
target_include_directories(test_lin_conv PRIVATE src)
target_include_directories(test_cyc_conv PRIVATE src)

target_link_libraries(test_mod_t PRIVATE finitefield)
target_link_libraries(test_lin_conv PRIVATE finitefield)
target_link_libraries(test_cyc_conv PRIVATE finitefield)

enable_testing()

add_test(NAME test_mod_t COMMAND test_mod_t)
add_test(NAME test_lin_conv COMMAND test_lin_conv)
add_test(NAME test_cyc_conv COMMAND test_cyc_conv)