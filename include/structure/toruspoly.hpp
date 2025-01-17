#ifndef TORUSPOLY_HPP
#define TORUSPOLY_HPP

#include "structure/torus.hpp"
#include "structure/galoisfieldpoly.hpp"

class DiscreteTorusPoly : public PolyBase<DiscreteTorus> {
public:
    DiscreteTorusPoly(const std::vector<DiscreteTorus> &coeffs);

    DiscreteTorusPoly(const DiscreteTorusPoly &toruspoly) = delete;
    DiscreteTorusPoly(const GaloisFieldPoly &gfpoly) = delete;

    DiscreteTorusPoly(DiscreteTorusPoly &&toruspoly) noexcept = default;
    DiscreteTorusPoly(GaloisFieldPoly &&gfpoly) noexcept;

protected:
    void print(std::ostream &os) const override;

friend std::ostream& operator<<(std::ostream &os, const DiscreteTorusPoly &poly);
};
DiscreteTorusPoly operator*(const IntPoly& intpoly, const DiscreteTorusPoly &toruspoly);

#endif