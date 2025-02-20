#ifndef MERSENNE_MODULUS_STRATEGY_HPP
#define MERSENNE_MODULUS_STRATEGY_HPP

#include <cstdint>
#include <memory>
#include "strategy/modulus_strategy.hpp"

class MersenneModulusStrategy : public ModulusStrategy {
private:
  uint32_t P;
  uint32_t n;
  MersenneModulusStrategy(uint32_t P);
public:
  static std::shared_ptr<MersenneModulusStrategy> getInstance(uint32_t P);
  uint32_t modulus(uint32_t x) const override;
  uint32_t modulus(uint64_t x) const;
};

#endif