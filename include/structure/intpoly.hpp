#ifndef INTPOLY_HPP
#define INTPOLY_HPP

#include <cstdint>
#include "structure/poly_base.hpp"

class IntPoly : public PolyBase<uint32_t> {
  public:
    IntPoly() = default;
    IntPoly(size_t N);
    IntPoly(const std::vector<uint32_t> &coeffs);

    IntPoly(const IntPoly &poly) = delete;

    IntPoly(IntPoly &&intpoly) noexcept = default;
  
  protected:
    void print(std::ostream &os) const override;

  friend std::ostream& operator<<(std::ostream &os, const IntPoly &poly);
};

#endif