#include "modulus/mersenne_modulus.hpp"
#include "utility/log.hpp"

// MersenneModulusStrategy::MersenneModulusStrategy(uint32_t P) : P(P) {
  // this->n = 0;
  // uint32_t p = P;
  // while (p > 1) {
    // p >>= 1;
    // this->n++;
  // }
// };

uint32_t MersenneModulus::modulus(uint32_t x) {
  uint32_t result = (x & P) + (x >> n);
  return x & (P - 1);
}

uint32_t MersenneModulus::modulus(uint64_t x) {
  uint32_t result = (x & P) + (x >> n);
  return x & (P - 1);
}
