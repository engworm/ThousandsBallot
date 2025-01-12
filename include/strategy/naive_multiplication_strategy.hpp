#ifndef NAIVE_MULTIPLICATION_STRATEGY_HPP
#define NAIVE_MULTIPLICATION_STRATEGY_HPP

#include "strategy/multiplication_strategy.hpp"
#include "utility/log.hpp"

class NaiveMultiplicationStrategy : public MultiplicationStrategy {
public:
    GaloisFieldPoly multiply(const GaloisFieldPoly &poly1, const GaloisFieldPoly &poly2) const override {
        std::vector<GaloisFieldElement> zero(poly1.size(), GaloisFieldElement(0));
        GaloisFieldPoly result(zero);
        for (size_t i = 0; i < poly1.size(); ++i) {
          for (size_t j = 0; j < poly1.size(); ++j) {
            size_t k = (i + j) % poly1.size();
            if (i + j >= poly1.size()) {
              result[k] -= poly1[j]* poly2[i];
            }
            else {
              result[k] += poly2[j] * poly2[i];
            }
          }
        }
        return result;
    }
};

#endif 