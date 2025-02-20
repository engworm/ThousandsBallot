#ifndef PARSER_HPP
#define PARSER_HPP

#include <boost/program_options.hpp>
#include <random>
#include "params/params.hpp"
#include "params/nttparams.hpp"
#include "utility/log.hpp"

class CommandLineParser {
  private:
    int argc;
    char **argv;
    int seed;

  public:
    std::mt19937 PRNG;

    CommandLineParser(int argc, char **argv) : argc(argc), argv(argv) {
      boost::program_options::options_description desc("Options");
      desc.add_options()
        ("help,h", "Help\n")
        ("param,P", boost::program_options::value<std::vector<uint32_t>>()->multitoken(), "[REQUIRED] TFHE Parameter.\nSpecify q and n, N, where q is a integer ring order and n is the length of secret key, N is degree of Polynomial.\ne.g. -P 12289 4 1024\n")
        // ("mont,M", boost::program_options::value<std::vector<uint32_t>>()->multitoken(), "[REQUIRED] Montgomery Multiplication scaling factor R.\nSpecify integer r, so that R = 2^r > P.\ne.g. -M 18\n")
        ("ntt,N", boost::program_options::value<std::vector<uint32_t>>()->multitoken(), "[REQUIRED] Specify modulus P, where P is a prime number.\ne.g. -N 12289\n")
        ("seed,S", boost::program_options::value<uint32_t>(), "[OPTIONAL] Seed for random number generator.\n");
                                                                                                
      boost::program_options::variables_map vm;
      try {
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
      } catch (boost::program_options::error &e) {
        Log::error(e.what());
      }
      boost::program_options::notify(vm);

      if (vm.count("help")) {
        std::cout << desc << std::endl;
        exit(0);
      }

      if (vm.count("param")) {
        std::vector<uint32_t> P = vm["param"].as<std::vector<uint32_t>>();
        Params::q = P[0];
        Params::n = P[1];
        Params::N = P[2];
      }

#if defined(POLYNOMIAL_MULTIPLICATION_METHOD_NTT)
      Log::info("Polynomial Multiplication Method: [ NTT ]");
      if (vm.count("ntt")) {
        std::vector<uint32_t> X = vm["ntt"].as<std::vector<uint32_t>>();
        NTTParams::P = X[0];
        NTTParams::N = Params::N;
        Log::debug("NTT param = {\n",
                  "P =", NTTParams::P, "\n",
                  "N =", NTTParams::N, "\n}");
      }
  #if defined(MODULUS_STRATEGY_MERSENNE)
        Log::info("Modulus Strategy: [ Mersenne ]");
        if (NTTParams::P & (NTTParams::P+1) != 0) {
          Log::error("P is not a Mersenne number");
        }
  #elif defined(MODULUS_STRATEGY_NAIVE)
        Log::info("Modulus Strategy: [ Naive ]");
  #endif
#elif defined(POLYNOMIAL_MULTIPLICATION_METHOD_NAIVE)
      Log::info("Polynomial Multiplication Method: [ Naive ]");
      Log::warn("Naive polynomial multiplication has been selected. This method is less efficient and may result in slower performance compared to NTT.");
#else
      Log::error("Polynomial Multiplication Method is not defined");
#endif

      if (vm.count("seed")) {
        seed = vm["seed"].as<uint32_t>();
      } else {
        seed = 0;
      }
      PRNG = std::mt19937(seed);


    };
};

#endif