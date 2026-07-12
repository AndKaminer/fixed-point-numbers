cmake_minimum_required(VERSION 3.14)
project(FixedPoint CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(cpp/third_party/benchmark)

add_executable(addition_benchmark cpp/benchmarks/addition.cpp)
target_include_directories(addition_benchmark PRIVATE cpp/include)
target_link_libraries(addition_benchmark PRIVATE benchmark::benchmark)

add_executable(vector_benchmark cpp/benchmarks/vector.cpp)
target_include_directories(vector_benchmark PRIVATE cpp/include)
target_link_libraries(vector_benchmark PRIVATE benchmark::benchmark)
