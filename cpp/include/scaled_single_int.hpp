#include <cstdint>
#include <ostream>

namespace scaled_int {

constexpr uint32_t pow10(uint8_t power) {
  uint32_t out {1};
  for (; power > 0; --power) {
    out *= 10;
  }

  return out;
}

template <uint8_t fractional_digits>
struct fixed_point32_t {
  static_assert(fractional_digits <= 9, "Error: 32 bit fixed point number can only have 9 (base 10) fractional digits");

  uint32_t num_ {0};

  constexpr fixed_point32_t(uint16_t whole, uint16_t frac) : 
    num_ ((static_cast<uint32_t>(whole) * pow10(fractional_digits)) + [frac]() -> uint32_t {
      if (frac == 0) {
        return 0;
      }

      uint32_t out {frac};

      while (out < pow10(fractional_digits - 1)) {
        out *= 10;
      }
      return out;
    }())
  {};
  constexpr explicit fixed_point32_t(uint32_t num) : num_(num) {}
  
  constexpr fixed_point32_t() = default;

  constexpr fixed_point32_t operator+(const fixed_point32_t other) const {
    return fixed_point32_t<fractional_digits>{num_ + other.num_};
  }

  constexpr fixed_point32_t operator-(const fixed_point32_t other) const {
    return fixed_point32_t<fractional_digits>{num_ - other.num_};
  }

  constexpr fixed_point32_t operator*(const fixed_point32_t other) const {
    return fixed_point32_t<fractional_digits>{static_cast<uint32_t>((static_cast<uint64_t>(num_) * static_cast<uint64_t>(other.num_)) / pow10(fractional_digits))};
  }

  constexpr fixed_point32_t operator+(const int other) const {
    return fixed_point32_t<fractional_digits>{num_ + other * pow10(fractional_digits)};
  }

  constexpr fixed_point32_t operator/(const fixed_point32_t other) const {
    return fixed_point32_t{static_cast<uint32_t>(static_cast<uint64_t>(num_) * pow10(fractional_digits) / static_cast<uint64_t>(other.num_))};
  }


  constexpr fixed_point32_t& operator++() {
    this->num_ += pow10(fractional_digits);
    return *this;
  }
  
  friend std::ostream& operator<<(std::ostream& os, const fixed_point32_t fp32) {
    os << fp32.num_ / pow10(fractional_digits) << "." << (fp32.num_ % pow10(fractional_digits));
    return os;
  }

};

};
