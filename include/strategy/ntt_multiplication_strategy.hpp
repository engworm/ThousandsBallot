#ifndef NTT_MULTIPLICATION_STRATEGY_HPP
#define NTT_MULTIPLICATION_STRATEGY_HPP

#include <vector>
#include <memory>
#include "strategy/multiplication_strategy.hpp"
#include "strategy/ntt_multiplication_strategy.hpp"
#include "structure/galoisfieldpoly.hpp"
#include "utility/log.hpp"

// Singleton Pattern
class NTTMultiplicationStrategy : public MultiplicationStrategy {
private:
  uint32_t P; 
  uint32_t N;

  uint32_t N_inverse;
  uint32_t psi;
  uint32_t psi_inverse;
  uint32_t omega;

  std::vector<GaloisFieldElement> psi_power_table;
  std::vector<GaloisFieldElement> psi_power_table_bit_reversed_order;
  std::vector<GaloisFieldElement> psi_inverse_power_table;
  std::vector<GaloisFieldElement> psi_inverse_power_table_bit_reversed_order;

  static std::shared_ptr<NTTMultiplicationStrategy> instance;
  NTTMultiplicationStrategy(uint32_t P, uint32_t N);

  void init_psi_power_table(uint32_t N);
  void init_psi_power_table_bit_reversed_order(uint32_t N);
  void init_psi_inverse_power_table(uint32_t N);
  void init_psi_inverse_power_table_bit_reversed_order(uint32_t N);

  void forward_NTT(GaloisFieldPoly &a) const;
  void inverse_NTT(GaloisFieldPoly &a) const;

  bool setup(uint32_t P, uint32_t N);
  uint32_t inv(GaloisFieldElement x);    // 戻値の型をGaloisFieldElementにする！
  GaloisFieldElement search_2N_root_of_unity(int seed);
  bool check_2N_primitive_root_of_unitiy(GaloisFieldElement const &psi);
  GaloisFieldElement search_2N_primitive_root_of_unity();

public:
  static std::shared_ptr<NTTMultiplicationStrategy> getInstance(uint32_t P, uint32_t N);
  GaloisFieldPoly multiply(GaloisFieldPoly &a, GaloisFieldPoly &b) const override ;
};

#endif 