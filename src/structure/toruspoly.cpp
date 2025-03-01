#include "structure/toruspoly.hpp"
#include "method/naive_multiplication_strategy.hpp"
#include "method/ntt_multiplication_strategy.hpp"
#include "factory/multiplication_factory.hpp"

DiscreteTorusPoly::DiscreteTorusPoly(uint32_t N) : PolyBase<DiscreteTorus>(N) {};  

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
  auto multiplication_strategy = MultiplicationFactory<NTTMultiplicationStrategy>::create(NTTParams::P, NTTParams::N);
#elif defined(POLYNOMIAL_MULTIPLICATION_METHOD_NAIVE)
  auto multiplication_strategy = MultiplicationFactory<NaiveMultiplicationStrategy>::create(Params::q, Params::N);
#else
  Log::error("Polynomial Multiplication Method is not defined");
#endif

  return multiplication_strategy->multiply(poly1, poly2);
}