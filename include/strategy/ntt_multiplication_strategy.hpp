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
  NTTMultiplicationStrategy();

  void init_psi_power_table();
  void init_psi_power_table_bit_reversed_order();

  void trans_NTT(std::vector<GaloisFieldElement> &a) const;
  void trans_INTT(std::vector<GaloisFieldElement> &a) const;

public:
  static NTTMultiplicationStrategy* getInstance();
  GaloisFieldPoly multiply(GaloisFieldPoly &a, GaloisFieldPoly &b) const override ;
};

#endif 