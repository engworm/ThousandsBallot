#include "factory/modulus_factory.hpp"

std::shared_ptr<ModulusStrategy> ModulusFactory::modulus_strategy = nullptr;
std::shared_ptr<ModulusFactory> ModulusFactory::instance = nullptr;

ModulusFactory::ModulusFactory(uint32_t P) {
  if ((P & (P+1)) == 0) {
    Log::info("Modulus Strategy: [ Mersenne ]");
    modulus_strategy = std::static_pointer_cast<ModulusStrategy>(MersenneModulusStrategy::getInstance(P));
  } else {
    Log::info("Modulus Strategy: [ Naive ]");
    modulus_strategy = std::static_pointer_cast<ModulusStrategy>(NaiveModulusStrategy::getInstance(P));
  }
}

void ModulusFactory::create(uint32_t P) {
  if (instance == nullptr) {
    instance = std::shared_ptr<ModulusFactory>(new ModulusFactory(P));
  } else {
    Log::error("Modulus Factory is already defined");
  }
}

std::shared_ptr<ModulusFactory> ModulusFactory::getInstance() {
  if (instance == nullptr) {
    Log::error("Modulus Factory is not defined");
    return nullptr;
  } else {
    return instance;
  }
}
