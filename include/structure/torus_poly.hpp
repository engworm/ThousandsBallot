#ifndef TORUS_POLY_HPP
#define TORUS_POLY_HPP

#include <iostream>
#include <cstdint>
#include <vector>
#include "params/params.hpp"
#include "structure/torus.hpp"
#include "structure/poly.hpp"

class DiscreteTorusPoly {
  private:
    uint32_t N{}; 
    std::uint32_t P = Params::P;
    std::vector<DiscreteTorus> coeffs;
  
  protected:
    DiscreteTorus& operator[](int i) { return coeffs[i]; }

  public:
    DiscreteTorusPoly(const std::vector<DiscreteTorus> &coeffs) : coeffs(coeffs) {
      this->N = coeffs.size();
    };

    // DiscreteTorusPoly(const DiscreteTorusPoly &toruspoly) {
      // this->N = toruspoly.N;
      // this->P = toruspoly.P;
      // for (int i = 0; i < N; ++i) {
        // this->coeffs[i] = toruspoly[i];
      // }
    // }

    DiscreteTorusPoly(DiscreteTorusPoly&& toruspoly) noexcept
      : N(toruspoly.N), P(toruspoly.P), coeffs(std::move(toruspoly.coeffs)) {};

    uint32_t size() const { return this->N; };
    DiscreteTorus operator[](int i) const { return coeffs[i]; };
    std::vector<DiscreteTorus> get_coeffs() const {return coeffs; }

    friend DiscreteTorusPoly operator*(const Poly& poly, const DiscreteTorusPoly &toruspoly) {

      if (poly.size() != toruspoly.N) {
        throw std::invalid_argument("Polynomial degree must be the same");
      }

      std::vector<DiscreteTorus> zero(toruspoly.N, DiscreteTorus(0));
      DiscreteTorusPoly result(zero);
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