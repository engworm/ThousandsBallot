#ifndef TORUS_POLY_HPP
#define TORUS_POLY_HPP

#include <iostream>
#include <cstdint>
#include <vector>
#include "params/params.hpp"
#include "structure/torus.hpp"
#include "structure/poly.hpp"
#include "structure/int_poly.hpp"

class DiscreteTorusPoly : public PolyBase<DiscreteTorus> {
  public:
    DiscreteTorusPoly(const std::vector<DiscreteTorus> &coeffs) : PolyBase<DiscreteTorus>(coeffs) {
      this->N = coeffs.size();
    };

    DiscreteTorusPoly(const DiscreteTorusPoly &toruspoly) : PolyBase<DiscreteTorus>(toruspoly.get_coeffs()) {
      this->N = toruspoly.size();
     }

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

      return std::move(result);
    }

    friend std::ostream& operator<<(std::ostream &os, const DiscreteTorusPoly &toruspoly) {
      for (auto coeff: toruspoly.coeffs) {
        os << coeff << ' ';
      }
      return os;
    }
};


#endif