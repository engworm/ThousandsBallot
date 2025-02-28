#include "structure/torus.hpp"
#include "utility/log.hpp"
#include "factory/modulus_factory.hpp"

std::shared_ptr<ModulusFactory> DiscreteTorus::modulus_factory = nullptr;

DiscreteTorus::DiscreteTorus() : x(0) {};
DiscreteTorus::DiscreteTorus(uint32_t x) : x(x) {
        if (x >= this->q) {
          Log::error("Discrete Torus Element must be less than P");
        }
      };

DiscreteTorus::DiscreteTorus(const DiscreteTorus &t) {
  this->x = t.x;
  this->q = t.q;
  return;
};

uint32_t DiscreteTorus::val() const {
  return this->x;
};

void DiscreteTorus::operator+=(const DiscreteTorus &t) {
  uint32_t tmp = this->x + t.x;
  this->x = modulus_factory->modulus(tmp);
  return;
};

void DiscreteTorus::operator-=(const DiscreteTorus &t) {
  uint32_t tmp = this->x + (this->q - t.x);
  this->x = modulus_factory->modulus(tmp);
  return;
};

void DiscreteTorus::operator*=(const uint32_t c) {
  this->x = modulus_factory->modulus((uint64_t)this->x * c); 
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

DiscreteTorus::DiscreteTorus(const GaloisFieldElement &a) : x(a.val()) {};