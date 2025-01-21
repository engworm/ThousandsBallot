#include "structure/galoisfieldpoly.hpp"
#include "structure/toruspoly.hpp"
#include "factory/multiplication_factory.hpp"

GaloisFieldPoly::GaloisFieldPoly(size_t N) 
    : PolyBase<GaloisFieldElement>(N) {
};

GaloisFieldPoly::GaloisFieldPoly(const std::vector<GaloisFieldElement> &coeffs) 
    : PolyBase<GaloisFieldElement>(coeffs) {};
    
GaloisFieldPoly::GaloisFieldPoly(IntPoly &&intpoly) noexcept
    : PolyBase<GaloisFieldElement>(std::move(intpoly)) {
}

GaloisFieldPoly::GaloisFieldPoly(DiscreteTorusPoly &&toruspoly) noexcept
    : PolyBase<GaloisFieldElement>(std::move(toruspoly)) {
}

std::vector<GaloisFieldElement> GaloisFieldPoly::get_coeffs() const {
  return PolyBase<GaloisFieldElement>::get_coeffs();
}

void GaloisFieldPoly::print(std::ostream &os) const {
  PolyBase<GaloisFieldElement>::print(os);
}

std::ostream& operator<<(std::ostream &os, const GaloisFieldPoly &poly) {
  poly.print(os);
  return os;
}

GaloisFieldPoly operator*(GaloisFieldPoly &poly1, GaloisFieldPoly &poly2) {
  if (poly1.size() != poly2.size()) {
    Log::error("Polynomial degree must be the same");
  }
  
  bool useNTT = false;
#ifdef NTT
  useNTT = true;
#endif

  auto multiplication_strategy = MultiplicationFactory::create(useNTT);
  return multiplication_strategy->multiply(poly1, poly2);
}