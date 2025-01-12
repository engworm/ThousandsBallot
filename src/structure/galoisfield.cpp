#include <utility>
#include "structure/galoisfield.hpp"
#include "structure/torus.hpp"
#include "utility/log.hpp"

uint32_t GaloisFieldElement::modP(uint32_t x) {
  return x%this->P;
}

GaloisFieldElement::GaloisFieldElement() : a(0) {};

GaloisFieldElement::GaloisFieldElement(const GaloisFieldElement &a) : a(a.a) {}; 
GaloisFieldElement::GaloisFieldElement(const uint32_t &x) : a(x) {}; 
GaloisFieldElement::GaloisFieldElement(const DiscreteTorus &t) : a(t.val()) {}; 

GaloisFieldElement::GaloisFieldElement(uint32_t &&x) noexcept : a(std::move(x)) {};

uint32_t GaloisFieldElement::val() const {
  return this->a;
}

void GaloisFieldElement::operator+=(const GaloisFieldElement &b) {
  uint32_t tmp = this->a + b.a;
  this->a = modP(tmp);
  return;
};  

void GaloisFieldElement::operator-=(const GaloisFieldElement &a) {
  uint32_t tmp = this->a + (this->P - a.a);
  this->a = modP(tmp);
  return;
};

void GaloisFieldElement::operator*=(const GaloisFieldElement &b) {
  uint32_t A = reprMontgomery(this->a);
  uint32_t B = reprMontgomery(b.a);
  this->a = invReprMontgomery(mulMontgomery(A, B));
  return;
};

GaloisFieldElement& GaloisFieldElement::operator=(const GaloisFieldElement& other) {
  if (this != &other) {
    this->a = other.a;
    this->P = other.P;
  }
  return *this;
}

GaloisFieldElement& GaloisFieldElement::operator=(GaloisFieldElement&& other) noexcept {
  if (this != &other) {
    this->a = other.a;
    this->P = other.P;
    other.a = 0;
    other.P = 0;
  }
  return *this;
}


std::ostream& operator<<(std::ostream &os, const GaloisFieldElement &a) {
  os << a.a;
  return os;
}

bool operator==(const GaloisFieldElement &a1, const GaloisFieldElement&a2) {
  return a1.val() == a2.val();
}

GaloisFieldElement operator+(const GaloisFieldElement &a, const GaloisFieldElement &b) {
  GaloisFieldElement c = a;
  c += b;
  return c;
}

GaloisFieldElement operator*(const GaloisFieldElement a, const GaloisFieldElement &b) {
  GaloisFieldElement c = a; 
  c *= b;
  return c;
}
