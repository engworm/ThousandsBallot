#include "structure/intpoly.hpp"

IntPoly::IntPoly(const std::vector<uint32_t> &coeffs) : PolyBase<uint32_t>(coeffs) {
  this->N = coeffs.size();
};

void IntPoly::print(std::ostream &os) const {
  PolyBase<uint32_t>::print(os);
}

std::ostream& operator<<(std::ostream &os, const IntPoly &poly) {
  poly.print(os);
  return os;
}

