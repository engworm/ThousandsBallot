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
  int32_t r = (x << 18)%Consts::P; // (x*Consts::R)%Consts::P;
  return r;
}

uint32_t invReprMontgomery(uint32_t X) {
  uint32_t r = X + Consts::P*((Consts::mu*X) & 0x3FFFF);   // X + P*((mu*X)%R)
  return r >> 18;
}

uint32_t mulMontgomery(uint32_t X, uint32_t Y) {
  uint32_t c = X*Y;
  uint32_t r = c + Consts::P*((Consts::mu*c) & 0x3FFFF); // c + Consts::P*((Consts::mu*c)%Consts::R);
  return r >> 18;
}

uint32_t redcMontgomery(uint32_t x) {
  uint32_t q = Consts::mu*(x & 0x3FFFF) & 0x3FFFF; // Consts::mu*(x%Consts::R)%Consts::R;
  uint32_t r = (x + Consts::P*q) >> 18;
  if (r >= Consts::P) {
    r -= Consts::P;
  }
  return r;
}

#endif