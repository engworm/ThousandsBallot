#include "strategy/ntt_multiplication_strategy.hpp"

NTTMultiplicationStrategy* NTTMultiplicationStrategy::instance = nullptr;
std::vector<GaloisFieldElement> NTTMultiplicationStrategy::psi_power_table;
std::vector<GaloisFieldElement> NTTMultiplicationStrategy::psi_power_table_bit_reversed_order;

NTTMultiplicationStrategy::NTTMultiplicationStrategy() {
  Log::info("NTT Multiplication Strategy: ψ power table preparation is complete");
  init_psi_power_table();
  init_psi_power_table_bit_reversed_order();
}

void NTTMultiplicationStrategy::init_psi_power_table() {
  psi_power_table.reserve(N);
  psi_power_table[0] = 1;
  for (int i = 0; i < N; ++i) {
    psi_power_table[i] = psi_power_table[i-1] * psi;
  }
}

void NTTMultiplicationStrategy::init_psi_power_table_bit_reversed_order() {
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

NTTMultiplicationStrategy* NTTMultiplicationStrategy::getInstance() {
  if (!instance) { 
    instance = new NTTMultiplicationStrategy();
  }
  return instance;
}

GaloisFieldPoly NTTMultiplicationStrategy::multiply(const GaloisFieldPoly &a, const GaloisFieldPoly &b) const {
  std::vector<GaloisFieldElement> zero(a.size(), GaloisFieldElement(0));
  GaloisFieldPoly result(zero);
  Log::info("NTT multiplication logic here");
  return result;
}