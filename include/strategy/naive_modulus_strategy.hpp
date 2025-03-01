#ifndef NAIVE_MODULUS_STRATEGY_HPP
#define NAIVE_MODULUS_STRATEGY_HPP

#include <cstdint>
#include <memory>
#include "strategy/modulus_strategy.hpp"

class NaiveModulusStrategy {
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