#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include "params/params.hpp"
#include "include/structure/torus.hpp"
#include "include/structure/tlwe.hpp"
#include "include/operator/Montgomery.hpp"
#include "utility/log.hpp"

int main(int argc, char* argv[]) {

  Consts::P = static_cast<uint32_t>(std::stoul(argv[1]));
  Consts::R = static_cast<uint32_t>(1 << std::stol(argv[2]));
  Consts::mu = constMontgomeryMu();
  Consts::R2 = constMontgomeryR2();
  Log::print(Log::LogLevel::INFO, "P =", Consts::P);
  Log::print(Log::LogLevel::INFO, "R =", Consts::R);
  Log::print(Log::LogLevel::INFO, "mu =", Consts::mu);

  if (((uint64_t)Consts::mu*Consts::P)%Consts::R != Consts::R-1) {
     std::cerr << "Error: Montgomery constant mismatch. Expected: " << Consts::R - 1 << ", but got: " << ((uint64_t)Consts::mu*Consts::P)%Consts::R << std::endl;
        return -1;
  }

  DiscreteTorus a(Consts::P-30), b(10);
  DiscreteTorus c = a + b;
  Log::print(Log::LogLevel::INFO, "c, a:", c, a);

  DiscreteTorus d = 8 * a;
  Log::print(Log::LogLevel::INFO, "d:", d);

  Log::print(Log::LogLevel::INFO, "d:", (8*(Consts::P-30))%Consts::P);

  return 0;
}