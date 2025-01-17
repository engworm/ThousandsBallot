#include "factory/multiplication_factory.hpp"
#include "strategy/ntt_multiplication_strategy.hpp"
#include "strategy/naive_multiplication_strategy.hpp"

std::shared_ptr<MultiplicationStrategy> MultiplicationFactory::create(bool useNTT) {
    if (useNTT) {
        return NTTMultiplicationStrategy::getInstance();
    } else {
        static std::shared_ptr<NaiveMultiplicationStrategy> instance
            = std::make_shared<NaiveMultiplicationStrategy>();
        return instance;
    }
};
