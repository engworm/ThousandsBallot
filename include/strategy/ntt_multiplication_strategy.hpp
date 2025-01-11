#ifndef NTT_MULTIPLICATION_STRATEGY_HPP
#define NTT_MULTIPLICATION_STRATEGY_HPP

#include <vector>
#include "params/nttparams.hpp"
#include "strategy/multiplication_strategy.hpp"
#include "structure/galoisfieldpoly.hpp"
#include "utility/log.hpp"

// Singleton Pattern
class NTTMultiplicationStrategy : public MultiplicationStrategy {
private:
  uint32_t P = NttParams::P;
  uint32_t N = NttParams::N;
  uint32_t psi = NttParams::psi;
  uint32_t omega = NttParams::omega;

  static std::vector<GaloisFieldElement> psi_power_table;
  static std::vector<GaloisFieldElement> psi_power_table_bit_reversed_order;

  static NTTMultiplicationStrategy *instance;
  NTTMultiplicationStrategy() {
    Log::info("NTT Multiplication Strategy: ψ power table preparation is complete");
    init_psi_power_table();
    init_psi_power_table_bit_reversed_order();
  };

public:
  static NTTMultiplicationStrategy* getInstance() {
    if (!instance) { 
      instance = new NTTMultiplicationStrategy();
    }
    return instance;
  }

  void init_psi_power_table() {
    psi_power_table.reserve(N);
    psi_power_table[0] = 1;
    for (int i = 0; i < N; ++i) {
      psi_power_table[i] = psi_power_table[i-1] * psi;
    }
  }

  void init_psi_power_table_bit_reversed_order() {
    auto bit_reverse = [](uint32_t n, uint32_t log2n) {
      uint32_t ans = 0;
      for (uint32_t i = 0; i < log2n; ++i) {
          ans = (ans << 1) | (n & 1);
          n >>= 1;
      }
      return ans;
    };

    psi_power_table_bit_reversed_order.reserve(N);
    for (int i = 0; i < N; ++i) {
      int rev_i = bit_reverse(i, std::log2(N));
      psi_power_table_bit_reversed_order[rev_i] = psi_power_table[i];
    }
  }

  GaloisFieldPoly multiply(const GaloisFieldPoly &a, const GaloisFieldPoly &b) const override {
    std::vector<GaloisFieldElement> zero(a.size(), GaloisFieldElement(0));
    GaloisFieldPoly result(zero);
    Log::info("NTT multiplication logic here");
    return result;
  }
};

#endif 