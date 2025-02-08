#ifndef TORUSPOLY_HPP
#define TORUSPOLY_HPP

#include "structure/torus.hpp"
#include "structure/galoisfieldpoly.hpp"

class DiscreteTorusPoly : public PolyBase<DiscreteTorus> {
  private:
    uint32_t q = Params::q;

  private:
    void print(std::ostream &os) const override;

  public:
    DiscreteTorusPoly() = default;
    DiscreteTorusPoly(size_t N); 
    DiscreteTorusPoly(const std::vector<DiscreteTorus> &coeffs);

    DiscreteTorusPoly(const DiscreteTorusPoly &toruspoly) = delete;
    DiscreteTorusPoly(const GaloisFieldPoly &gfpoly) = delete;

    DiscreteTorusPoly(DiscreteTorusPoly &&toruspoly) noexcept = default;
    DiscreteTorusPoly(GaloisFieldPoly &&gfpoly) noexcept;

    uint32_t modulus() const;

    friend std::ostream& operator<<(std::ostream &os, const DiscreteTorusPoly &poly);
};
DiscreteTorusPoly operator*(IntPoly& intpoly, DiscreteTorusPoly &toruspoly);

#endif