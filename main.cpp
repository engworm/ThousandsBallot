#include <iostream>
#include "params/params.hpp"
#include "include/structure/torus.hpp"
#include "include/structure/tlwe.hpp"
#include "include/operator/Montgomery.hpp"

int main() {

  DiscreteTorus a(3), b(10);
  DiscreteTorus c = a + b;
  std::cout << c.val() << std::endl;

  DiscreteTorus d = 3 * a;
  std::cout << d.val() << std::endl;

  DiscreteTorus e = 3 * b;
  std::cout << e.val() << std::endl;

  std::vector<DiscreteTorus> A;
  A.emplace_back(0);
  A.emplace_back(1);
  A.emplace_back(2);

  // DiscreteTLWE x(A);

  if (Consts::mu != constMontgomery()) {
    std::cerr << "something wrong!" << std::endl;
    return -1;
  }

  uint32_t x = reprMontgomery(Consts::P-1);
  uint32_t y = reprMontgomery(10);
  uint32_t z = mulMontgomery(x, y);
  std::cout << invReprMontgomery(z) << std::endl;
  return 0;
}