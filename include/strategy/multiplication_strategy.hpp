#ifndef MULTIPLICATION_STRATEGY_HPP
#define MULTIPLICATION_STRATEGY_HPP

#include "structure/galoisfieldpoly.hpp"

class MultiplicationStrategy {
public:
    virtual ~MultiplicationStrategy() = default;
    virtual GaloisFieldPoly multiply(GaloisFieldPoly &a, GaloisFieldPoly &b) const = 0;
};

#endif