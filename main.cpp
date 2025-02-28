#include <iostream>
#include <vector>
#include <boost/program_options.hpp>
#include <utility>
#include <fstream>

#include "structure/intpoly.hpp"
#include "structure/toruspoly.hpp"

#include "utility/parser.hpp"
#include "utility/stopwatch.hpp"
#include "utility/log.hpp"

int main(int argc, char* argv[]) {
  CommandLineParser parser(argc, argv);

  auto prng = parser.PRNG;
  std::uniform_int_distribution<uint32_t> dis_poly(0, Params::q-1);

  std::ofstream ofs("log.txt");
  StopWatch<ChronoTimer> sw(ofs, "Timer", true);

  for (int i = 0; i < 100; ++i) {
    std::vector<uint32_t> coeffs1(Params::N);
    std::vector<DiscreteTorus> coeffs2(Params::N);
    for (auto& coeff : coeffs1) {
        coeff = dis_poly(prng);
    }
    for (auto& coeff : coeffs2) {
        coeff = dis_poly(prng);
    }

    // IntPoly intpoly1({1, 1, 1, 1});
    // DiscreteTorusPoly toruspoly2({0, 1, 0, 0});
    IntPoly intpoly1(coeffs1);
    DiscreteTorusPoly toruspoly2(coeffs2);

    // Log::debug("intpoly1:", intpoly1);
    // Log::debug("toruspoly2:", toruspoly2);

    DiscreteTorusPoly toruspoly3 = std::move(intpoly1 * toruspoly2);
  }
  sw.stop("stop");

  return 0;
}