#ifndef INTPOLY_HPP
#define INTPOLY_HPP

#include <cstdint>
#include "structure/poly_base.hpp"

class IntPoly : public PolyBase<uint32_t> {
  private:
    void print(std::ostream &os) const override;

  public:
    IntPoly() = default;
    IntPoly(uint32_t N);
    IntPoly(const std::vector<uint32_t> &coeffs);

    IntPoly(const IntPoly &poly) = delete;
    IntPoly(IntPoly &&intpoly) noexcept = default;
  
    friend std::ostream& operator<<(std::ostream &os, const IntPoly &poly);
};

#endif