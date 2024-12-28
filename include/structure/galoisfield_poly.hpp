#ifndef GALOISFIELD_POLY_HPP
#define GALOISFIELD_POLY_HPP

#include <iostream>
#include <cstdint>
#include <vector>
#include "params/params.hpp"
#include "structure/galoisfield.hpp"
#include "structure/poly.hpp"
#include "structure/int_poly.hpp"
#include "structure/torus.hpp"
#include "structure/torus_poly.hpp"

class GaloisFieldPoly : public PolyBase<GaloisFieldElement> {
  private:
    uint32_t N = NttParams::N;
    std::uint32_t P = NttParams::P;
    std::vector<GaloisFieldElement> coeffs;

  public:
    GaloisFieldPoly(const std::vector<GaloisFieldElement> &coeffs) : coeffs(coeffs) {
      this->N = coeffs.size();
    };
    
    GaloisFieldPoly(const IntPoly &poly) {
      if (this->N != poly.size()) {
        throw std::invalid_argument("Polynomial degree must be the same");
      }
      for (int i = 0; i < this->N; ++i) {
        std::vector<uint32_t> tmp = poly.get_coeffs(); 
        this->coeffs.emplace_back(GaloisFieldElement(poly[i]));
      }
    };

    GaloisFieldPoly(const DiscreteTorusPoly &poly) {
      if (this->N != poly.size()) {
        throw std::invalid_argument("Polynomial degree must be the same");
      }
      for (int i = 0; i < this->N; ++i) {
        std::vector<DiscreteTorus> tmp = poly.get_coeffs();
        this->coeffs.emplace_back(GaloisFieldElement(poly[i]));
      }
    };

    friend GaloisFieldPoly operator*(const GaloisFieldPoly &poly1, const GaloisFieldPoly &poly2) {
      if (poly1.N != poly2.N) {
        throw std::invalid_argument("Polynomial degree must be the same");
      }
      std::cout << "mgmg" << std::endl;

      std::vector<GaloisFieldElement> zero(poly1.N, GaloisFieldElement(0));
      GaloisFieldPoly result(zero);
      std::cout << "NTT multiplication" << std::endl;
      return std::move(result);
    }

    friend std::ostream& operator<<(std::ostream &os, const GaloisFieldPoly &poly) {
      for (auto coeff: poly.coeffs) {
        os << coeff << ' ';
      }
      return os;
    }
};

#endif