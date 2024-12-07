#include <cstdint>
#include <vector>
#include "torus.hpp"

class TLWE {
  private:
    int n;
    std::uint32_t prime;
    std::vector<DiscreteTorus> x;

  public:
  TLWE(int n, std::uint32_t prime) : n(n), prime(prime) { return; };
  TLWE(const TLWE &tlwe);
  DiscreteTorus operator[](int i) const { return x[i]; };
  int len() { return this->n+1; };

};

TLWE::TLWE(const TLWE &tlwe) {
  n = tlwe.n;
  prime = tlwe.prime;
  x = tlwe.x;
}

TLWE operator+(const TLWE &a, const TLWE &b) {
  TLWE c = a;
  for (int i = 0; i < c.len(); ++i) {
    c[i] += b[i];
  }
  return c;
};
