#ifndef NTT_HPP
#define NTT_HPP

#include <iostream>
#include <cstdint>
#include <random>
#include "params/params.hpp"
#include "structure/galoisfield.hpp"
#include "utility/log.hpp"

class SetUpNttConstants {
  public:
    static bool setup() {
      NttParams::P = Params::P;
      NttParams::N = Params::N;

      NttParams::psi = search_2N_primitive_root_of_unity().val();
      NttParams::omega = NttParams::psi*NttParams::psi;

      return true;
    }
  
  private:
    static GaloisFieldElement search_2N_root_of_unity(int seed) {
      std::mt19937 gen(seed);
      std::uniform_int_distribution<uint32_t> dis(0, Params::P-1);
    
      GaloisFieldElement x(dis(gen));
      GaloisFieldElement psi = 1; 

      if ((NttParams::P-1)%(2*Params::N) != 0) {
        Log::error("P-1 is not divisible by 2N");
      }

      for (int i = 0; i < (Params::P-1)/(2*Params::N); ++i) {
        psi *= x;
      }
    
      return psi;
    }
    
    // check if psi is 2N-th primitive root of unity
    static bool check_2N_primitive_root_of_unitiy(GaloisFieldElement const &psi) {
      GaloisFieldElement psi_pow = 1;
      for (int i = 0; i < Params::N; ++i) {
        psi_pow *= psi;
      }

      if (psi_pow == NttParams::P-1 && psi_pow*psi_pow == 1) {
        return true;
      } else {
        return false;
      }
    }
    
    static GaloisFieldElement search_2N_primitive_root_of_unity() {
      int seed = 0;
      GaloisFieldElement psi = search_2N_root_of_unity(seed);
      while (!check_2N_primitive_root_of_unitiy(psi)) {
        seed++;
        psi = search_2N_root_of_unity(seed);
      }
      return psi;
    }
};

#endif
