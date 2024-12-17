#include <iostream>
#include <cstdint>
#include "params/params.hpp"

#ifndef MONTGOMERY_HPP
#define MONTGOMERY_HPP

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
uint32_t constMontgomery() {
  int32_t r = extendedEuclidean(Consts::R, Consts::P).second;
  return (uint32_t)(Consts::R - r);
}

uint32_t reprMontgomery(uint32_t x) {
  int32_t r = (x*Consts::R)%Consts::P;
  return r;
}

uint32_t invReprMontgomery(uint32_t x) {
  uint32_t r = x + Consts::P*((Consts::mu*x)%Consts::R);
  return r/Consts::R;
}

uint32_t mulMontgomery(uint32_t a, uint32_t b) {
  uint32_t c = a*b;
  int32_t r = (c + Consts::P*((Consts::mu*c)%Consts::R))/Consts::R;
  return r;
}

#endif