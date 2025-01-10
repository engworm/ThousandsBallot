#include <iostream>
#include <vector>
#include <boost/program_options.hpp>
#include "params/params.hpp"
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
              "N =", Params::N, "\n", 
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
  if (!SetUpNttConstants::setup()) {
    Log::error("NTT is not ready");
  }
#endif

  std::vector<uint32_t> secret(Params::n, 0);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 1);
  for (uint32_t i = 0; i < Params::n; ++i) {
    secret[i] = dis(gen);
  }
  DiscreteTLWE tlwe = EncryptDiscreteTLWE::encrypt(10, secret);
  Log::debug("tlwe:", tlwe);

  DiscreteTorus ans = DecryptDiscreteTLWE::decrypt(tlwe, secret);
  Log::debug("tlwe:", ans);

  IntPoly intpoly1({1, 1, 1, 1});
  DiscreteTorusPoly toruspoly2({0, 1, 0, 0});

  DiscreteTorusPoly toruspoly = intpoly1 * toruspoly2;
  Log::debug("toruspoly:", toruspoly);


  Log::debug("NTT domain param = {",
              "\n",
              "P =", NttParams::P, "\n", 
              "N =", NttParams::N, "\n", 
              "ψ =", NttParams::psi, "\n", 
              "ω =", NttParams::omega, "\n}");
    
  std::vector<GaloisFieldElement> psi_power_table(NttParams::N);
  psi_power_table[0] = 1;
  for (int i = 0; i < NttParams::N; ++i) {
    psi_power_table[i] = psi_power_table[i-1] * NttParams::psi;
  }

  auto bit_reverse = [](uint32_t n, uint32_t log2n) {
          uint32_t ans = 0;
          for (uint32_t i = 0; i < log2n; ++i) {
              ans = (ans << 1) | (n & 1);
              n >>= 1;
          }
          return ans;
      };
    
  std::vector<GaloisFieldElement> psi_power_table_bit_reversed_order(NttParams::N);
  for (int i = 0; i < NttParams::N; ++i) {
    int rev_i = bit_reverse(i, std::log2(NttParams::N));
    std::cout << rev_i << std::endl;
    psi_power_table_bit_reversed_order[rev_i] = psi_power_table[i];
  }

  Log::debug("psi_powe_table_bit_reversed_order",  psi_power_table_bit_reversed_order[0], psi_power_table_bit_reversed_order[1], psi_power_table_bit_reversed_order[2], psi_power_table_bit_reversed_order[3]); 

  GaloisFieldPoly p1 = intpoly1;
  GaloisFieldPoly p2 = toruspoly2;

  GaloisFieldPoly p3 = p1 * p2;
  Log::debug("p3:", p3);

  DiscreteTorusPoly toruspoly3 = p3;
  Log::debug("toruspoly3:", toruspoly3);

  return 0;
}