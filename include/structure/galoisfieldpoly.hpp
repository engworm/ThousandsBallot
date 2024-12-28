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
      DiscreteTorusPoly(const std::vector<DiscreteTorus> &coeffs) : PolyBase<DiscreteTorus>(coeffs) {
        this->N = coeffs.size();
      };

      DiscreteTorusPoly(const DiscreteTorusPoly &toruspoly) : PolyBase<DiscreteTorus>(toruspoly.get_coeffs()) {
        this->N = toruspoly.size();
      }

      DiscreteTorusPoly(const GaloisFieldPoly &poly);

      friend DiscreteTorusPoly operator*(const IntPoly& intpoly, const DiscreteTorusPoly &toruspoly) {

        if (intpoly.size() != toruspoly.N) {
          throw std::invalid_argument("Polynomial degree must be the same");
        }

        std::vector<DiscreteTorus> zero(toruspoly.N, DiscreteTorus(0));
        DiscreteTorusPoly result(zero);
        for (size_t i = 0; i < toruspoly.N; ++i) {
          for (size_t j = 0; j < toruspoly.N; ++j) {
            size_t k = (i + j) % toruspoly.N;
            if (i + j >= toruspoly.N) {
              result[k] -= intpoly[j]* toruspoly[i];
            }
            else {
              result[k] += intpoly[j] * toruspoly[i];
            }
          }
        }

        return result;
      }
  };
}

class GaloisFieldPoly : public PolyBase<GaloisFieldElement> {
  public:
    GaloisFieldPoly() = default;
    GaloisFieldPoly(const std::vector<GaloisFieldElement> &coeffs) : PolyBase<GaloisFieldElement>(coeffs) {
      this->N = coeffs.size();
    };
    
    GaloisFieldPoly(const IntPoly &poly) {
      this->N = poly.size();
      for (int i = 0; i < this->N; ++i) {
        std::vector<uint32_t> tmp = poly.get_coeffs(); 
        this->coeffs.emplace_back(GaloisFieldElement(poly[i]));
      }
    };

    GaloisFieldPoly(const galoisfieldpoly::DiscreteTorusPoly &poly) {
      this->N = poly.size();
      for (int i = 0; i < this->N; ++i) {
        std::vector<DiscreteTorus> tmp = poly.get_coeffs();
        this->coeffs.emplace_back(GaloisFieldElement(poly[i]));
      }
    };

    std::vector<GaloisFieldElement> get_coeffs() const { return coeffs; }

    friend GaloisFieldPoly operator*(const GaloisFieldPoly &poly1, const GaloisFieldPoly &poly2) {
      if (poly1.N != poly2.N) {
        Log::error("Polynomial degree must be the same");
      }
      std::cout << "mgmg" << std::endl;

      std::vector<GaloisFieldElement> zero(poly1.N, GaloisFieldElement(0));
      GaloisFieldPoly result(zero);
      std::cout << "NTT multiplication" << std::endl;
      std::cout << result.size() << std::endl;
      return result;
    }

    friend std::ostream& operator<<(std::ostream &os, const GaloisFieldPoly &poly) {
      for (auto coeff: poly.coeffs) {
        os << coeff << ' ';
      }
      return os;
    }
};

galoisfieldpoly::DiscreteTorusPoly::DiscreteTorusPoly(const GaloisFieldPoly &poly) {
  this->N = poly.size();
  for (int i = 0; i < this->N; ++i) {
    std::vector<GaloisFieldElement> tmp = poly.get_coeffs();
    this->coeffs.emplace_back(DiscreteTorus(poly[i]));
  }
}

#endif