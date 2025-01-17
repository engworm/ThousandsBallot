#ifndef NTT_HPP
#define NTT_HPP

#include <iostream>
#include <cstdint>
#include <random>
#include "params/params.hpp"
#include "params/nttparams.hpp"
#include "structure/galoisfield.hpp"
#include "utility/log.hpp"
#include "utility/extendedEuclidean.hpp"

class SetUpNttConstants {
  public:
    static bool setup();
  
  private:
    static uint32_t inv(GaloisFieldElement x);
    
    static GaloisFieldElement search_2N_root_of_unity(int seed);
    static bool check_2N_primitive_root_of_unitiy(GaloisFieldElement const &psi);

    static GaloisFieldElement search_2N_primitive_root_of_unity();
};

#endif
