#ifndef POLYNOMIAL_MULTIPLICATION_MEASURE
#define POLYNOMIAL_MULTIPLICATION_MEASURE

#include <iostream>
#include <random>
#include "structure/intpoly.hpp"
#include "structure/toruspoly.hpp"
#include "utility/stopwatch.hpp"

class PolynomialMultiplicationMeasure {
  private:
    std::ostream& os;
    StopWatch<ChronoTimer> sw;
    std::mt19937 mt;
    uint32_t total_testcase;

  public:
    PolynomialMultiplicationMeasure(std::ostream& os, std::mt19937 mt, uint32_t total_testcase) 
          : os(os), mt(mt), total_testcase(total_testcase) {};

    void measure();
};

void PolynomialMultiplicationMeasure::measure() {

  std::uniform_int_distribution<uint32_t> dis_poly(0, Params::q-1);

  std::vector<IntPoly> intpolys;
  intpolys.reserve(total_testcase); 
  for (int i = 0; i < total_testcase; ++i) {
      intpolys.emplace_back(Params::N); 
  }

  std::vector<DiscreteTorusPoly> toruspolys;
  toruspolys.reserve(total_testcase); 
  for (int i = 0; i < total_testcase; ++i) {
      toruspolys.emplace_back(Params::N); 
  }

  for (int i = 0; i < total_testcase; ++i) {
    for (size_t j = 0; j < Params::N; ++j) {
      intpolys[i][j] = dis_poly(mt);
      toruspolys[i][j] = dis_poly(mt);
    }
  }

  this->sw.start("start");

  for (int i = 0; i < total_testcase; ++i) {
    DiscreteTorusPoly toruspoly = std::move(intpolys[i] * toruspolys[i]);
    // Log::debug(toruspoly);
  }

  this->sw.stop("stop");
};

#endif