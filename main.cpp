#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include "params/params.hpp"
#include "include/structure/torus.hpp"
#include "include/structure/tlwe.hpp"
#include "include/operator/Montgomery.hpp"

int main(int argc, char* argv[]) {

  Consts::P = static_cast<uint32_t>(std::stoul(argv[1]));
  Consts::R = static_cast<u_int32_t>(1 << std::stoi(argv[2]));
  Consts::mu = constMontgomery();
  std::cout << "P: " << Consts::P << std::endl;
  std::cout << "R: " << Consts::R << std::endl;
  std::cout << "mu: " << Consts::mu << std::endl;

  if (((uint64_t)Consts::mu*Consts::P)%Consts::R != Consts::R-1) {
     std::cerr << "Error: Montgomery constant mismatch. Expected: " << Consts::R - 1 << ", but got: " << ((uint64_t)Consts::mu*Consts::P)%Consts::R << std::endl;
        return -1;
  }

  DiscreteTorus a(Consts::P-30), b(10);
  DiscreteTorus c = a + b;
  std::cout << c.val() << std::endl;

  DiscreteTorus d = 10 * a;
  std::cout << d.val() << std::endl;

  uint32_t x = reprMontgomery(Consts::P-30);
  uint32_t y = reprMontgomery(10);
  uint32_t z = invReprMontgomery(mulMontgomery(x, y));
  std::cout << z << std::endl;
  std::cout << ((Consts::P-30)*10) % Consts::P << std::endl;
  return 0;
}