#ifndef INTPOLY_HPP
#define INTPOLY_HPP

#include <cstdint>
#include "structure/poly_base.hpp"

class IntPoly : public PolyBase<uint32_t> {
  public:
    IntPoly() = default;
    IntPoly(const std::vector<uint32_t> &coeffs) : PolyBase<uint32_t>(coeffs) {
      this->N = coeffs.size();
    };
};

#endif