#ifndef NTT_MULTIPLICATION_STRATEGY_HPP
#define NTT_MULTIPLICATION_STRATEGY_HPP

#include "strategy/multiplication_strategy.hpp"
#include "utility/log.hpp"

class NTTMultiplicationStrategy : public MultiplicationStrategy {
public:
    GaloisFieldPoly multiply(const GaloisFieldPoly &a, const GaloisFieldPoly &b) const override {
        std::vector<GaloisFieldElement> zero(a.size(), GaloisFieldElement(0));
        GaloisFieldPoly result(zero);
        Log::info("NTT multiplication logic here");
        return result;
    }
};

#endif 