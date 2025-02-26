#ifndef MODULUS_FACTORY_HPP
#define MODULUS_FACTORY_HPP

#include <cstdint>
#include <memory>
#include "strategy/modulus_strategy.hpp"
#include "strategy/mersenne_modulus_strategy.hpp"
#include "strategy/naive_modulus_strategy.hpp"
#include "utility/log.hpp"

class ModulusFactory {
private:
  static std::shared_ptr<ModulusStrategy> modulus_strategy; 
  static std::shared_ptr<ModulusFactory> instance;

  ModulusFactory(uint32_t P); 

public:
  static void create(uint32_t P);
  static std::shared_ptr<ModulusFactory> getInstance();

  uint32_t modulus(uint32_t x) const {
    return modulus_strategy->modulus(x);
  }
  
};

#endif