#ifndef PARAMS_HPP
#define PARAMS_HPP

#include <cstdint>

namespace Params {
  extern uint32_t P;
  extern uint32_t n;
  extern uint32_t N;
}

namespace MontgomeryParams {
  extern uint32_t R;
  extern uint32_t mu;
  extern uint32_t R2;
}

namespace NttParams {
  extern uint32_t P;
  extern uint32_t N;
  extern uint32_t psi;
  extern uint32_t omega;
}

#endif