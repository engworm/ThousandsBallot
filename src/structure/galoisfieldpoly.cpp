#include "structure/galoisfieldpoly.hpp"
#include "structure/toruspoly.hpp"
#include "factory/multiplication_method_manager.hpp"

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
