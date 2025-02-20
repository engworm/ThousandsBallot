#include "strategy/ntt_multiplication_strategy.hpp"
#include "utility/extendedEuclidean.hpp"
#include "structure/toruspoly.hpp"

std::shared_ptr<NTTMultiplicationStrategy> NTTMultiplicationStrategy::instance = nullptr;

NTTMultiplicationStrategy::NTTMultiplicationStrategy(uint32_t P, uint32_t N) : P(P), N(N) {
  setup(this->P, this->N);
  init_psi_power_table(this->N);
  init_psi_power_table_bit_reversed_order(this->N);
  init_psi_inverse_power_table(this->N);
  init_psi_inverse_power_table_bit_reversed_order(this->N);
  Log::info("NTT Multiplication Strategy: ψ power table(bit-reversed) preparation is complete");
}

bool NTTMultiplicationStrategy::setup(uint32_t P, uint32_t N) {
  this->N_inverse = inv(this->N);

  this->psi = search_2N_primitive_root_of_unity().val();
  this->psi_inverse = inv(this->psi);
  this->omega = this->psi*this->psi;

  Log::info("NTT Constants: {\n",
            "P =", this->P, "\n",
            "N =", this->N, "\n",
            "N^-1 =", this->N_inverse, "\n",
            "ψ =", this->psi, "\n",
            "ψ^-1 =", this->psi_inverse, "\n",
            "ω =", this->omega, "\n}");

  return true;
}
  
uint32_t NTTMultiplicationStrategy::inv(GaloisFieldElement x) {
  uint32_t r = extendedEuclidean(this->P, x.val()).second + this->P;
  return r;
}
    
GaloisFieldElement NTTMultiplicationStrategy::search_2N_root_of_unity(int seed) {
  std::mt19937 gen(seed);
  std::uniform_int_distribution<uint32_t> dis(0, this->P-1);
    
  GaloisFieldElement x(dis(gen));
  GaloisFieldElement psi = 1; 

  if ((this->P-1)%(2*this->N) != 0) {
    Log::error("P-1 is not divisible by 2N");
  }

  for (int i = 0; i < (this->P-1)/(2*this->N); ++i) {
    psi *= x;
  }
    
  return psi;
}
    
// check if psi is 2N-th primitive root of unity
bool NTTMultiplicationStrategy::check_2N_primitive_root_of_unitiy(GaloisFieldElement const &psi) {
  GaloisFieldElement psi_pow = 1;
  for (int i = 0; i < this->N; ++i) {
    psi_pow *= psi;
  }

  bool res = false;
  if (psi_pow == this->P-1 && psi_pow*psi_pow == 1) {
    res = true;
  } 
  return res;
}
    
GaloisFieldElement NTTMultiplicationStrategy::search_2N_primitive_root_of_unity() {
  int seed = 0;
  GaloisFieldElement psi = search_2N_root_of_unity(seed);
  while (!check_2N_primitive_root_of_unitiy(psi)) {
    seed++;
    psi = search_2N_root_of_unity(seed);
  }
  return psi;
}

void NTTMultiplicationStrategy::init_psi_power_table(uint32_t N) {
  this->psi_power_table.reserve(N);
  this->psi_power_table[0] = 1;
  for (int i = 1; i < N; ++i) {
    this->psi_power_table[i] = this->psi_power_table[i-1] * this->psi;
  }
}

void NTTMultiplicationStrategy::init_psi_inverse_power_table(uint32_t N) {
  this->psi_inverse_power_table.reserve(N);
  this->psi_inverse_power_table[0] = 1;
  for (int i = 1; i < N; ++i) {
    this->psi_inverse_power_table[i] = this->psi_inverse_power_table[i-1] * this->psi_inverse;
  }
}


// bit-reversed order の処理は共通化したい
void NTTMultiplicationStrategy::init_psi_power_table_bit_reversed_order(uint32_t N) {
  auto bit_reverse = [](uint32_t n, uint32_t log2n) {
    uint32_t ans = 0;
    for (uint32_t i = 0; i < log2n; ++i) {
        ans = (ans << 1) | (n & 1);
        n >>= 1;
    }
    return ans;
  };

  this->psi_power_table_bit_reversed_order.reserve(N);
  for (int i = 0; i < N; ++i) {
    int rev_i = bit_reverse(i, std::log2(N));
    this->psi_power_table_bit_reversed_order[rev_i] = this->psi_power_table[i];
  }
}

void NTTMultiplicationStrategy::init_psi_inverse_power_table_bit_reversed_order(uint32_t N) {
  auto bit_reverse = [](uint32_t n, uint32_t log2n) {
    uint32_t ans = 0;
    for (uint32_t i = 0; i < log2n; ++i) {
        ans = (ans << 1) | (n & 1);
        n >>= 1;
    }
    return ans;
  };

  this->psi_inverse_power_table_bit_reversed_order.reserve(N);
  for (int i = 0; i < N; ++i) {
    int rev_i = bit_reverse(i, std::log2(N));
    this->psi_inverse_power_table_bit_reversed_order[rev_i] = this->psi_inverse_power_table[i];
  }
}

void NTTMultiplicationStrategy::forward_NTT(GaloisFieldPoly &a) const {
    uint32_t t = this->N;
    for (uint32_t m = 1; m < this->N; m *= 2) {
        t /= 2;
        for (uint32_t i = 0; i < m; ++i) {
            uint32_t j1 = 2 * i * t;
            uint32_t j2 = j1 + t - 1;
            GaloisFieldElement s = this->psi_power_table_bit_reversed_order[m + i];
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
  for (uint32_t m = this->N; m > 1; m /= 2) {
    uint32_t j1 = 0;
    uint32_t h = m / 2;
    for (uint32_t i = 0; i < h; ++i) {
      uint32_t j2 = j1 + t - 1;
      GaloisFieldElement s = this->psi_inverse_power_table_bit_reversed_order[h + i];
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
    a[i] = a[i] * this->N_inverse;
  }
}

std::shared_ptr<NTTMultiplicationStrategy> NTTMultiplicationStrategy::getInstance(uint32_t P, uint32_t N) {
  if (instance == nullptr) {
    instance = std::shared_ptr<NTTMultiplicationStrategy>(new NTTMultiplicationStrategy(P, N));
  }
  return instance;
}

GaloisFieldPoly NTTMultiplicationStrategy::multiply_debug(GaloisFieldPoly &poly1, GaloisFieldPoly &poly2) const {
  std::vector<GaloisFieldElement> zero(poly1.size(), GaloisFieldElement(0));
  GaloisFieldPoly result(zero);
  for (size_t i = 0; i < poly1.size(); ++i) {
    for (size_t j = 0; j < poly1.size(); ++j) {
      size_t k = (i + j) % poly1.size();
      if (i + j >= poly1.size()) {
          result[k] -= poly1[j]* poly2[i];
      }
      else {
          result[k] += poly1[j] * poly2[i];
      }
    }
  }
  return result;
}

GaloisFieldPoly NTTMultiplicationStrategy::multiply(GaloisFieldPoly &a, GaloisFieldPoly &b) const {
#ifdef NTT_DEBUG
  return multiply_debug(a, b);
#else
  forward_NTT(a);
  forward_NTT(b);
  GaloisFieldPoly res(this->P, this->N);
  for (size_t i = 0; i < this->N; ++i) {
    res[i] = a[i] * b[i];
  } 
  inverse_NTT(res);
  return res;
#endif
}

DiscreteTorusPoly NTTMultiplicationStrategy::multiply(IntPoly &poly1, DiscreteTorusPoly &poly2) const {
  GaloisFieldPoly gfpoly1 = std::move(poly1);
  GaloisFieldPoly gfpoly2 = std::move(poly2);
  GaloisFieldPoly res = multiply(gfpoly1, gfpoly2);
  DiscreteTorusPoly torus_res = std::move(res);
  return torus_res;
}