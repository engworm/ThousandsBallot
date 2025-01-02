#ifndef POLY_BASE_HPP
#define POLY_BASE_HPP

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
    uint32_t N = NttParams::N;
    std::vector<T> coeffs;
  
  public:
    PolyBase();
    PolyBase(const std::vector<T> &coeffs); 

    uint32_t size() const;
    T operator[](int i) const;
    T& operator[](int i);
    std::vector<T> get_coeffs() const;

    template<Arithmetic U>
    friend std::ostream& operator<<(std::ostream &os, const PolyBase<U> &poly);
};

#include "structure/poly_base.tpp"

#endif