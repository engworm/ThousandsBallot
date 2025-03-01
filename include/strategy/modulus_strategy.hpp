#ifndef MODULUS_STRATEGY_HPP
#define MODULUS_STRATEGY_HPP

#include <cstdint>
#include <memory>

template <typename T>
class ModulusStrategy {
public:
  static uint32_t modulus(uint32_t x);
  static uint32_t modulus(uint64_t x);
};

#endif