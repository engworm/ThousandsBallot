#ifndef DISCRETE_TORUS_GALOISFIELD_HPP
#define DISCRETE_TORUS_GALOISFIELD_HPP

#include <iostream>
#include <cstdint>
#include <random>
#include "params/params.hpp"
#include "operator/Montgomery.hpp"
#include "utility/log.hpp"

class GaloisFieldElement;

namespace galoisfield {
  class DiscreteTorus {
    friend class TorusPoly;

    private:
      uint32_t x;
      uint32_t P = Params::P;

    public:
      DiscreteTorus();
      DiscreteTorus(uint32_t x) : x(x) {
          if (x >= this->P) {
            throw std::invalid_argument("Discrete Torus Element must be less than P");
          }
        }

      DiscreteTorus(const DiscreteTorus &t);
      DiscreteTorus(const GaloisFieldElement &a);

      uint32_t val() const {
        return this->x;
      };

      void operator+=(const DiscreteTorus &t) {
        uint32_t tmp = this->x + t.x;
        this->x = modP(tmp);
        return;
      };

      void operator-=(const DiscreteTorus &t) {
        uint32_t tmp = this->x + (this->P - t.x);
        this->x = modP(tmp);
        return;
      };

      void operator*=(const uint32_t c) {
        uint32_t X = reprMontgomery(this->x);
        uint32_t C = reprMontgomery(c);
        this->x = invReprMontgomery(mulMontgomery(X, C));
        return;
      };

      // should replace it to faster algo
      uint32_t modP(uint32_t x) {
        return x%this->P;
      }

    friend DiscreteTorus operator+(const DiscreteTorus &t1, const DiscreteTorus &t2) {
        DiscreteTorus t = t1;
        t += t2;
        return t;
      }

    friend DiscreteTorus operator*(const uint32_t c, const DiscreteTorus &t1) {
      DiscreteTorus t = t1; 
      t *= c;
      return t;
    }

    friend std::ostream& operator<<(std::ostream &os, const DiscreteTorus &t) {
      os << t.x;
      return os;
    }
  };

  DiscreteTorus::DiscreteTorus(const DiscreteTorus &t) {
    this->x = t.x;
    this->P = t.P;
    return;
  }
}

class GaloisFieldElement {
  private:
    uint32_t a{};
    uint32_t P = Params::P;
  
    uint32_t modP(uint32_t x) {
      return x%this->P;
    }

  public:
    GaloisFieldElement() : a(0) {};

    GaloisFieldElement(const GaloisFieldElement &a) : a(a.a) {}; 
    GaloisFieldElement(const uint32_t &x) : a(x) {}; 
    GaloisFieldElement(const galoisfield::DiscreteTorus &t) : a(t.val()) {}; 

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

    GaloisFieldElement& operator=(const GaloisFieldElement& other) {
      if (this != &other) {
        this->a = other.a;
        this->P = other.P;
      }
      return *this;
    }

    GaloisFieldElement& operator=(GaloisFieldElement&& other) noexcept {
      if (this != &other) {
        this->a = other.a;
        this->P = other.P;
        other.a = 0;
        other.P = 0;
      }
      return *this;
    }


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

galoisfield::DiscreteTorus::DiscreteTorus(const GaloisFieldElement &a) : x(a.val()) {};


#endif