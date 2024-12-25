#ifndef TLWE_HPP
#define TLWE_HPP

#include <iostream>
#include <cstdint>
#include <vector>
#include <random>
#include "torus.hpp"
#include "params/params.hpp"

class DiscreteTLWE {
  private:
    int n = Params::n;
    std::uint32_t prime = Params::P;
    std::vector<DiscreteTorus> v;

  public:
    DiscreteTLWE(const uint32_t message, const std::vector<uint32_t> &secret) {
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> dis(0, this->prime-1);

      DiscreteTorus b(message);
      for (int i = 0; i < this->n; ++i) {
          uint32_t random_value = dis(gen);
          this->v.push_back(DiscreteTorus(random_value));
          b += secret[i] * DiscreteTorus(random_value); 
      }
      v.push_back(b);
    }

    // DiscreteTLWE(std::vector<DiscreteTorus> v) : v(v) { 
      // return; 
    // };

    DiscreteTLWE(const DiscreteTLWE &tlwe);
    DiscreteTorus operator[](int i) const { return v[i]; };
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
  this->v = tlwe.v;
}

DiscreteTLWE operator+(const DiscreteTLWE &a, const DiscreteTLWE &b) {
  DiscreteTLWE c = a;
  c += b;
  return c;
}

#endif	
