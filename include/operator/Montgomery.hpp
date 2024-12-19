#ifndef MONTGOMERY_HPP
#define MONTGOMERY_HPP

#include <iostream>
#include <cstdint>
#include <bit>
#include "params/params.hpp"

std::pair<int32_t, int32_t> extendedEuclidean(uint32_t a, uint32_t b) {
  if (b==0) {
    return std::pair<int32_t, int32_t> (1, 0);
  }
  std::pair<int32_t, int32_t> r = extendedEuclidean(b, a%b);
  int32_t s = r.first;
  int32_t t = r.second;
  return std::pair<int32_t, int32_t> (t, s - t*(a/b));
}

// Compute μ = -P^{-1} mod R
uint32_t constMontgomeryMu() {
  int32_t r = extendedEuclidean(Consts::R, Consts::P).second;
  return (uint32_t)(Consts::R - r);
}

uint32_t constMontgomeryR2() {
  uint64_t r2 = ((uint64_t)Consts::R * Consts::R);
  return r2 % Consts::P;
}

uint32_t redcMontgomery(uint64_t x) {
  uint32_t q = Consts::mu*(x & (Consts::R-1)) & (Consts::R-1); // mu*(x%R)%R;
  uint32_t r = (x + Consts::P*q) >> std::countr_zero(Consts::R);
  if (r >= Consts::P) {
    r -= Consts::P;
  }
  return r;
}

uint32_t mulMontgomery(uint32_t X, uint32_t Y) {
  uint32_t r = redcMontgomery((uint64_t)X*Y);
  return r;
}

uint32_t reprMontgomery(uint32_t x) {
  return mulMontgomery(x, Consts::R2);
}

uint32_t invReprMontgomery(uint32_t X) {
  return mulMontgomery(X, 1);
}


#endif