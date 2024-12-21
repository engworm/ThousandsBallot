#ifndef TLWE_HPP
#define TLWE_HPP

#include <cstdint>
#include <vector>
#include "torus.hpp"
#include "params/params.hpp"

class DiscreteTLWE {
  private:
    int n = Params::n;
    std::uint32_t prime = Params::P;
    std::vector<DiscreteTorus> v;

  public:
    DiscreteTLWE(std::vector<DiscreteTorus> v) : v(v) { 
      return; 
    };
    DiscreteTLWE(const DiscreteTLWE &tlwe);
    DiscreteTorus operator[](int i) const { return v[i]; };
    int len() { return this->v.size(); };

    friend std::ostream& operator<<(std::ostream &os, const DiscreteTLWE &tlwe) {
      for (auto torus: tlwe.v) {
        os << torus.val() << ' ';
      }
    return os;
  }

};

DiscreteTLWE::DiscreteTLWE(const DiscreteTLWE &tlwe) {
  this->v = tlwe.v;
}

DiscreteTLWE operator+(const DiscreteTLWE &a, const DiscreteTLWE &b) {
  DiscreteTLWE c = a;
  for (int i = 0; i < c.len(); ++i) {
    c[i] += b[i];
  }
  return c;
};

#endif	