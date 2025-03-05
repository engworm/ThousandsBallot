#ifndef POLY_BASE_HPP
#define POLY_BASE_HPP

#include <iostream>
#include <cstdint>
#include <vector>
#include "utility/log.hpp"

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T> || requires(T a, T b) {
    { a + b } -> std::same_as<T>;
};


template<Arithmetic T>
class PolyBase {
  private:
    uint32_t N; 
    std::vector<T> coeffs;

  protected:
    virtual void print(std::ostream &os) const;

  public:
    PolyBase();
    PolyBase(uint32_t N);
    PolyBase(const std::vector<T> &coeffs); 
    PolyBase(const PolyBase &poly) = delete;

    PolyBase(PolyBase &&poly) noexcept = default;

    template<Arithmetic U>
    PolyBase(PolyBase<U> &&poly) noexcept;

    void reset();

    uint32_t size() const;
    T operator[](const size_t i) const;
    T& operator[](const size_t i);
    std::vector<T> get_coeffs() const;

    template<Arithmetic U>
    friend std::ostream& operator<<(std::ostream &os, const PolyBase<U> &poly);
};

template<Arithmetic T>
void PolyBase<T>::print(std::ostream &os) const {
  for (auto coeff: coeffs) {
    os << coeff << ' ';
  }
}

template<Arithmetic T>
PolyBase<T>::PolyBase() = default;

template<Arithmetic T>
PolyBase<T>::PolyBase(uint32_t N) : N(N), coeffs(N, T(0)) {};

// 実質的にコピーコンストラクタになっているが，ベクトルの代入なので高速に動作する
// Optimized C++, p215
template<Arithmetic T>
PolyBase<T>::PolyBase(const std::vector<T> &coeffs) : coeffs(coeffs), N(coeffs.size()) {};

// reserveしてから末尾追加するため，高速に動作する
// 何度も呼ばれるため，実戦投入する際はパフォーマンスの評価が必要
// Optimized C++, p216
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
  poly.print(os);
  return os;
}

#endif