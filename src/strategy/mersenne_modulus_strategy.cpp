#include "strategy/mersenne_modulus_strategy.hpp"
#include "utility/log.hpp"

MersenneModulusStrategy::MersenneModulusStrategy(uint32_t P) : P(P) {
  this->n = 0;
  uint32_t p = P;
  while (p > 1) {
    p >>= 1;
    this->n++;
  }
};

std::shared_ptr<MersenneModulusStrategy> MersenneModulusStrategy::getInstance(uint32_t P) {
  return std::shared_ptr<MersenneModulusStrategy>(new MersenneModulusStrategy(P));
}

uint32_t MersenneModulusStrategy::modulus(uint32_t x) const {
  uint32_t result = (x & this->P) + (x >> this->n);
  return x & (this->P - 1);
}

uint32_t MersenneModulusStrategy::modulus(uint64_t x) const {
  uint32_t result = (x & this->P) + (x >> this->n);
  return x & (this->P - 1);
}
