#include "separate_ints.hpp"
#include "single_int.hpp"
#include "scaled_single_int.hpp"

#include <benchmark/benchmark.h>
#include <cstdint>

void BM_Separate(benchmark::State& state) {
  separate_ints::fixed_point32_t a {100, 725};
  separate_ints::fixed_point32_t b {532, 3802};
  for (auto _ : state) {
    benchmark::DoNotOptimize(a);
    benchmark::DoNotOptimize(b);

    auto c = a + b;

    benchmark::DoNotOptimize(c);
    ++a;
  }
}

void BM_Merged(benchmark::State& state) {
  merged_ints::fixed_point32_t a {100, 725};
  merged_ints::fixed_point32_t b {532, 3802};
  for (auto _ : state) {
    benchmark::DoNotOptimize(a);
    benchmark::DoNotOptimize(b);

    auto c = a + b;

    benchmark::DoNotOptimize(c);
    ++a;
  }
}

void BM_Scaled(benchmark::State& state) {
  scaled_int::fixed_point32_t<4> a {100, 725};
  scaled_int::fixed_point32_t<4> b {532, 3802};
  for (auto _ : state) {
    benchmark::DoNotOptimize(a);
    benchmark::DoNotOptimize(b);

    auto c = a + b;

    benchmark::DoNotOptimize(c);
    ++a;
  }
}

void BM_Integer(benchmark::State& state) {
  uint32_t a {100725};
  uint32_t b {5323802};
  for (auto _ : state) {
    benchmark::DoNotOptimize(a);
    benchmark::DoNotOptimize(b);

    auto c = a + b;

    benchmark::DoNotOptimize(c);
    ++a;
  }
}

void BM_Float(benchmark::State& state) {
  float a {100.725};
  float b {532.3802};
  for (auto _ : state) {
    benchmark::DoNotOptimize(a);
    benchmark::DoNotOptimize(b);

    auto c = a + b;

    benchmark::DoNotOptimize(c);
    ++a;
  }
}

BENCHMARK(BM_Integer);
BENCHMARK(BM_Float);
BENCHMARK(BM_Separate);
BENCHMARK(BM_Merged);
BENCHMARK(BM_Scaled);

BENCHMARK_MAIN();
