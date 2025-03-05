#ifndef MULTIPLICATION_MANAGER_HPP
#define MULTIPLICATION_MANAGER_HPP

#include <memory>

#include "params/params.hpp"
#include "params/nttparams.hpp"

#include "method/naive_multiplication_method.hpp"
#include "method/ntt_multiplication_method.hpp"

class MultiplicationMethodManager {
public:
  static std::shared_ptr<MultiplicationMethod> create() {
    #if defined(POLYNOMIAL_MULTIPLICATION_METHOD_NTT)
      return NTTMultiplicationMethod::getInstance(NTTParams::P, NTTParams::N);
    #elif defined(POLYNOMIAL_MULTIPLICATION_METHOD_NAIVE)
      return NaiveMultiplicationMethod::getInstance(Params::q, Params::N);
    #else
      return nullptr;
    #endif
  }
};

#endif