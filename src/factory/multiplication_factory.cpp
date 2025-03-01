#include "factory/multiplication_factory.hpp"
#include "method/ntt_multiplication_strategy.hpp"
#include "method/naive_multiplication_strategy.hpp"

template <>
std::shared_ptr<NTTMultiplicationStrategy> MultiplicationFactory<NTTMultiplicationStrategy>::create(uint32_t P, uint32_t N) {
  return NTTMultiplicationStrategy::getInstance(P, N);
}

template<>
std::shared_ptr<NaiveMultiplicationStrategy> MultiplicationFactory<NaiveMultiplicationStrategy>::create(uint32_t P, uint32_t N) {
  return NaiveMultiplicationStrategy::getInstance(P, N);
}
