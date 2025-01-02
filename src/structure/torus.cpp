#include "structure/torus.hpp"
#include "utility/log.hpp"

namespace galoisfield {
  DiscreteTorus::DiscreteTorus() : x(0) {};
  DiscreteTorus::DiscreteTorus(uint32_t x) : x(x) {
          if (x >= this->P) {
            Log::error("Discrete Torus Element must be less than P");
          }
        };

  DiscreteTorus::DiscreteTorus(const DiscreteTorus &t) {
    this->x = t.x;
    this->P = t.P;
    return;
  };

  uint32_t DiscreteTorus::val() const {
    return this->x;
  };

  void DiscreteTorus::operator+=(const DiscreteTorus &t) {
    uint32_t tmp = this->x + t.x;
    this->x = modP(tmp);
    return;
  };

  void DiscreteTorus::operator-=(const DiscreteTorus &t) {
    uint32_t tmp = this->x + (this->P - t.x);
    this->x = modP(tmp);
    return;
  };

  void DiscreteTorus::operator*=(const uint32_t c) {
    uint32_t X = reprMontgomery(this->x);
    uint32_t C = reprMontgomery(c);
    this->x = invReprMontgomery(mulMontgomery(X, C));
    return;
  };

  uint32_t DiscreteTorus::modP(uint32_t x) {
    return x%this->P;
  };

  std::ostream& operator<<(std::ostream &os, const DiscreteTorus &t) {
    os << t.x;
    return os;
  };


  DiscreteTorus operator+(const DiscreteTorus &t1, const DiscreteTorus &t2) {
    DiscreteTorus t = t1;
    t += t2;
    return t;
  }

  DiscreteTorus operator*(const uint32_t c, const DiscreteTorus &t1) {
    DiscreteTorus t = t1; 
    t *= c;
    return t;
  }

};

galoisfield::DiscreteTorus::DiscreteTorus(const GaloisFieldElement &a) : x(a.val()) {};