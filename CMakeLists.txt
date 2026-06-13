cmake_minimum_required(VERSION 3.20)

project(finitefield LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(finitefield INTERFACE)
target_include_directories(finitefield INTERFACE include)

add_executable(test_mod_t tests/test_mod_t.cpp)

target_include_directories(test_mod_t PRIVATE
    src/doctest
)

target_link_libraries(test_mod_t PRIVATE finitefield)

enable_testing()
add_test(NAME test_mod_t COMMAND test_mod_t)