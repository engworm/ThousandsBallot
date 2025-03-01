#include <iostream>
#include <vector>
#include <boost/program_options.hpp>
#include <utility>
#include <fstream>

#include "utility/parser.hpp"
#include "measure/polynomial_multiplication_measure.hpp"

int main(int argc, char* argv[]) {
  CommandLineParser parser(argc, argv);

  PolynomialMultiplicationMeasure polynomial_multiplication_measure(std::cout, parser.PRNG, 1000);
  polynomial_multiplication_measure.measure();

  return 0;
}