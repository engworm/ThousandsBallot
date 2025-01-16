#include <iostream>
#include <cstdint>
#include <bit>
#include "params/params.hpp"
#include "operator/Montgomery.hpp"
#include "utility/extendedEuclidean.hpp"


// Compute μ = -P^{-1} mod R
uint32_t constMontgomeryMu() {
  int32_t r = extendedEuclidean(MontgomeryParams::R, Params::P).second;
  return (uint32_t)(MontgomeryParams::R - r);
}

uint32_t constMontgomeryR2() {
  uint64_t r2 = ((uint64_t)MontgomeryParams::R * MontgomeryParams::R);
  return r2 % Params::P;
}

uint32_t redcMontgomery(uint64_t x) {
  uint32_t q = MontgomeryParams::mu*(x & (MontgomeryParams::R-1)) & (MontgomeryParams::R-1); // mu*(x%R)%R;
  uint32_t r = (x + Params::P*q) >> std::countr_zero(MontgomeryParams::R);
  if (r >= Params::P) {
    r -= Params::P;
  }
  return r;
}

uint32_t mulMontgomery(uint32_t X, uint32_t Y) {
  uint32_t r = redcMontgomery((uint64_t)X*Y);
  return r;
}

uint32_t reprMontgomery(uint32_t x) {
  return mulMontgomery(x, MontgomeryParams::R2);
}

uint32_t invReprMontgomery(uint32_t X) {
  return mulMontgomery(X, 1);
}

