#include <algorithm>
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

  constexpr fixed_point32_t operator-(const fixed_point32_t other) const {
    const uint16_t frac_diff {static_cast<uint16_t>(std::max(frac_, other.frac_) - std::min(frac_, other.frac_))};
    return {
      static_cast<uint16_t>(whole_ - other.whole_ - (frac_ >= other.frac_ ? 0 : 1)),
      static_cast<uint16_t>(frac_ >= other.frac_ ? frac_diff : 10000 - frac_diff)};
  }

  constexpr fixed_point32_t operator+(const int other) const {
    return {
      static_cast<uint16_t>(whole_ + other),
      frac_
    };
  }

  constexpr bool operator<(const fixed_point32_t other) const {
    if (whole_ != other.whole_) {
      return whole_ < other.whole_;
    }

    return frac_ < other.frac_;
  }

  constexpr bool operator==(const fixed_point32_t other) const {
    return whole_ == other.whole_ and frac_ == other.frac_;
  }

  constexpr bool operator>(const fixed_point32_t other) const {
    if (whole_ != other.whole_) {
      return whole_ > other.whole_;
    }

    return frac_ > other.frac_;
  }

  constexpr fixed_point32_t operator*(const fixed_point32_t other) const {
    uint32_t a {static_cast<uint32_t>(whole_ * other.whole_)};
    uint32_t b {static_cast<uint32_t>(whole_ * other.frac_)};
    uint32_t c {static_cast<uint32_t>(frac_ * other.whole_)};
    uint32_t d {static_cast<uint32_t>(frac_ * other.frac_)}; // 10000 * 10000
    return { 
      static_cast<uint16_t>(a + (b / 10000) + (c / 10000) + (d / 100000000)),
      static_cast<uint16_t>((b % 10000) + (c % 10000) + (d % 100000000))
    };
  }

  constexpr fixed_point32_t operator/(const fixed_point32_t other) const {
    // (a1 + a2 / 10000) / (b1 + b2 / 10000)
    // = a1 / (b1 + b2 / 10000) + a2 / (b1 + b2 / 10000)
    // = 10000 * a1 / (10000 * b1 + b2) + ...
    uint64_t numer {(static_cast<uint64_t>(10000) * whole_ + frac_) * 10000};
    uint32_t denom {static_cast<uint32_t>(10000) * other.whole_ + other.frac_};
    uint32_t out {static_cast<uint32_t>(numer / denom)};
    return {
      static_cast<uint16_t>(out / 10000),
      static_cast<uint16_t>(out % 10000)
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
