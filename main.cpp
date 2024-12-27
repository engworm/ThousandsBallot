#include <iostream>
#include <vector>
#include <boost/program_options.hpp>
#include "params/params.hpp"
#include "structure/torus.hpp"
#include "structure/tlwe.hpp"
#include "operator/Montgomery.hpp"
#include "utility/log.hpp"
#include "encrypt/encrypt_tlwe.hpp"
#include "decrypt/decrypt_tlwe.hpp"
#include "structure/torus_poly.hpp"
#include "structure/poly.hpp"

int main(int argc, char* argv[]) {
  boost::program_options::options_description desc("Options");
  desc.add_options()
    ("help,h", "Help\n")
    ("param,P", boost::program_options::value<std::vector<uint32_t>>()->multitoken(), "[REQUIRED] TFHE Parameter.\nSpecify integer P and n, N, where P is a prime number and n is the length of secret key, N is degree of Polynomial.\ne.g. -P 12289 4 1024\n")
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
    Params::N = P[2];
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
  Log::print(Log::LogLevel::INFO, "N =", Params::N);
  Log::print(Log::LogLevel::INFO, "R =", MontgomeryParams::R);
  Log::print(Log::LogLevel::INFO, "μ =", MontgomeryParams::mu);
  Log::print(Log::LogLevel::INFO, "R^2 =", MontgomeryParams::R2);

  if (((uint64_t)MontgomeryParams::mu*Params::P)%MontgomeryParams::R != MontgomeryParams::R-1) {
    Log::print(Log::LogLevel::ERROR, "Error: Montgomery constant mismatch.");
    return 1;
  }

  /* 
  Torusの加法と減法をオーバーフローさせないために，
  2P < 2^32 である必要がある
  */
  if (Params::P > (1<<31)) {
    throw std::invalid_argument("2P must be less than 2^32");
  }

  std::vector<uint32_t> secret(Params::n, 0);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 1);
  for (uint32_t i = 0; i < Params::n; ++i) {
    secret[i] = dis(gen);
  }
  DiscreteTLWE tlwe = EncryptDiscreteTLWE::encrypt(10, secret);
  Log::print(Log::LogLevel::INFO, "tlwe:", tlwe);

  DiscreteTorus ans = DecryptDiscreteTLWE::decrypt(tlwe, secret);
  Log::print(Log::LogLevel::INFO, "tlwe:", ans);

  Poly poly({1, 1, 1, 1});
  TorusPoly toruspoly({0, 1, 0, 0});
  Log::print(Log::LogLevel::INFO, "toruspoly:", poly * toruspoly);

  return 0;
}