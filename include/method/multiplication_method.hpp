#ifndef MULTIPLICATION_METHOD_HPP
#define MULTIPLICATION_METHOD_HPP

#include "structure/galoisfieldpoly.hpp"

class MultiplicationMethod {
public:
    virtual ~MultiplicationMethod() = default;
    virtual DiscreteTorusPoly multiply(IntPoly &poly1, DiscreteTorusPoly &poly2) const = 0;
};

#endif