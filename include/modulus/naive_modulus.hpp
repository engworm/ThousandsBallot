#ifndef NAIVE_MODULUS_HPP
#define NAIVE_MODULUS_HPP

#include <cstdint>
#include <memory>
#include "modulus/modulus_wrapper.hpp"

class NaiveModulus {
public:
  static uint32_t q;

  static uint32_t modulus(uint32_t x) {
    return x % q;
  }

  static uint32_t modulus(uint64_t x) {
    return x % q;
  }
};

#endif