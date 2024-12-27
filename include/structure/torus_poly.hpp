#ifndef TORUS_POLY_HPP
#define TORUS_POLY_HPP

#include <iostream>
#include <cstdint>
#include <vector>
#include "params/params.hpp"
#include "structure/torus.hpp"
#include "structure/poly.hpp"

class TorusPoly {

  private:
    uint32_t N{}; 
    std::uint32_t P = Params::P;
    std::vector<DiscreteTorus> coeffs;
  
  protected:
    DiscreteTorus& operator[](int i) { return coeffs[i]; }

  public:
    TorusPoly(const std::vector<DiscreteTorus> &coeffs) : coeffs(coeffs) {
      this->N = coeffs.size();
    };

    DiscreteTorus operator[](int i) const { return coeffs[i]; };

    friend TorusPoly operator*(const Poly& poly, const TorusPoly toruspoly) {

      if (poly.size() != toruspoly.N) {
        throw std::invalid_argument("Polynomial degree must be the same");
      }

      std::vector<DiscreteTorus> zero(toruspoly.N, DiscreteTorus(0));
      TorusPoly result(zero);
      for (size_t i = 0; i < toruspoly.N; ++i) {
        for (size_t j = 0; j < toruspoly.N; ++j) {
          size_t k = (i + j) % toruspoly.N;
          if (i + j >= toruspoly.N) {
            result[k] -= poly[j]* toruspoly[i];
          }
          else {
            result[k] += poly[j] * toruspoly[i];
          }
        }
      }

      return result;
    }

    friend std::ostream& operator<<(std::ostream &os, const TorusPoly &toruspoly) {
      for (auto coeff: toruspoly.coeffs) {
        os << coeff << ' ';
      }
      return os;
    }
};


#endif