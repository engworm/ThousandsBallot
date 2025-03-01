#ifndef MERSENNE_MODULUS_STRATEGY_HPP
#define MERSENNE_MODULUS_STRATEGY_HPP

#include <cstdint>
#include <memory>
#include "strategy/modulus_wrapper.hpp"

class MersenneModulusStrategy {
public:
  static uint32_t P;
  static uint32_t n;

  static uint32_t modulus(uint32_t x);
  static uint32_t modulus(uint64_t x);
};

#endif