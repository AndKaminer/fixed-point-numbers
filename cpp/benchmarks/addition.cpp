#include "benchmark/utils.h"
#include "separate_ints.hpp"
#include "single_int.hpp"
#include "scaled_single_int.hpp"

#include "fixed_point_util.hpp"

#include <benchmark/benchmark.h>
#include <cstdint>

template <typename T>
void bench(benchmark::State& state) {
  auto a {util::Make<T>::value(100, 725)};
  auto b {util::Make<T>::value(532, 3802)};
  for (auto _ : state) {
    benchmark::DoNotOptimize(a = a + b);
  }

}

void BM_Separate(benchmark::State& state) {
  bench<separate_ints::fixed_point32_t>(state);
}

void BM_Merged(benchmark::State& state) {
  bench<merged_ints::fixed_point32_t>(state);
}

void BM_Scaled(benchmark::State& state) {
  bench<scaled_int::fixed_point32_t<4>>(state);
}

void BM_Integer(benchmark::State& state) {
  bench<uint32_t>(state);
}

void BM_Float(benchmark::State& state) {
  bench<float>(state);
}

BENCHMARK(BM_Integer);
BENCHMARK(BM_Float);
BENCHMARK(BM_Separate);
BENCHMARK(BM_Merged);
BENCHMARK(BM_Scaled);

BENCHMARK_MAIN();
