#ifndef NTT_MULTIPLICATION_STRATEGY_HPP
#define NTT_MULTIPLICATION_STRATEGY_HPP

#include <vector>
#include <memory>
#include "params/nttparams.hpp"
#include "strategy/multiplication_strategy.hpp"
#include "structure/galoisfieldpoly.hpp"
#include "utility/log.hpp"

// Singleton Pattern
class NTTMultiplicationStrategy : public MultiplicationStrategy {
private:
  uint32_t P = NttParams::P;
  uint32_t N = NttParams::N;
  uint32_t N_inverse = NttParams::N_inverse;
  uint32_t psi = NttParams::psi;
  uint32_t psi_inverse = NttParams::psi_inverse;
  uint32_t omega = NttParams::omega;

  static std::vector<GaloisFieldElement> psi_power_table;
  static std::vector<GaloisFieldElement> psi_power_table_bit_reversed_order;
  static std::vector<GaloisFieldElement> psi_inverse_power_table;
  static std::vector<GaloisFieldElement> psi_inverse_power_table_bit_reversed_order;

  static std::shared_ptr<NTTMultiplicationStrategy> instance;
  NTTMultiplicationStrategy();

  void init_psi_power_table();
  void init_psi_power_table_bit_reversed_order();
  void init_psi_inverse_power_table();
  void init_psi_inverse_power_table_bit_reversed_order();

  void forward_NTT(GaloisFieldPoly &a) const;
  void inverse_NTT(GaloisFieldPoly &a) const;

public:
  static std::shared_ptr<NTTMultiplicationStrategy> getInstance();
  GaloisFieldPoly multiply(GaloisFieldPoly &a, GaloisFieldPoly &b) const override ;
};

#endif 