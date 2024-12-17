#include <cstdint>

#ifndef PARAMS_HPP
#define PARAMS_HPP

namespace Consts {
  constexpr uint32_t P = 3*(1<<12)+1;
  constexpr uint32_t R = 1<<18;
  constexpr uint32_t mu = 274431;
}

namespace Params {
  constexpr int n = 4;
}

#endif