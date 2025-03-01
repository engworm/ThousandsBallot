#ifndef MODULUS_WRAPPER_HPP
#define MODULUS_WRAPPER_HPP

#include <cstdint>
#include <memory>

template <typename T>
class ModulusWrapper{
public:
  static uint32_t modulus(uint32_t x) {
    return T::modulus(x);
  }

  static uint32_t modulus(uint64_t x) {
    return T::modulus(x);
  }
};

#endif