#include <cstdint>
#include <vector>
#include "torus.hpp"

#ifndef TLWE_HPP
#define TLWE_HPP

class DiscreteTLWE {
  private:
    int n;
    std::uint32_t prime;
    std::vector<DiscreteTorus> v;

  public:
    DiscreteTLWE(std::vector<DiscreteTorus> v, std::uint32_t prime) : v(v), prime(prime) { 
      n = v.size()-1;
      return; 
    };
    DiscreteTLWE(const DiscreteTLWE &tlwe);
    DiscreteTorus operator[](int i) const { return v[i]; };
    int len() { return this->n+1; };

};

DiscreteTLWE::DiscreteTLWE(const DiscreteTLWE &tlwe) {
  n = tlwe.n;
  prime = tlwe.prime;
  v = tlwe.v;
}

DiscreteTLWE operator+(const DiscreteTLWE &a, const DiscreteTLWE &b) {
  DiscreteTLWE c = a;
  for (int i = 0; i < c.len(); ++i) {
    c[i] += b[i];
  }
  return c;
};

#endif	