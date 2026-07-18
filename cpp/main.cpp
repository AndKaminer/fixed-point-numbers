#include "include/separate_ints.hpp"
#include "include/single_int.hpp"
#include "include/scaled_single_int.hpp"
#include <iostream>

int main() {
  separate_ints::fixed_point32_t a {100, 725};
  separate_ints::fixed_point32_t b {532, 3802};
  std::cout << a + b << std::endl;
  std::cout << a * b << std::endl;


  merged_ints::fixed_point32_t d {100, 725};
  merged_ints::fixed_point32_t e {532, 3802};
  std::cout << d + e << std::endl;
  std::cout << d * e << std::endl;


  scaled_int::fixed_point32_t<3> g {100, 725};
  scaled_int::fixed_point32_t<4> h {532, 3802};
  std::cout << h + g << std::endl;
  std::cout << h * g << std::endl;

}
