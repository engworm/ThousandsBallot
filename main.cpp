#include <iostream>
#include <vector>
#include <boost/program_options.hpp>
#include <utility>
#include <fstream>

#include "measure/polynomial_multiplication_measure.hpp"

#include "utility/parser.hpp"
#include "utility/chronotimer.hpp"

int main(int argc, char* argv[]) {
  CommandLineParser parser(argc, argv);

  PolynomialMultiplicationMeasure<ChronoTimer> polynomial_multiplication_measure(std::cout, parser.PRNG, 1000);
  polynomial_multiplication_measure.measure();

  return 0;
}