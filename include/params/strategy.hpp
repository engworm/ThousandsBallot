#ifndef STRATEGY_HPP
#define STRATEGY_HPP

template <typename T, typename S>
class Strategy {

  using ModulusStrategy = T;
  using MultiplicationMethod = S;

  public:
    ModulusWrapper<ModulusStrategy> modulus_wrapper;
    MultiplicationFactory<MultiplicationMethod> multiplication_factory;
};

#endif