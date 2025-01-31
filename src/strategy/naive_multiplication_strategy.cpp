#include "strategy/naive_multiplication_strategy.hpp"
#include "structure/toruspoly.hpp"

NaiveMultiplicationStrategy::NaiveMultiplicationStrategy(uint32_t P, uint32_t N) : P(P), N(N) {
}

std::shared_ptr<NaiveMultiplicationStrategy> NaiveMultiplicationStrategy::getInstance(uint32_t P, uint32_t N) {
  auto instance = std::shared_ptr<NaiveMultiplicationStrategy>(new NaiveMultiplicationStrategy(P, N));
  return instance;
}

GaloisFieldPoly NaiveMultiplicationStrategy::multiply(GaloisFieldPoly &poly1, GaloisFieldPoly &poly2) const {
  std::vector<GaloisFieldElement> zero(poly1.size(), GaloisFieldElement(0));
  GaloisFieldPoly result(zero);
  for (size_t i = 0; i < poly1.size(); ++i) {
    for (size_t j = 0; j < poly1.size(); ++j) {
      size_t k = (i + j) % poly1.size();
      if (i + j >= poly1.size()) {
          result[k] -= poly1[j]* poly2[i];
      }
      else {
          result[k] += poly1[j] * poly2[i];
      }
    }
  }
  return result;
}

DiscreteTorusPoly NaiveMultiplicationStrategy::multiply(IntPoly &poly1, DiscreteTorusPoly&poly2) const {
  GaloisFieldPoly gfpoly1 = std::move(poly1);
  GaloisFieldPoly gfpoly2 = std::move(poly2);
  GaloisFieldPoly gfpoly3 = multiply(gfpoly1, gfpoly2);
  DiscreteTorusPoly result = std::move(gfpoly3);
  return result;
}
