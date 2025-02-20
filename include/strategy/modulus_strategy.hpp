#ifndef MODULUS_STRATEGY_HPP
#define MODULUS_STRATEGY_HPP

#include <cstdint>
#include <memory>

class ModulusStrategy {
public:
  virtual ~ModulusStrategy() = default;
  virtual uint32_t modulus(uint32_t x) const = 0;
};

#endif