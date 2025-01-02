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
      DiscreteTorus(uint32_t x);

      DiscreteTorus(const DiscreteTorus &t);
      DiscreteTorus(const GaloisFieldElement &a);

      uint32_t val() const;

      void operator+=(const DiscreteTorus &t);
      void operator-=(const DiscreteTorus &t);
      void operator*=(const uint32_t c);

      // should replace it to faster algo
      uint32_t modP(uint32_t x);

      friend std::ostream& operator<<(std::ostream &os, const DiscreteTorus &t);

  };

  DiscreteTorus operator+(const DiscreteTorus &t1, const DiscreteTorus &t2);
  DiscreteTorus operator*(const uint32_t c, const DiscreteTorus &t1);

}

class GaloisFieldElement {
  private:
    uint32_t a{};
    uint32_t P = Params::P;
  
    uint32_t modP(uint32_t x);

  public:
    GaloisFieldElement(); 

    GaloisFieldElement(const GaloisFieldElement &a);
    GaloisFieldElement(const uint32_t &x);
    GaloisFieldElement(const galoisfield::DiscreteTorus &t);

    uint32_t val() const;

    void operator+=(const GaloisFieldElement &b);
    void operator-=(const GaloisFieldElement &a);
    void operator*=(const GaloisFieldElement &b);

    GaloisFieldElement& operator=(const GaloisFieldElement& other);

    GaloisFieldElement& operator=(GaloisFieldElement&& other) noexcept;


    friend std::ostream& operator<<(std::ostream &os, const GaloisFieldElement &a);
};

bool operator==(const GaloisFieldElement &a1, const GaloisFieldElement&a2);
GaloisFieldElement operator+(const GaloisFieldElement &a, const GaloisFieldElement &b);
GaloisFieldElement operator*(const GaloisFieldElement a, const GaloisFieldElement &b);


#endif