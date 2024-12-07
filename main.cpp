#include <iostream>
#include "include/structure/torus.hpp"

int main() {

  constexpr int32_t P = 7;
  DiscreteTorus a(3, P), b(10, P);
  DiscreteTorus c = a + b;
  std::cout << c.val() << std::endl;

  DiscreteTorus d = 3 * a;
  std::cout << d.val() << std::endl;

  DiscreteTorus e = 3 * b;
  std::cout << e.val() << std::endl;
  return 0;
}