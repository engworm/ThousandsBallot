#include "structure/galoisfieldpoly.hpp"
#include "structure/toruspoly.hpp"


GaloisFieldPoly::GaloisFieldPoly() = default;
GaloisFieldPoly::GaloisFieldPoly(const std::vector<GaloisFieldElement> &coeffs) : PolyBase<GaloisFieldElement>(coeffs) {
  this->N = coeffs.size();
};
    
GaloisFieldPoly::GaloisFieldPoly(const IntPoly &poly) {
  this->N = poly.size();
  for (int i = 0; i < this->N; ++i) {
    std::vector<uint32_t> tmp = poly.get_coeffs(); 
    this->coeffs.emplace_back(GaloisFieldElement(poly[i]));
  }
};

GaloisFieldPoly::GaloisFieldPoly(const DiscreteTorusPoly &poly) {
  this->N = poly.size();
  for (int i = 0; i < this->N; ++i) {
    std::vector<DiscreteTorus> tmp = poly.get_coeffs();
    this->coeffs.emplace_back(GaloisFieldElement(poly[i]));
  }
};

std::ostream& operator<<(std::ostream &os, const GaloisFieldPoly &poly) {
  for (auto coeff: poly.coeffs) {
    os << coeff << ' ';
  }
  return os;
}

GaloisFieldPoly operator*(const GaloisFieldPoly &poly1, const GaloisFieldPoly &poly2) {
  if (poly1.size() != poly2.size()) {
    Log::error("Polynomial degree must be the same");
  }

  std::vector<GaloisFieldElement> zero(poly1.size(), GaloisFieldElement(0));
  GaloisFieldPoly result(zero);
  std::cout << "NTT multiplication" << std::endl;
  std::cout << result.size() << std::endl;
  return result;
}