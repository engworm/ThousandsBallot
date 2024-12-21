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
    ("help,h", "Help")
    ("param,P", boost::program_options::value<std::vector<uint32_t>>()->multitoken(), "[REQUIRED] Parameter")
    ("mont,M", boost::program_options::value<std::vector<uint32_t>>()->multitoken(), "[REQUIRED] Montgomery Multiplication Parameter.\n e.g. -M r, where R = 2^r.");
                                                                                                
  boost::program_options::variables_map vm;
  try {
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
  } catch (boost::program_options::error &e) {
    Log::print(Log::LogLevel::ERROR, e.what());
    return 1;
  }
  boost::program_options::notify(vm);

  if (vm.count("help")) {
    std::cout << "flag" << std::endl;
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
  Log::print(Log::LogLevel::INFO, "mu =", MontgomeryParams::mu);

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

  return 0;
}