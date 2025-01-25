#ifndef MULTIPLICATION_FACTORY_HPP
#define MULTIPLICATION_FACTORY_HPP

#include <memory>
#include "strategy/multiplication_strategy.hpp"

class MultiplicationFactory {
public:
    static std::shared_ptr<MultiplicationStrategy> create(uint32_t P, uint32_t N, bool useNTT);
};

#endif