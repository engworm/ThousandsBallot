#include "structure/toruspoly.hpp"

DiscreteTorusPoly::DiscreteTorusPoly(size_t N) : PolyBase<DiscreteTorus>(N) {};  

DiscreteTorusPoly::DiscreteTorusPoly(const std::vector<DiscreteTorus> &coeffs) : PolyBase<DiscreteTorus>(coeffs) {};

DiscreteTorusPoly::DiscreteTorusPoly(GaloisFieldPoly &&gfpoly) noexcept
    : PolyBase<DiscreteTorus>(std::move(gfpoly)) {
}

void DiscreteTorusPoly::print(std::ostream &os) const {
  PolyBase<DiscreteTorus>::print(os);
}

std::ostream& operator<<(std::ostream &os, const DiscreteTorusPoly &poly) {
  poly.print(os);
  return os;
}

DiscreteTorusPoly operator*(const IntPoly& intpoly, const DiscreteTorusPoly &toruspoly) {

  if (intpoly.size() != toruspoly.size()) {
    throw std::invalid_argument("Polynomial degree must be the same");
  }

  std::vector<DiscreteTorus> zero(toruspoly.size(), DiscreteTorus(0));
  DiscreteTorusPoly result(zero);
  for (size_t i = 0; i < toruspoly.size(); ++i) {
    for (size_t j = 0; j < toruspoly.size(); ++j) {
      size_t k = (i + j) % toruspoly.size();
      if (i + j >= toruspoly.size()) {
        result[k] -= intpoly[j]* toruspoly[i];
      }
      else {
        result[k] += intpoly[j] * toruspoly[i];
      }
    }
  }

  return result;
}