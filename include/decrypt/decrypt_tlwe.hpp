#ifndef DECRYPT_TLWE_HPP
#define DECRYPT_TLWE_HPP

#include "params/params.hpp"
#include "structure/tlwe.hpp"

class DecryptDiscreteTLWE : public DiscreteTLWE {
  public:
    static DiscreteTorus decrypt(const DiscreteTLWE &tlwe, const std::vector<uint32_t> &secret) {
      DiscreteTorus b = tlwe.v[tlwe.n];
      for (int i = 0; i < tlwe.n; ++i) {
        b -= secret[i] * tlwe.v[i];
      }
      return b;
    }

};

#endif