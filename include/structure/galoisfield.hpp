#ifndef GALOISFIELD_HPP
#define GALOISFIELD_HPP

#include <iostream>
#include <cstdint>
#include <random>
#include "params/params.hpp"
#include "operator/Montgomery.hpp"
#include "structure/torus.hpp"

class GaloisFieldElement {
  private:
    uint32_t a{};
    uint32_t P = Params::P;
  
    uint32_t modP(uint32_t x) {
      return x%this->P;
    }

  public:
    GaloisFieldElement() : a(0) {};
    GaloisFieldElement(uint32_t a) : a(a) {
      if (a >= this->P) {
        throw std::invalid_argument("Galois Field Element must be less than P");
      }
    }

    // DiscreteTorusを渡すコピーコンストラクタが必要
    // uint32_tを渡すコピーコンストラクタが必要
    GaloisFieldElement(const GaloisFieldElement &a); 
    GaloisFieldElement(const DiscreteTorus &t); 

    uint32_t val() const {
      return this->a;
    }

    void operator+=(const GaloisFieldElement &b) {
      uint32_t tmp = this->a + b.a;
      this->a = modP(tmp);
      return;
    };  

    void operator-=(const GaloisFieldElement &a) {
      uint32_t tmp = this->a + (this->P - a.a);
      this->a = modP(tmp);
      return;
    };

    void operator*=(const GaloisFieldElement &b) {
      uint32_t A = reprMontgomery(this->a);
      uint32_t B = reprMontgomery(b.a);
      this->a = invReprMontgomery(mulMontgomery(A, B));
      return;
    };


    friend bool operator==(const GaloisFieldElement &a1, const GaloisFieldElement&a2) {
      return a1.a == a2.a;
    }

    friend GaloisFieldElement operator+(const GaloisFieldElement &a, const GaloisFieldElement &b) {
      GaloisFieldElement c = a;
      c += b;
      return c;
    }

    friend GaloisFieldElement operator*(const GaloisFieldElement a, const GaloisFieldElement &b) {
      GaloisFieldElement c = a; 
      c *= b;
      return c;
    }

    friend std::ostream& operator<<(std::ostream &os, const GaloisFieldElement &a) {
      os << a.a;
      return os;
    }
};

GaloisFieldElement::GaloisFieldElement(const GaloisFieldElement &a) {
  this->a = a.a;
  return;
}

GaloisFieldElement::GaloisFieldElement(const DiscreteTorus &t) {
  this->a = t.val();
  return;
}

class InitializeGaloisField : public GaloisFieldElement {
  public:
    static bool initialize() {
      NttParams::P = Params::P;
      NttParams::N = Params::N;
      NttParams::psi = search_2N_primitive_root_of_unity().val();

      GaloisFieldElement a = 1;
      for (int i = 0; i < Params::N; ++i) {
          a *= NttParams::psi;
      }
      std::cout << "psi^" << Params::N << " = " << a.val() << std::endl;
      if (a.val() != Params::P-1) {
        throw std::invalid_argument("psi is not primitive root of unity");
        return false;
      }

      a *= a;
      std::cout << "psi^" << 2*Params::N << " = " << a.val() << std::endl;
      if (a.val() != 1) {
        throw std::invalid_argument("psi is not primitive root of unity");
        return false;
      }
      return true;
    }
  
  private:
    static GaloisFieldElement search_2N_root_of_unity(int seed) {
      std::mt19937 gen(seed);
      std::uniform_int_distribution<uint32_t> dis(0, Params::P-1);
    
      GaloisFieldElement x(dis(gen));
      GaloisFieldElement psi = 1; 
      for (int i = 0; i < (Params::P-1)/(2*Params::N); ++i) {
        psi *= x;
      }
    
      std::cout << "psi = " << psi.val() << std::endl;
      return psi;
    }
    
    static bool check_2N_primitive_root_of_unitiy(GaloisFieldElement &psi) {
      GaloisFieldElement psi_pow = 1;
      for (int i = 1; i < Params::N; ++i) {
        psi_pow *= psi;
        // std::cout << "psi^" << i << " = " << psi_pow.a << std::endl;
      }
      if (psi_pow == 1) {
        return false;
      } else {
        return true;
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