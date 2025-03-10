#ifndef DISCRETE_TORUS_GALOISFIELD_HPP
#define DISCRETE_TORUS_GALOISFIELD_HPP

#include <iostream>
#include <cstdint>
#include <random>
#include "params/nttparams.hpp"
#include "operator/Montgomery.hpp"

class DiscreteTorus;

class GaloisFieldElement {
  private:
    uint32_t a{};
    uint32_t P = NTTParams::P;

  public:
    GaloisFieldElement(); 

    GaloisFieldElement(const GaloisFieldElement &a);
    GaloisFieldElement(const uint32_t &x);
    GaloisFieldElement(const DiscreteTorus &t);

    GaloisFieldElement(uint32_t &&x) noexcept;
    GaloisFieldElement(GaloisFieldElement &&a) noexcept;

    uint32_t val() const;

    void operator+=(const GaloisFieldElement &b);
    void operator-=(const GaloisFieldElement &a);
    void operator*=(const GaloisFieldElement &b);

    GaloisFieldElement& operator=(const GaloisFieldElement& other);

    GaloisFieldElement& operator=(GaloisFieldElement&& other) noexcept;


    friend std::ostream& operator<<(std::ostream &os, const GaloisFieldElement &a);
};

bool operator==(const GaloisFieldElement &a1, const GaloisFieldElement&a2);
GaloisFieldElement operator+(const GaloisFieldElement &a, const GaloisFieldElement &b);
GaloisFieldElement operator-(const GaloisFieldElement &a, const GaloisFieldElement &b);
GaloisFieldElement operator*(const GaloisFieldElement a, const GaloisFieldElement &b);


#endif