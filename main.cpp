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


  // std::vector<IntPoly> intpolys(1000, IntPoly(Params::N));
  // std::vector<DiscreteTorusPoly> toruspolys(1000, DiscreteTorusPoly(Params::N));
  IntPoly intpoly1(Params::N);
  DiscreteTorusPoly toruspoly2(Params::N);
  for (size_t i = 0; i < Params::N; ++i) {
    intpoly1[i] = dis_poly(prng);
    toruspoly2[i] = dis_poly(prng);
  }

  StopWatch<ChronoTimer> sw;
  sw.start("start");

  // for (int i = 0; i < 1000; ++i) {
  DiscreteTorusPoly toruspoly = std::move(intpoly1 * toruspoly2);
  // }
  sw.stop("stop");

  return 0;
}