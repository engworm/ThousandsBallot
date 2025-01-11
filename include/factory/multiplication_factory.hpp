#ifndef MULTIPLICATION_FACTORY_HPP
#define MULTIPLICATION_FACTORY_HPP

#include <memory>
#include "strategy/multiplication_strategy.hpp"
#include "strategy/ntt_multiplication_strategy.hpp"
#include "strategy/naive_multiplication_strategy.hpp"

class MultiplicationFactory {
public:
    static std::unique_ptr<MultiplicationStrategy> create(bool useNTT) {
        if (useNTT) {
            return std::make_unique<NTTMultiplicationStrategy>();
        } else {
            return std::make_unique<NaiveMultiplicationStrategy>();
        }
    }
};

#endif