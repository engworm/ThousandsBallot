#ifndef TORUS_HPP
#define TORUS_HPP

#include <cstdint>
#include "params/params.hpp"
#include "operator/Montgomery.hpp"

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

    DiscreteTorus(const DiscreteTorus &tlwe);

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

#endif 
