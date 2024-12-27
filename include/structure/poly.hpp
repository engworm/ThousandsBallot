#ifndef POLY_HPP
#define POLY_HPP

#include <iostream>
#include <cstdint>
#include <vector>
#include "params/params.hpp"

class Poly {
  public:
    uint32_t N{};
    std::vector<uint32_t> coeffs;
    uint32_t& operator[](int i) { return coeffs[i]; }
  
  public:
    Poly() = default;
    Poly(const std::vector<uint32_t> &coeffs) : coeffs(coeffs) {
      this->N = coeffs.size();
    };

    uint32_t size() const { return this->N; };
    uint32_t operator[](int i) const { return coeffs[i]; };
    std::vector<uint32_t> get_coeffs() const { return coeffs; }
};

#endif