#include <iostream>
#include <vector>
#include <boost/program_options.hpp>
#include "params/params.hpp"
#include "include/structure/torus.hpp"
#include "include/structure/tlwe.hpp"
#include "include/operator/Montgomery.hpp"
#include "utility/log.hpp"

int main(int argc, char* argv[]) {
  boost::program_options::options_description desc("Options");
  desc.add_options()
    ("help,h", "Help\n")
    ("param,P", boost::program_options::value<std::vector<uint32_t>>()->multitoken(), "[REQUIRED] TFHE Parameter.\nSpecify integer P and n, where P is a prime number and n is the length of secret key.\ne.g. -P 12289 4\n")
    ("mont,M", boost::program_options::value<std::vector<uint32_t>>()->multitoken(), "[REQUIRED] Montgomery Multiplication scaling factor R.\nSpecify integer r, so that R = 2^r > P.\ne.g. -M 18\n");
                                                                                                
  boost::program_options::variables_map vm;
  try {
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
  } catch (boost::program_options::error &e) {
    Log::print(Log::LogLevel::ERROR, e.what());
    return 1;
  }
  boost::program_options::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << std::endl;
    return 0;
  }

  if (vm.count("param")) {
    std::vector<uint32_t> P = vm["param"].as<std::vector<uint32_t>>();
    Params::P = P[0];
    Params::n = P[1];
  }
  else {
    return 1;
  }

  if (vm.count("mont")) {
    std::vector<uint32_t> M = vm["mont"].as<std::vector<uint32_t>>();
    MontgomeryParams::R = 1 << M[0];
    MontgomeryParams::mu = constMontgomeryMu();
    MontgomeryParams::R2 = constMontgomeryR2();
  }
  else {
    return 1;
  }

  Log::print(Log::LogLevel::INFO, "P =", Params::P);
  Log::print(Log::LogLevel::INFO, "n =", Params::n);
  Log::print(Log::LogLevel::INFO, "R =", MontgomeryParams::R);
  Log::print(Log::LogLevel::INFO, "μ =", MontgomeryParams::mu);
  Log::print(Log::LogLevel::INFO, "R^2 =", MontgomeryParams::R2);

  if (((uint64_t)MontgomeryParams::mu*Params::P)%MontgomeryParams::R != MontgomeryParams::R-1) {
    Log::print(Log::LogLevel::ERROR, "Error: Montgomery constant mismatch.");
    return 1;
  }

  DiscreteTorus a(Params::P-30), b(10);
  DiscreteTorus c = a + b;
  Log::print(Log::LogLevel::INFO, "c, a:", c, a);

  DiscreteTorus d = 8 * a;
  Log::print(Log::LogLevel::INFO, "d:", d);

  Log::print(Log::LogLevel::INFO, "d:", (8*(Params::P-30))%Params::P);

  std::vector<uint32_t> secret(Params::n, 0);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 1);
  for (uint32_t i = 0; i < Params::n; ++i) {
    secret[i] = dis(gen);
  }
  DiscreteTLWE tlwe(10, secret);
  Log::print(Log::LogLevel::INFO, "tlwe:", tlwe);

  return 0;
}