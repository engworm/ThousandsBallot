#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include "params/params.hpp"
#include "include/structure/torus.hpp"
#include "include/structure/tlwe.hpp"
#include "include/operator/Montgomery.hpp"
#include "utility/log.hpp"

int main(int argc, char* argv[]) {

  Params::P = static_cast<uint32_t>(std::stoul(argv[1]));
  Params::n = static_cast<uint32_t>(std::stoul(argv[2]));
  MontgomeryParams::R = static_cast<uint32_t>(1 << std::stol(argv[3]));
  MontgomeryParams::mu = constMontgomeryMu();
  MontgomeryParams::R2 = constMontgomeryR2();
  Log::print(Log::LogLevel::INFO, "P =", Params::P);
  Log::print(Log::LogLevel::INFO, "n =", Params::n);
  Log::print(Log::LogLevel::INFO, "R =", MontgomeryParams::R);
  Log::print(Log::LogLevel::INFO, "mu =", MontgomeryParams::mu);

  if (((uint64_t)MontgomeryParams::mu*Params::P)%MontgomeryParams::R != MontgomeryParams::R-1) {
    Log::print(Log::LogLevel::ERROR, "Error: Montgomery constant mismatch.");
    return -1;
  }

  DiscreteTorus a(Params::P-30), b(10);
  DiscreteTorus c = a + b;
  Log::print(Log::LogLevel::INFO, "c, a:", c, a);

  DiscreteTorus d = 8 * a;
  Log::print(Log::LogLevel::INFO, "d:", d);

  Log::print(Log::LogLevel::INFO, "d:", (8*(Params::P-30))%Params::P);

  return 0;
}