#include <iostream>
#include <vector>
#include <boost/program_options.hpp>
#include <utility>
#include "params/params.hpp"
#include "params/nttparams.hpp"
#include "structure/tlwe.hpp"
#include "utility/log.hpp"
#include "utility/extendedEuclidean.hpp"
#include "encrypt/encrypt_tlwe.hpp"
#include "decrypt/decrypt_tlwe.hpp"
#include "structure/torus.hpp"
#include "structure/galoisfield.hpp"
#include "structure/toruspoly.hpp"
#include "structure/galoisfieldpoly.hpp"

int main(int argc, char* argv[]) {
  boost::program_options::options_description desc("Options");
  desc.add_options()
    ("help,h", "Help\n")
    ("param,P", boost::program_options::value<std::vector<uint32_t>>()->multitoken(), "[REQUIRED] TFHE Parameter.\nSpecify integer P and n, N, where P is a prime number and n is the length of secret key, N is degree of Polynomial.\ne.g. -P 12289 4 1024\n")
    // ("mont,M", boost::program_options::value<std::vector<uint32_t>>()->multitoken(), "[REQUIRED] Montgomery Multiplication scaling factor R.\nSpecify integer r, so that R = 2^r > P.\ne.g. -M 18\n")
    ("ntt,N", boost::program_options::value<std::vector<uint32_t>>()->multitoken(), "[REQUIRED] NTT Parameter.\nSpecify modulus P, where P is a prime number.\ne.g. -N 12289\n")
    ("seed,S", boost::program_options::value<uint32_t>(), "[OPTIONAL] Seed for random number generator.\n");
                                                                                                
  boost::program_options::variables_map vm;
  try {
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
  } catch (boost::program_options::error &e) {
    throw std::invalid_argument(e.what());
    return 1;
  }
  boost::program_options::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << std::endl;
    return 0;
  }

  if (vm.count("param")) {
    std::vector<uint32_t> P = vm["param"].as<std::vector<uint32_t>>();
    Params::q = P[0];
    Params::n = P[1];
    Params::N = P[2];
  }
  else {
    return 1;
  }

  // if (vm.count("mont")) {
    // std::vector<uint32_t> M = vm["mont"].as<std::vector<uint32_t>>();
    // MontgomeryParams::R = 1 << M[0];
    // // P ans R should be coprime
    // if (!isCoprime(Params::q, MontgomeryParams::R)) {
      // Log::error("q and R must be coprime");
      // return 1;
    // }
    // MontgomeryParams::mu = constMontgomeryMu();
    // MontgomeryParams::R2 = constMontgomeryR2();
  // }
  // else {
    // return 1;
  // }

  Log::debug("param = {\n",
              "q =", Params::q, "\n", 
              "n =", Params::n, "\n", 
              "N =", Params::N, "\n}");

  // Log::debug("Montgomery param = {\n",
              // "R =", MontgomeryParams::R, "\n", 
              // "μ =", MontgomeryParams::mu, "\n", 
              // "R^2 =", MontgomeryParams::R2, "\n}");

  // if (((uint64_t)MontgomeryParams::mu*Params::q)%MontgomeryParams::R != MontgomeryParams::R-1) {
    // Log::error("Montgomery constant mismatched");
    // return 1;
  // }

  /* 
  Torusの加法と減法をオーバーフローさせないために，
  2P < 2^32 である必要がある
  */
  if (Params::q > (1<<31)) {
    Log::error("2q must be less than 2^32");
  }

#ifdef NTT
  Log::info("Polynomial Multiplication Method: [ NTT ]");
    if (vm.count("ntt")) {
    std::vector<uint32_t> X = vm["ntt"].as<std::vector<uint32_t>>();
    NTTParams::P = X[0];
    NTTParams::N = Params::N;
    Log::debug("NTT param = {\n",
              "P =", NTTParams::P, "\n",
              "N =", NTTParams::N, "\n}");
  }
  #ifdef NTT_DEBUG
    Log::info("NTT Debug Mode: [ ON ]");
  #endif
#else
  Log::info("Polynomial Multiplication Method: [ Naive ]");
  Log::warn("Naive polynomial multiplication has been selected. This method is less efficient and may result in slower performance compared to NTT.");
#endif

  uint32_t seed = 0;
  if (vm.count("seed")) {
    seed = vm["seed"].as<uint32_t>();
    std::srand(seed);
  }
  std::mt19937 gen(seed);


  std::uniform_int_distribution<uint32_t> dis_poly(0, Params::q-1);

  std::vector<uint32_t> coeffs1(Params::N);
  std::vector<DiscreteTorus> coeffs2(Params::N);
  for (auto& coeff : coeffs1) {
      coeff = dis_poly(gen);
  }
  for (auto& coeff : coeffs2) {
      coeff = dis_poly(gen);
  }

  // IntPoly intpoly1({1, 1, 1, 1});
  // DiscreteTorusPoly toruspoly2({0, 1, 0, 0});
  IntPoly intpoly1(coeffs1);
  DiscreteTorusPoly toruspoly2(coeffs2);

  Log::debug("intpoly1:", intpoly1);
  Log::debug("toruspoly2:", toruspoly2);

  DiscreteTorusPoly toruspoly3 = std::move(intpoly1 * toruspoly2);
  Log::debug("toruspoly3:", toruspoly3);

  return 0;
}