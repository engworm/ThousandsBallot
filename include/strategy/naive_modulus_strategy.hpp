#ifndef NAIVE_MODULUS_STRATEGY_HPP
#define NAIVE_MODULUS_STRATEGY_HPP

#include <cstdint>
#include <memory>
#include "strategy/modulus_strategy.hpp"

class NaiveModulusStrategy : public ModulusStrategy {
private:
  uint32_t P;
  NaiveModulusStrategy(uint32_t P);
public:
  static std::shared_ptr<NaiveModulusStrategy> getInstance(uint32_t P);
  uint32_t modulus(uint32_t x) const override;
  uint32_t modulus(uint64_t x) const override;
};

#endif