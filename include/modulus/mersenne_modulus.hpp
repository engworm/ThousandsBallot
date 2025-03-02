#ifndef MERSENNE_MODULUS_HPP
#define MERSENNE_MODULUS_HPP

#include <cstdint>
#include <memory>
#include "modulus/modulus_wrapper.hpp"

class MersenneModulus {
public:
  static uint32_t P;
  static uint32_t n;

  static uint32_t modulus(uint32_t x);
  static uint32_t modulus(uint64_t x);
};

#endif