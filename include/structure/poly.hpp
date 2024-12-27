#ifndef POLY_HPP
#define POLY_HPP

#include <iostream>
#include <cstdint>
#include <vector>
#include "params/params.hpp"

class Poly {
  private:
    uint32_t N{};
    std::vector<uint32_t> coeffs;

  protected:
    uint32_t& operator[](int i) { return coeffs[i]; }
  
  public:
    Poly(const std::vector<uint32_t> &coeffs) : coeffs(coeffs) {
      this->N = coeffs.size();
    };

    uint32_t size() const { return this->N; };
    uint32_t operator[](int i) const { return coeffs[i]; };
};

#endif