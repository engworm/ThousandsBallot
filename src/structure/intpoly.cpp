#include "structure/intpoly.hpp"

IntPoly::IntPoly(size_t N) : PolyBase<uint32_t>(N) {};

IntPoly::IntPoly(const std::vector<uint32_t> &coeffs) : PolyBase<uint32_t>(coeffs) {};

void IntPoly::print(std::ostream &os) const {
  PolyBase<uint32_t>::print(os);
}

std::ostream& operator<<(std::ostream &os, const IntPoly &poly) {
  poly.print(os);
  return os;
}

