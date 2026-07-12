#include "separate_ints.hpp"
#include "single_int.hpp"
#include "scaled_single_int.hpp"

#include <benchmark/benchmark.h>
#include <vector>

void BM_Separate(benchmark::State& state) {
  std::vector<separate_ints::fixed_point32_t> vec {};
  separate_ints::fixed_point32_t a {};

  for (auto _ : state) {
    benchmark::DoNotOptimize(vec);
    vec.push_back(a);
    ++a;
  }
}

void BM_Merged(benchmark::State& state) {
  std::vector<merged_ints::fixed_point32_t> vec {};
  merged_ints::fixed_point32_t a {};

  for (auto _ : state) {
    benchmark::DoNotOptimize(vec);
    vec.push_back(a);
    ++a;
  }
}

void BM_Scaled(benchmark::State& state) {
  std::vector<scaled_int::fixed_point32_t<5>> vec {};
  scaled_int::fixed_point32_t<5> a {};

  for (auto _ : state) {
    benchmark::DoNotOptimize(vec);
    vec.push_back(a);
    ++a;
  }
}

void BM_Integer(benchmark::State& state) {
  std::vector<int> vec {};
  int a {};

  for (auto _ : state) {
    benchmark::DoNotOptimize(vec);
    vec.push_back(a);
    ++a;
  }
}

void BM_Float(benchmark::State& state) {
  std::vector<float> vec {};
  float a {};

  for (auto _ : state) {
    benchmark::DoNotOptimize(vec);
    vec.push_back(a);
    ++a;
  }
}

BENCHMARK(BM_Integer);
BENCHMARK(BM_Float);
BENCHMARK(BM_Separate);
BENCHMARK(BM_Merged);
BENCHMARK(BM_Scaled);

BENCHMARK_MAIN();
