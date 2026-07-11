#include "separate_ints.hpp"
#include "single_int.hpp"
#include "scaled_single_int.hpp"

#include <iostream>

int main() {
  separate_ints::fixed_point32_t a {100, 725};
  separate_ints::fixed_point32_t b {532, 3802};
  auto c {a + b};

  std::cout << a << " " << b << " " << c << std::endl;

  merged_ints::fixed_point32_t d {100, 725};
  merged_ints::fixed_point32_t e {532, 3802};
  auto f {d + e};

  std::cout << d << " " << e << " " << f << std::endl;

  scaled_int::fixed_point32_t<3> g {100, 725};
  scaled_int::fixed_point32_t<4> h {532, 3802};
  auto i {h + g};

  std::cout << g << " " << h << " " << i << std::endl;

}
