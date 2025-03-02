#include "method/naive_multiplication_method.hpp"
#include "structure/toruspoly.hpp"

NaiveMultiplicationMethod::NaiveMultiplicationMethod(uint32_t P, uint32_t N) : P(P), N(N) {
}

std::shared_ptr<NaiveMultiplicationMethod> NaiveMultiplicationMethod::getInstance(uint32_t P, uint32_t N) {
  auto instance = std::shared_ptr<NaiveMultiplicationMethod>(new NaiveMultiplicationMethod(P, N));
  return instance;
}

DiscreteTorusPoly NaiveMultiplicationMethod::multiply(IntPoly &poly1, DiscreteTorusPoly&poly2) const {
  std::vector<DiscreteTorus> zero(poly1.size(), DiscreteTorus(0));
  DiscreteTorusPoly result(zero);
  for (size_t i = 0; i < poly1.size(); ++i) {
    for (size_t j = 0; j < poly1.size(); ++j) {
      size_t k = (i + j) % poly1.size();
      if (i + j >= poly1.size()) {
          result[k] -= poly1[j] * poly2[i];
      }
      else {
          result[k] += poly1[j] * poly2[i];
      }
    }
  }
  return result;
}
