#ifndef NTT_HPP
#define NTT_HPP

#include <iostream>
#include <cstdint>
#include <random>
#include "params/nttparams.hpp"
#include "structure/galoisfield.hpp"
#include "utility/log.hpp"
#include "utility/extendedEuclidean.hpp"

class SetUpNttConstants {
  public:
    static bool setup() {
      NttParams::P = Params::P;
      NttParams::N = Params::N;
      NttParams::N_inverse = inv(NttParams::N);

      NttParams::psi = search_2N_primitive_root_of_unity().val();
      NttParams::psi_inverse = inv(NttParams::psi);
      NttParams::omega = NttParams::psi*NttParams::psi;

      Log::info("NTT Constants: {\n",
                "P =", NttParams::P, "\n",
                "N =", NttParams::N, "\n",
                "N^-1 =", NttParams::N_inverse, "\n",
                "ψ =", NttParams::psi, "\n",
                "ψ^-1 =", NttParams::psi_inverse, "\n",
                "ω =", NttParams::omega, "\n}");

      return true;
    }
  
  private:
    static uint32_t inv(GaloisFieldElement x) {
      uint32_t r = extendedEuclidean(Params::P, x.val()).second + Params::P;
      return r;
    }
    
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

      bool res = false;
      if (psi_pow == NttParams::P-1 && psi_pow*psi_pow == 1) {
        res = true;
      } 
      return res;
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
