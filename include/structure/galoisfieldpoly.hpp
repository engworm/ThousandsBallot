#ifndef DISCRETE_TORUS_GALOISFIELD_POLY_HPP
#define DISCRETE_TORUS_GALOISFIELD_POLY_HPP

#include <iostream>
#include <vector>
#include <cstdint>
#include "params/nttparams.hpp"
#include "structure/galoisfield.hpp"
#include "structure/poly_base.hpp"
#include "structure/intpoly.hpp"

class DiscreteTorusPoly;

class GaloisFieldPoly : public PolyBase<GaloisFieldElement> {
  private:
    uint32_t P = NTTParams::P;

  private:
    void print(std::ostream &os) const override;

  public:
    GaloisFieldPoly() = default;
    GaloisFieldPoly(uint32_t P, uint32_t N);
    GaloisFieldPoly(const std::vector<GaloisFieldElement> &coeffs);
    
    GaloisFieldPoly(const IntPoly &poly) = delete;
    GaloisFieldPoly(const DiscreteTorusPoly &poly) = delete;
    GaloisFieldPoly(const GaloisFieldPoly &poly) = delete;

    GaloisFieldPoly(IntPoly &&poly) noexcept;
    GaloisFieldPoly(DiscreteTorusPoly &&poly) noexcept; 
    GaloisFieldPoly(GaloisFieldPoly &&poly) noexcept = default;

    std::vector<GaloisFieldElement> get_coeffs() const;
    uint32_t modulus() const;

    friend std::ostream& operator<<(std::ostream &os, const GaloisFieldPoly &poly);
};

#endif