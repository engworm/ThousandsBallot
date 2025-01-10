#ifndef NAIVE_MULTIPLICATION_STRATEGY_HPP
#define NAIVE_MULTIPLICATION_STRATEGY_HPP

#include "strategy/multiplication_strategy.hpp"
#include "utility/log.hpp"

class RegularMultiplicationStrategy : public MultiplicationStrategy {
public:
    GaloisFieldPoly multiply(const GaloisFieldPoly &a, const GaloisFieldPoly &b) const override {
        if (a.size() != b.size()) {
            Log::error("Polynomial degree must be the same");
        }

        std::vector<GaloisFieldElement> zero(a.size(), GaloisFieldElement(0));
        GaloisFieldPoly result(zero);
        // Regular multiplication logic here
        Log::warn("Naive polynomial multiplication has been selected");
        return result;
    }
};

#endif // REGULAR_MULTIPLICATION_STRATEGY_HPP