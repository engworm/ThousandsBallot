#ifndef MODULUS_FACTORY_HPP
#define MODULUS_FACTORY_HPP

#include <cstdint>
#include <memory>
#include "strategy/modulus_strategy.hpp"
#include "strategy/mersenne_modulus_strategy.hpp"
#include "strategy/naive_modulus_strategy.hpp"
#include "utility/log.hpp"

template <typename ModulusStrategy>
class ModulusFactory {
public:
  static std::shared_ptr<ModulusStrategy> create(uint32_t P);
};

template <typename ModulusStrategy>
std::shared_ptr<ModulusStrategy> ModulusFactory<ModulusStrategy>::create(uint32_t P) {
#if defined(MODULUS_STRATEGY_MERSENNE)
  return MersenneModulusStrategy::getInstance(P);
#else
  return NaiveModulusStrategy::getInstance(P);
#endif
}


#endif