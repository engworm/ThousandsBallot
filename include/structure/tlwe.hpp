#ifndef TLWE_HPP
#define TLWE_HPP

#include <iostream>
#include <cstdint>
#include <vector>
#include <random>
#include "torus.hpp"
#include "params/params.hpp"

class DiscreteTLWE {

  friend class EncryptDiscreteTLWE;
  friend class DecryptDiscreteTLWE;

  private:
    int n{}; 
    std::uint32_t P = Params::P;
    std::vector<DiscreteTorus> v;

  protected:
    DiscreteTorus operator[](int i) const { return v[i]; };

  public:
    DiscreteTLWE(const uint32_t n) : n(n) {};
    DiscreteTLWE(const DiscreteTLWE &tlwe);

    int len() const { return this->v.size(); };

    friend std::ostream& operator<<(std::ostream &os, const DiscreteTLWE &tlwe) {
      for (auto torus: tlwe.v) {
        os << torus.val() << ' ';
      }
      return os;
    }

    void operator+=(const DiscreteTLWE &tlwe) {
      for (int i = 0; i < this->len(); ++i) {
        this->v[i] += tlwe[i];
      }
    }

    void operator*=(const uint32_t c) {
      for (int i = 0; i < this->len(); ++i) {
        this->v[i] *= c;
      }
    }
};

DiscreteTLWE::DiscreteTLWE(const DiscreteTLWE &tlwe) {
  this->n = tlwe.n;
  this->v = tlwe.v;
}

DiscreteTLWE operator+(const DiscreteTLWE &a, const DiscreteTLWE &b) {
  DiscreteTLWE c = a;
  c += b;
  return c;
}

#endif	
