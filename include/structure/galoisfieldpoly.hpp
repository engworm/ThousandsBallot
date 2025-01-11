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

class GaloisFieldPoly;

namespace galoisfieldpoly {
  class DiscreteTorusPoly : public PolyBase<DiscreteTorus> {
    public:
      DiscreteTorusPoly(const std::vector<DiscreteTorus> &coeffs);
      DiscreteTorusPoly(const DiscreteTorusPoly &toruspoly);
      DiscreteTorusPoly(const GaloisFieldPoly &poly);

      friend std::ostream& operator<<(std::ostream &os, const DiscreteTorusPoly &poly);
  };
  DiscreteTorusPoly operator*(const IntPoly& intpoly, const DiscreteTorusPoly &toruspoly);
}

class GaloisFieldPoly : public PolyBase<GaloisFieldElement> {
  public:
    GaloisFieldPoly(const std::vector<GaloisFieldElement> &coeffs);
    
    GaloisFieldPoly(const IntPoly &poly) = delete;
    GaloisFieldPoly(const galoisfieldpoly::DiscreteTorusPoly &poly) = delete;

    GaloisFieldPoly(IntPoly &&poly) noexcept;
    GaloisFieldPoly(galoisfieldpoly::DiscreteTorusPoly &&poly) noexcept;

    friend std::ostream& operator<<(std::ostream &os, const GaloisFieldPoly &poly);
};

GaloisFieldPoly operator*(const GaloisFieldPoly &poly1, const GaloisFieldPoly &poly2);

#endif