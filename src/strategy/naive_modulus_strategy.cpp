#include "strategy/naive_modulus_strategy.hpp"

NaiveModulusStrategy::NaiveModulusStrategy(uint32_t P) : P(P) {};

std::shared_ptr<NaiveModulusStrategy> NaiveModulusStrategy::getInstance(uint32_t P) {
  return std::shared_ptr<NaiveModulusStrategy>(new NaiveModulusStrategy(P));
}

uint32_t NaiveModulusStrategy::modulus(uint32_t x) const {
  return x % this->P;
}

uint32_t NaiveModulusStrategy::modulus(uint64_t x) const {
  return x % this->P;
}

