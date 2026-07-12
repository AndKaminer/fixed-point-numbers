#include <cstdint>
#include <ostream>

namespace separate_ints {

struct fixed_point32_t {
  uint16_t whole_ {0};
  uint16_t frac_ {0};

  constexpr fixed_point32_t(uint16_t whole, uint16_t frac) {
    if (frac < 10) {
      frac *= 1000;
    } else if (frac < 100) {
      frac *= 100;
    } else if (frac < 1000) {
      frac *= 10;
    }

    whole_ = whole;
    frac_ = frac;
  }
  
  fixed_point32_t() = delete;

  constexpr fixed_point32_t operator+(const fixed_point32_t other) const {
    uint16_t new_whole {static_cast<uint16_t>(whole_ + other.whole_ + (frac_ + other.frac_ < 10000 ? 1 : 0))};
    return {new_whole, static_cast<uint16_t>((frac_ + other.frac_) % 10000)};
  }

  friend std::ostream& operator<<(std::ostream& os, const fixed_point32_t fp32) {
    os << fp32.whole_ << "." << (fp32.frac_ % 10000);
    return os;
  }

};

};
