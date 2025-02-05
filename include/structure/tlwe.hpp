#ifndef TLWE_HPP
#define TLWE_HPP

#include <iostream>
#include <cstdint>
#include <vector>
#include <random>
#include "params/params.hpp"
#include "structure/galoisfield.hpp"
#include "structure/torus.hpp"

class DiscreteTLWE {

  friend class EncryptDiscreteTLWE;
  friend class DecryptDiscreteTLWE;

  private:
    int n{}; 
    std::uint32_t q = Params::q;
    std::vector<DiscreteTorus> v;

  protected:
    DiscreteTorus operator[](int i) const { return v[i]; };

  public:
    DiscreteTLWE(const uint32_t n) : n(n) {};
    DiscreteTLWE(const DiscreteTLWE &tlwe);
    DiscreteTLWE(DiscreteTLWE &&tlwe) noexcept 
                          : n(tlwe.n), q(tlwe.q), v(std::move(tlwe.v)) {}; 

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
