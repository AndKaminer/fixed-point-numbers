#include <concepts>
#include <cstdint>

template <typename T>
struct Make {
  constexpr static T value(uint16_t whole, uint16_t frac) {return T{whole, frac};}
};

template <>
struct Make<float> {
  constexpr static float value(uint16_t whole, uint16_t frac) {
    return
      whole + 
      static_cast<float>(frac) / (frac < 10 ? 10 : (frac < 100 ? 100 : (frac < 1000 ? 1000 : 10000)));
  }
};

template <>
struct Make<uint32_t> {
  constexpr static uint32_t value(uint16_t whole, uint16_t frac) {
    return whole * 10000 + frac * (frac < 10 ? 1000 : (frac < 100 ? 100 : (frac < 1000 ? 10 : 1)));
  }
}

template <typename T>
concept RelaxedNumericConcept = std::three_way_comparable<T> && requires(T obj) {
  ++obj;
  obj + obj;
  obj - obj;
  obj * obj;
  obj / obj;
};
