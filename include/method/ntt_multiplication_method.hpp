#ifndef NTT_MULTIPLICATION_METHOD_HPP
#define NTT_MULTIPLICATION_METHOD_HPP

#include <vector>
#include <memory>
#include "method/multiplication_method.hpp"
#include "structure/galoisfieldpoly.hpp"
#include "utility/log.hpp"

class NTTMultiplicationMethod : public MultiplicationMethod {
private:
  uint32_t P; 
  uint32_t N;

  GaloisFieldElement N_inverse;
  GaloisFieldElement psi;
  GaloisFieldElement psi_inverse;
  GaloisFieldElement omega;

  std::vector<GaloisFieldElement> psi_power_table;
  std::vector<GaloisFieldElement> psi_power_table_bit_reversed_order;
  std::vector<GaloisFieldElement> psi_inverse_power_table;
  std::vector<GaloisFieldElement> psi_inverse_power_table_bit_reversed_order;

  static std::shared_ptr<NTTMultiplicationMethod> instance;
  NTTMultiplicationMethod(uint32_t P, uint32_t N);

  void init_psi_power_table(uint32_t N);
  void init_psi_power_table_bit_reversed_order(uint32_t N);
  void init_psi_inverse_power_table(uint32_t N);
  void init_psi_inverse_power_table_bit_reversed_order(uint32_t N);

  void forward_NTT(GaloisFieldPoly &a) const;
  void inverse_NTT(GaloisFieldPoly &a) const;

  bool setup(uint32_t P, uint32_t N);
  GaloisFieldElement inv(GaloisFieldElement x);   
  GaloisFieldElement search_2N_root_of_unity(int seed);
  bool check_2N_primitive_root_of_unitiy(GaloisFieldElement const &psi);
  GaloisFieldElement search_2N_primitive_root_of_unity();

  GaloisFieldPoly multiply(GaloisFieldPoly &a, GaloisFieldPoly &b) const;
  GaloisFieldPoly multiply_debug(GaloisFieldPoly &a, GaloisFieldPoly &b) const;

public:
  static std::shared_ptr<NTTMultiplicationMethod> getInstance(uint32_t P, uint32_t N);
  DiscreteTorusPoly multiply(IntPoly &poly1, DiscreteTorusPoly &poly2) const override;
};

#endif 