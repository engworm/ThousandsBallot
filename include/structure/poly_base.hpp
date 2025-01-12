#ifndef POLY_BASE_HPP
#define POLY_BASE_HPP

#include <iostream>
#include <cstdint>
#include <vector>
#include "params/nttparams.hpp"
#include "structure/galoisfield.hpp"

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T> || requires(T a, T b) {
    { a + b } -> std::same_as<T>;
};


template<Arithmetic T>
class PolyBase {
  protected:
    uint32_t N = NttParams::N;
    std::vector<T> coeffs;

  public:
    PolyBase();
    PolyBase(const std::vector<T> &coeffs); 

    PolyBase(PolyBase &&poly) noexcept;

    template<Arithmetic U>
    PolyBase(PolyBase<U> &&poly) noexcept;

    void reset();

    uint32_t size() const;
    T operator[](const size_t i) const;
    T& operator[](const size_t i);
    std::vector<T> get_coeffs() const;

    friend std::ostream& operator<< <>(std::ostream &os, const PolyBase<T> &poly);
};

template<Arithmetic T>
PolyBase<T>::PolyBase() = default;

template<Arithmetic T>
PolyBase<T>::PolyBase(const std::vector<T> &coeffs) : coeffs(coeffs) {
  this->N = coeffs.size();
}

template<Arithmetic T>
PolyBase<T>::PolyBase(PolyBase &&poly) noexcept
    : coeffs(std::move(poly.coeffs)) {
    this->N = poly.size();
}

template<Arithmetic T>
template<Arithmetic U>
PolyBase<T>::PolyBase(PolyBase<U> &&poly) noexcept {
  this->N = poly.size();
  this->coeffs.reserve(poly.size());
  for (int i = 0; i < poly.size(); ++i) {
      this->coeffs.emplace_back(std::move(poly[i]));
  }
  poly.reset();
}

template<Arithmetic T>
void PolyBase<T>::reset() {
  this->N = 0;
  std::vector<T>().swap(this->coeffs);
} 

template<Arithmetic T>
uint32_t PolyBase<T>::size() const {
  return this->N;
}

template<Arithmetic T>
T PolyBase<T>::operator[](const size_t i) const {
  return coeffs[i];
}

template<Arithmetic T>
T& PolyBase<T>::operator[](const size_t i) {
  return coeffs[i];
}

template<Arithmetic T>
std::vector<T> PolyBase<T>::get_coeffs() const {
  return coeffs;
}

template<Arithmetic T>
std::ostream& operator<<(std::ostream &os, const PolyBase<T> &poly) {
  for (auto coeff: poly.get_coeffs()) {
    os << coeff << ' ';
  }
  return os;
}

template class PolyBase<uint32_t>;
template class PolyBase<GaloisFieldElement>;
template PolyBase<GaloisFieldElement>::PolyBase(PolyBase<uint32_t> &&poly) noexcept;

#endif