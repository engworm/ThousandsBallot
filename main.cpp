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


  std::vector<IntPoly> intpolys;
  intpolys.reserve(1000); 
  for (int i = 0; i < 1000; ++i) {
      intpolys.emplace_back(Params::N); 
  }

  std::vector<DiscreteTorusPoly> toruspolys;
  toruspolys.reserve(1000); 
  for (int i = 0; i < 1000; ++i) {
      toruspolys.emplace_back(Params::N); 
  }

  for (int i = 0; i < 1000; ++i) {
    for (size_t j = 0; j < Params::N; ++j) {
      intpolys[i][j] = dis_poly(prng);
      toruspolys[i][j] = dis_poly(prng);
    }
  }

  StopWatch<ChronoTimer> sw;
  sw.start("start");

  for (int i = 0; i < 1000; ++i) {
    DiscreteTorusPoly toruspoly = std::move(intpolys[i] * toruspolys[i]);
  }
  // DiscreteTorusPoly toruspoly = std::move(intpolys[0] * toruspolys[0]);
  sw.stop("stop");
  // Log::debug(toruspoly);

  return 0;
}