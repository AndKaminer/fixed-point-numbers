#include "include/separate_ints.hpp"
#include "include/single_int.hpp"
#include "include/scaled_single_int.hpp"

#include <benchmark/benchmark.h>

/**

int main() {
  separate_ints::fixed_point32_t a {100, 725};
  separate_ints::fixed_point32_t b {532, 3802};
  auto c {a + b};

  merged_ints::fixed_point32_t d {100, 725};
  merged_ints::fixed_point32_t e {532, 3802};
  auto f {d + e};

  scaled_int::fixed_point32_t<3> g {100, 725};
  scaled_int::fixed_point32_t<4> h {532, 3802};
  auto i {h + g};

}

**/

void BM_StringCopy(benchmark::State& state) {
  std::string x = "hello";
  for (auto _ : state)
    std::string copy(x);
}

void BM_StringMove(benchmark::State& state) {
  std::string x = "hello";
  for (auto _ : state) {
    std::string moved(std::move(x));
  }
}

BENCHMARK(BM_StringCopy);
BENCHMARK(BM_StringMove);

BENCHMARK_MAIN();
