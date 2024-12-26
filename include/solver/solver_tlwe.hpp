#ifndef SOLVER_TLWE_HPP
#define SOLVER_TLWE_HPP

#include "params/params.hpp"
#include "structure/torus.hpp"
#include "structure/tlwe.hpp"

class SolverTLWE : public DiscreteTLWE {
  public:
    static DiscreteTorus solve(const DiscreteTLWE &tlwe, const std::vector<uint32_t> &secret) {
      return tlwe.decrypt(secret);
    }

};

#endif