#ifndef NAIVE_MULTIPLICATION_METHOD_HPP
#define NAIVE_MULTIPLICATION_METHOD_HPP

#include <memory>
#include "method/multiplication_method.hpp"

class NaiveMultiplicationMethod : public MultiplicationMethod {
private:
  uint32_t P; 
  uint32_t N;

static std::shared_ptr<NaiveMultiplicationMethod> instance;
  NaiveMultiplicationMethod(uint32_t P, uint32_t N);

public:
  static std::shared_ptr<NaiveMultiplicationMethod> getInstance(uint32_t P, uint32_t N);
  DiscreteTorusPoly multiply(IntPoly &poly1, DiscreteTorusPoly &poly2) const override;
};

#endif 