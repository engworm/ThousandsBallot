#include <iostream>
#include <boost/program_options.hpp>
#include <random>
#include "utility/parser.hpp"

int main(int argc, char* argv[]) {
  CommandLineParser parser(argc, argv);

  auto prng = parser.PRNG;
  std::uniform_int_distribution<uint32_t> dis_poly(0, Params::q-1);
  
  // テストケースを作っておいて，ファイルに保存する
  return 0;
}