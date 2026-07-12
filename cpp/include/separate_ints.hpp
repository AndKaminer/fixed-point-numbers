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
  
  constexpr fixed_point32_t() = default;

  constexpr fixed_point32_t operator+(const fixed_point32_t other) const {
    uint32_t frac = frac_ + other.frac_;
    uint16_t carry = frac >= 10000;

    return {
        static_cast<uint16_t>(whole_ + other.whole_ + carry),
        static_cast<uint16_t>(carry ? frac - 10000 : frac)
    };
  }

  constexpr fixed_point32_t operator+(const int other) const {
    return {
      static_cast<uint16_t>(whole_ + other),
      frac_
    };
  }

  fixed_point32_t& operator++() {
    this->whole_++;
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const fixed_point32_t fp32) {
    os << fp32.whole_ << "." << (fp32.frac_ % 10000);
    return os;
  }

};

};
