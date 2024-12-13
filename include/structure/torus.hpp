#include <cstdint>

#ifndef TORUS_HPP
#define TORUS_HPP

class DiscreteTorus {
  private:
    uint32_t x;
    uint32_t prime;

  public:
    DiscreteTorus();
    DiscreteTorus(uint32_t x, uint32_t prime) : x(x), prime(prime) {
      this->x = modP(x);
      return;
      };

    uint32_t val() {
      return this->x;
    };

    void operator+=(const DiscreteTorus &t) {
      uint32_t tmp = this->x + t.x;
      this->x = modP(tmp);
      return;
    };

    void operator*=(const uint32_t c) {
      uint64_t tmp = this->x * c;
      this->x = modP(tmp);
      return;
    };

    // should replace it to faster algo
    uint32_t modP(uint32_t x) {
      return x % prime; 
    }

    uint32_t modP(uint64_t x) {
      return x % prime; 
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
};

#endif 
