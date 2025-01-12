#ifndef DISCRETE_TORUS_GALOISFIELD_POLY_HPP
#define DISCRETE_TORUS_GALOISFIELD_POLY_HPP

#include <iostream>
#include <cstdint>
#include <vector>
#include "params/params.hpp"
#include "structure/torus.hpp"
#include "structure/galoisfield.hpp"
#include "structure/poly_base.hpp"
#include "structure/intpoly.hpp"
#include "utility/log.hpp"

class DiscreteTorusPoly;

class GaloisFieldPoly : public PolyBase<GaloisFieldElement> {
  public:
    GaloisFieldPoly(const std::vector<GaloisFieldElement> &coeffs);
    
    GaloisFieldPoly(const IntPoly &poly) = delete;
    GaloisFieldPoly(const DiscreteTorusPoly &poly) = delete;

    GaloisFieldPoly(IntPoly &&poly) noexcept;
    GaloisFieldPoly(DiscreteTorusPoly &&poly) noexcept;

  protected:
    void print(std::ostream &os) const override;

  friend std::ostream& operator<<(std::ostream &os, const GaloisFieldPoly &poly);
};
GaloisFieldPoly operator*(const GaloisFieldPoly &poly1, const GaloisFieldPoly &poly2);

#endif