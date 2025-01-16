#include "strategy/ntt_multiplication_strategy.hpp"

NTTMultiplicationStrategy* NTTMultiplicationStrategy::instance = nullptr;
std::vector<GaloisFieldElement> NTTMultiplicationStrategy::psi_power_table;
std::vector<GaloisFieldElement> NTTMultiplicationStrategy::psi_power_table_bit_reversed_order;
std::vector<GaloisFieldElement> NTTMultiplicationStrategy::psi_inverse_power_table;
std::vector<GaloisFieldElement> NTTMultiplicationStrategy::psi_inverse_power_table_bit_reversed_order;

NTTMultiplicationStrategy::NTTMultiplicationStrategy() {
  init_psi_power_table();
  init_psi_power_table_bit_reversed_order();
  init_psi_inverse_power_table();
  init_psi_inverse_power_table_bit_reversed_order();
  Log::info("NTT Multiplication Strategy: ψ power table(bit-reversed) preparation is complete");
}

void NTTMultiplicationStrategy::init_psi_power_table() {
  psi_power_table.reserve(N);
  psi_power_table[0] = 1;
  for (int i = 1; i < N; ++i) {
    psi_power_table[i] = psi_power_table[i-1] * psi;
  }
}

void NTTMultiplicationStrategy::init_psi_inverse_power_table() {
  psi_inverse_power_table.reserve(N);
  psi_inverse_power_table[0] = 1;
  for (int i = 1; i < N; ++i) {
    psi_inverse_power_table[i] = psi_inverse_power_table[i-1] * psi_inverse;
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

void NTTMultiplicationStrategy::init_psi_inverse_power_table_bit_reversed_order() {
  auto bit_reverse = [](uint32_t n, uint32_t log2n) {
    uint32_t ans = 0;
    for (uint32_t i = 0; i < log2n; ++i) {
        ans = (ans << 1) | (n & 1);
        n >>= 1;
    }
    return ans;
  };

  psi_inverse_power_table_bit_reversed_order.reserve(N);
  for (int i = 0; i < N; ++i) {
    int rev_i = bit_reverse(i, std::log2(N));
    psi_inverse_power_table_bit_reversed_order[rev_i] = psi_inverse_power_table[i];
  }
}

void NTTMultiplicationStrategy::forward_NTT(GaloisFieldPoly &a) const {
    uint32_t t = N;
    for (uint32_t m = 1; m < N; m *= 2) {
        t /= 2;
        for (uint32_t i = 0; i < m; ++i) {
            uint32_t j1 = 2 * i * t;
            uint32_t j2 = j1 + t - 1;
            GaloisFieldElement s = psi_power_table_bit_reversed_order[m + i];
            for (uint32_t j = j1; j <= j2; ++j) {
                GaloisFieldElement u = a[j];
                GaloisFieldElement v = a[j + t] * s;
                a[j] = u + v;
                a[j + t] = u - v;
            }
        }
    }
}

void NTTMultiplicationStrategy::inverse_NTT(GaloisFieldPoly &a) const {
  uint32_t t = 1;
  for (uint32_t m = N; m > 1; m /= 2) {
    uint32_t j1 = 0;
    uint32_t h = m / 2;
    for (uint32_t i = 0; i < h; ++i) {
      uint32_t j2 = j1 + t - 1;
      GaloisFieldElement s = psi_inverse_power_table_bit_reversed_order[h + i];
      for (uint32_t j= j1; j <= j2; ++j) {
        GaloisFieldElement u = a[j];
        GaloisFieldElement v = a[j + t];
        a[j] = u + v;
        a[j + t] = (u - v) * s;
      }
      j1 += 2 * t;
    }
    t *= 2;
  }
  for (uint32_t i = 0; i < N; ++i) {
    a[i] = a[i] * N_inverse;
  }
}

NTTMultiplicationStrategy* NTTMultiplicationStrategy::getInstance() {
  if (!instance) { 
    instance = new NTTMultiplicationStrategy();
  }
  return instance;
}

GaloisFieldPoly NTTMultiplicationStrategy::multiply(GaloisFieldPoly &a, GaloisFieldPoly &b) const {
  forward_NTT(a);
  forward_NTT(b);
  GaloisFieldPoly res(a.size());
  for (size_t i = 0; i < N; ++i) {
    res[i] = a[i] * b[i];
  } 
  inverse_NTT(res);
  return res;
}