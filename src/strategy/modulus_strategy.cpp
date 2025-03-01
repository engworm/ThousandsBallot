#include "strategy/modulus_strategy.hpp"
#include "strategy/naive_modulus_strategy.hpp"

template <>
uint32_t ModulusStrategy<NaiveModulusStrategy>::modulus(uint32_t x) {
  return NaiveModulusStrategy::modulus(x);
}

template <>
uint32_t ModulusStrategy<NaiveModulusStrategy>::modulus(uint64_t x) {
  return NaiveModulusStrategy::modulus(x);
}