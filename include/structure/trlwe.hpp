#ifndef TRLWE_HPP
#define TRLWE_HPP

#include <vector>
#include "structure/toruspoly.hpp"

class DiscreteTRLWE {
  private:
    uint32_t q = Params::q;
    std::vector<std::vector<DiscreteTorusPoly>> data;
};

#endif