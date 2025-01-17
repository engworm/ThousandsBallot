#ifndef MULTIPLICATION_FACTORY_HPP
#define MULTIPLICATION_FACTORY_HPP

#include <memory>
#include "strategy/multiplication_strategy.hpp"

class MultiplicationFactory {
public:
    static MultiplicationStrategy* create(bool useNTT);
   
};

#endif