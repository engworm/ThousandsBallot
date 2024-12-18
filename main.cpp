#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include "params/params.hpp"
#include "include/structure/torus.hpp"
#include "include/structure/tlwe.hpp"
#include "include/operator/Montgomery.hpp"

int main() {

  DiscreteTorus a(Consts::P-30), b(10);
  DiscreteTorus c = a + b;
  std::cout << c.val() << std::endl;

  DiscreteTorus d = 10 * a;
  std::cout << d.val() << std::endl;

  if (Consts::mu != constMontgomery()) {
    std::cerr << "something wrong!" << std::endl;
    return -1;
  }

  uint32_t x = reprMontgomery(Consts::P-30);
  uint32_t y = reprMontgomery(10);
  uint32_t z = invReprMontgomery(mulMontgomery(x, y));
  std::cout << z << std::endl;
  std::cout << ((Consts::P-30)*10) % Consts::P << std::endl;
  return 0;
}