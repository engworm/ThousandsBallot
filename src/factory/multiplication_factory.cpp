#include "factory/multiplication_factory.hpp"
#include "strategy/ntt_multiplication_strategy.hpp"
#include "strategy/naive_multiplication_strategy.hpp"

MultiplicationStrategy* MultiplicationFactory::create(bool useNTT) {
    if (useNTT) {
        return NTTMultiplicationStrategy::getInstance();
    } else {
        static NaiveMultiplicationStrategy instance;
        return &instance;
    }
};
