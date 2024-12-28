#ifndef POLY_HPP
#define POLY_HPP

#include <iostream>
#include <cstdint>
#include <vector>
#include "params/params.hpp"

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T> || requires(T a, T b) {
    { a + b } -> std::same_as<T>;
};


template<Arithmetic T>
class PolyBase {
  protected:
    uint32_t N{};
    std::vector<T> coeffs;
    T& operator[](int i) { return coeffs[i]; }
  
  public:
    PolyBase() = default;
    PolyBase(const std::vector<T> &coeffs) : coeffs(coeffs) {
      this->N = coeffs.size();
    };

    uint32_t size() const { return this->N; };
    T operator[](int i) const { return coeffs[i]; };
    std::vector<T> get_coeffs() const { return coeffs; }

    friend std::ostream& operator<<(std::ostream &os, const PolyBase &poly) {
      for (auto coeff: poly.get_coeffs()) {
        os << coeff << ' ';
      }
      return os;
    }
};

#endif