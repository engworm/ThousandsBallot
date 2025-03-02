#include "factory/multiplication_factory.hpp"
#include "method/ntt_multiplication_method.hpp"
#include "method/naive_multiplication_method.hpp"

template <>
std::shared_ptr<NTTMultiplicationMethod> MultiplicationFactory<NTTMultiplicationMethod>::create(uint32_t P, uint32_t N) {
  return NTTMultiplicationMethod::getInstance(P, N);
}

template<>
std::shared_ptr<NaiveMultiplicationMethod> MultiplicationFactory<NaiveMultiplicationMethod>::create(uint32_t P, uint32_t N) {
  return NaiveMultiplicationMethod::getInstance(P, N);
}
