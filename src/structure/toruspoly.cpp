#include "structure/toruspoly.hpp"
#include "strategy/naive_multiplication_strategy.hpp"
#include "strategy/ntt_multiplication_strategy.hpp"
#include "factory/multiplication_factory.hpp"

DiscreteTorusPoly::DiscreteTorusPoly(size_t N) : PolyBase<DiscreteTorus>(N) {};  

DiscreteTorusPoly::DiscreteTorusPoly(const std::vector<DiscreteTorus> &coeffs) : PolyBase<DiscreteTorus>(coeffs) {};

DiscreteTorusPoly::DiscreteTorusPoly(GaloisFieldPoly &&gfpoly) noexcept
    : PolyBase<DiscreteTorus>(std::move(gfpoly)) {
}

uint32_t DiscreteTorusPoly::modulus() const {
  return q;
}

void DiscreteTorusPoly::print(std::ostream &os) const {
  PolyBase<DiscreteTorus>::print(os);
}

std::ostream& operator<<(std::ostream &os, const DiscreteTorusPoly &poly) {
  poly.print(os);
  return os;
}

DiscreteTorusPoly operator*(IntPoly& poly1, DiscreteTorusPoly &poly2) {
#if defined(POLYNOMIAL_MULTIPLICATION_METHOD_NTT)
  using MultiplicationStrategy = NTTMultiplicationStrategy;
#elif defined(POLYNOMIAL_MULTIPLICATION_METHOD_NAIVE)
  using MultiplicationStrategy = NaiveMultiplicationStrategy;
#else
  Log::error("Polynomial Multiplication Method is not defined");
#endif
  auto multiplication_strategy = MultiplicationFactory<MultiplicationStrategy>::create(poly2.modulus(), poly1.size());

  return multiplication_strategy->multiply(poly1, poly2);
}