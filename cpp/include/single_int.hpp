#include <cstdint>
#include <ostream>

namespace merged_ints {

struct fixed_point32_t {
  uint32_t num_ {0};

  constexpr fixed_point32_t(uint16_t whole, uint16_t frac) : 
    num_ ((static_cast<uint32_t>(whole) * 10000) + (frac < 10 ? frac * 1000 : (frac < 100 ? frac * 100 : (frac < 1000 ? frac * 10: frac))))
  {};

  constexpr explicit fixed_point32_t(uint32_t num) : num_(num) {}
  
  fixed_point32_t() = delete;

  constexpr fixed_point32_t operator+(const fixed_point32_t other) const {
    return fixed_point32_t{num_ + other.num_};
  }

  fixed_point32_t& operator++() {
    this->num_ += 10000;
    return *this;
  }

  constexpr fixed_point32_t operator+(int other) {
    return fixed_point32_t(num_ + other * 10000);
  }

  friend std::ostream& operator<<(std::ostream& os, const fixed_point32_t fp32) {
    os << fp32.num_ / 10000 << "." << (fp32.num_ % 10000);
    return os;
  }

};

};
