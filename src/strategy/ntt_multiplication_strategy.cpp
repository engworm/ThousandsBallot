#include "strategy/ntt_multiplication_strategy.hpp"

NTTMultiplicationStrategy* NTTMultiplicationStrategy::instance = nullptr;
std::vector<GaloisFieldElement> NTTMultiplicationStrategy::psi_power_table;
std::vector<GaloisFieldElement> NTTMultiplicationStrategy::psi_power_table_bit_reversed_order;