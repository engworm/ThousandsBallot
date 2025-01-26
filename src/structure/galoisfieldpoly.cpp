#include "structure/galoisfieldpoly.hpp"
#include "structure/toruspoly.hpp"
#include "factory/multiplication_factory.hpp"
#include "strategy/multiplication_strategy.hpp"
#include "strategy/naive_multiplication_strategy.hpp"
#include "strategy/ntt_multiplication_strategy.hpp"

GaloisFieldPoly::GaloisFieldPoly(uint32_t P, uint32_t N) 
    : P(P), PolyBase<GaloisFieldElement>(N) {
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

uint32_t GaloisFieldPoly::modulus() const {
  return P;
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
  if (poly1.modulus() != poly2.modulus()) {
    Log::error("The modulus of the polynomial coefficient fields must be the same");
  }
  
#ifdef NTT
  using MultiplicationStrategy = NTTMultiplicationStrategy;
#else
  using MultiplicationStrategy = NaiveMultiplicationStrategy;
#endif
  auto multiplication_strategy = MultiplicationFactory<MultiplicationStrategy>::create(poly1.modulus(), poly1.size());

  return multiplication_strategy->multiply(poly1, poly2);
}