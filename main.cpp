#include <iostream>
#include "params/params.hpp"
#include "include/structure/torus.hpp"
#include "include/structure/tlwe.hpp"
#include "include/operator/Montgomery.hpp"

int main() {

  DiscreteTorus a(Consts::P-11), b(10);
  DiscreteTorus c = a + b;
  std::cout << c.val() << std::endl;

  DiscreteTorus d = 3 * a;
  std::cout << d.val() << std::endl;

  // DiscreteTorus e = 3 * b;
  // std::cout << e.val() << std::endl;

  // std::vector<DiscreteTorus> A;
  // A.emplace_back(0);
  // A.emplace_back(1);
  // A.emplace_back(2);

  // DiscreteTLWE x(A);

  if (Consts::mu != constMontgomery()) {
    std::cerr << "something wrong!" << std::endl;
    return -1;
  }

  uint32_t x = reprMontgomery(Consts::P-11);
  uint32_t y = reprMontgomery(3);
  uint32_t z = invReprMontgomery(mulMontgomery(x, y));
  std::cout << z << std::endl;
  std::cout << ((Consts::P-11)*3) % Consts::P << std::endl;
  return 0;
}