#include "structure/toruspoly.hpp"
#include "factory/multiplication_method_manager.hpp"

DiscreteTorusPoly::DiscreteTorusPoly(uint32_t N) : PolyBase<DiscreteTorus>(N) {};  

DiscreteTorusPoly::DiscreteTorusPoly(const std::vector<DiscreteTorus> &coeffs) : PolyBase<DiscreteTorus>(coeffs) {};

DiscreteTorusPoly::DiscreteTorusPoly(GaloisFieldPoly &&gfpoly) noexcept
    : PolyBase<DiscreteTorus>(std::move(gfpoly)) {
}

uint32_t DiscreteTorusPoly::modulus() const {
  return q;
}

void DiscreteTorusPoly::print(std::ostream &os) const {
  PolyBase<DiscreteTorus>::print(os);
}

std::ostream& operator<<(std::ostream &os, const DiscreteTorusPoly &poly) {
  poly.print(os);
  return os;
}

DiscreteTorusPoly operator*(IntPoly& poly1, DiscreteTorusPoly &poly2) {
  auto multiplication_strategy = MultiplicationMethodManager::create();
  return multiplication_strategy->multiply(poly1, poly2);
}