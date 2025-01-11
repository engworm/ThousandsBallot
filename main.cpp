#include <iostream>
#include <vector>
#include <boost/program_options.hpp>
#include <utility>
#include "params/params.hpp"
#include "params/nttparams.hpp"
#include "structure/tlwe.hpp"
#include "utility/log.hpp"
#include "encrypt/encrypt_tlwe.hpp"
#include "decrypt/decrypt_tlwe.hpp"
#include "structure/torus.hpp"
#include "structure/galoisfield.hpp"
#include "structure/toruspoly.hpp"
#include "structure/galoisfieldpoly.hpp"
#include "operator/ntt.hpp"

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

  Log::debug("param = {\n",
              "P =", Params::P, "\n", 
              "n =", Params::n, "\n", 
              "N =", Params::N, "\n}");

  Log::debug("Montgomery param = {\n",
              "R =", MontgomeryParams::R, "\n", 
              "μ =", MontgomeryParams::mu, "\n", 
              "R^2 =", MontgomeryParams::R2, "\n}");

  if (((uint64_t)MontgomeryParams::mu*Params::P)%MontgomeryParams::R != MontgomeryParams::R-1) {
    Log::error("Montgomery constant mismatched");
    return 1;
  }

  /* 
  Torusの加法と減法をオーバーフローさせないために，
  2P < 2^32 である必要がある
  */
  if (Params::P > (1<<31)) {
    throw std::invalid_argument("2P must be less than 2^32");
  }

#ifdef NTT
  Log::info("Polynomial Multiplication Method: [NTT]");
  if (!SetUpNttConstants::setup()) {
    Log::error("Failed to set up NTT constants");
  }
#else
  Log::info("Polynomial Multiplication Method: [Naive]");
  Log::warn("Naive polynomial multiplication has been selected. This method is less efficient and may result in slower performance compared to NTT.");
#endif

  std::vector<uint32_t> secret(Params::n, 0);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 1);
  for (uint32_t i = 0; i < Params::n; ++i) {
    secret[i] = dis(gen);
  }

  uint32_t message = 10;
  Log::debug("mssg:", message);
  DiscreteTLWE tlwe = EncryptDiscreteTLWE::encrypt(message, secret);
  Log::debug("tlwe:", tlwe);

  DiscreteTorus ans = DecryptDiscreteTLWE::decrypt(tlwe, secret);
  Log::debug("decrypted mssg:", ans);

  IntPoly intpoly1({1, 1, 1, 1});
  DiscreteTorusPoly toruspoly2({0, 1, 0, 0});

  GaloisFieldPoly gfpoly1 = std::move(intpoly1);
  GaloisFieldPoly gfpoly2 = std::move(toruspoly2);

  Log::debug("gfpoly1:", gfpoly1);
  Log::debug("gfpoly2:", gfpoly2);

  GaloisFieldPoly gfpoly3 = gfpoly1 * gfpoly2;
  Log::debug("gfpoly3:", gfpoly3);

  DiscreteTorusPoly toruspoly3 = gfpoly3;
  Log::debug("toruspoly3:", toruspoly3);

  IntPoly intpoly4({1, 1, 1, 1});
  DiscreteTorusPoly toruspoly5({0, 1, 0, 0});

  GaloisFieldPoly gfpoly4 = std::move(intpoly4);
  GaloisFieldPoly gfpoly5 = std::move(toruspoly5);

  GaloisFieldPoly gfpoly6 = gfpoly4 * gfpoly5;
  DiscreteTorusPoly toruspoly6 = gfpoly6;
  Log::debug("toruspoly6:", toruspoly6);

  return 0;
}