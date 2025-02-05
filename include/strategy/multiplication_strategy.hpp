#ifndef MULTIPLICATION_STRATEGY_HPP
#define MULTIPLICATION_STRATEGY_HPP

#include "structure/galoisfieldpoly.hpp"

class MultiplicationStrategy {
public:
    virtual ~MultiplicationStrategy() = default;
    virtual DiscreteTorusPoly multiply(IntPoly &poly1, DiscreteTorusPoly &poly2) const = 0;
};

#endif