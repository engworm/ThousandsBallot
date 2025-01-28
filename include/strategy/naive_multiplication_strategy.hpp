#ifndef NAIVE_MULTIPLICATION_STRATEGY_HPP
#define NAIVE_MULTIPLICATION_STRATEGY_HPP

#include <memory>
#include "strategy/multiplication_strategy.hpp"

class NaiveMultiplicationStrategy : public MultiplicationStrategy {
private:
  uint32_t P; 
  uint32_t N;

  NaiveMultiplicationStrategy(uint32_t P, uint32_t N);
public:
  static std::shared_ptr<NaiveMultiplicationStrategy> getInstance(uint32_t P, uint32_t N);
  GaloisFieldPoly multiply(GaloisFieldPoly &poly1, GaloisFieldPoly &poly2) const override; 
};

#endif 