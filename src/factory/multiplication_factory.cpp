#include "factory/multiplication_factory.hpp"
#include "strategy/multiplication_strategy.hpp"
#include "strategy/ntt_multiplication_strategy.hpp"
#include "strategy/naive_multiplication_strategy.hpp"

std::shared_ptr<MultiplicationStrategy> MultiplicationFactory::create(uint32_t P, uint32_t N, bool useNTT) {
    if (useNTT) {
        return NTTMultiplicationStrategy::getInstance(P, N);
    } else {
        static std::shared_ptr<NaiveMultiplicationStrategy> instance
            = std::make_shared<NaiveMultiplicationStrategy>();
        return instance;
    }
};
