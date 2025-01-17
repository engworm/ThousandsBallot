#ifndef NAIVE_MULTIPLICATION_STRATEGY_HPP
#define NAIVE_MULTIPLICATION_STRATEGY_HPP

#include "strategy/multiplication_strategy.hpp"

class NaiveMultiplicationStrategy : public MultiplicationStrategy {
public:
    GaloisFieldPoly multiply(GaloisFieldPoly &poly1, GaloisFieldPoly &poly2) const override; 
};

#endif 