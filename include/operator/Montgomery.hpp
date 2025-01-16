#ifndef MONTGOMERY_HPP
#define MONTGOMERY_HPP

#include <iostream>
#include <cstdint>
#include <bit>
#include "params/params.hpp"

uint32_t constMontgomeryMu();
uint32_t constMontgomeryR2();
uint32_t redcMontgomery(uint64_t x);
uint32_t mulMontgomery(uint32_t X, uint32_t Y);
uint32_t reprMontgomery(uint32_t x);
uint32_t invReprMontgomery(uint32_t X);

#endif