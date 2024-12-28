#ifndef ENCRYPT_TLWE_HPP
#define ENCRYPT_TLWE_HPP

#include "params/params.hpp"
#include "structure/discrete_torus_galoisfield.hpp"
#include "structure/tlwe.hpp"

class EncryptDiscreteTLWE : public DiscreteTLWE {
  public:
    static DiscreteTLWE encrypt(const uint32_t message, const std::vector<uint32_t> &secret) {
      uint32_t n = secret.size();
      DiscreteTLWE tlwe(n);

      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<uint32_t> dis(0, Params::P-1);

      DiscreteTorus b(message);
      for (int i = 0; i < n; ++i) {
          uint32_t random_value = dis(gen);
          tlwe.v.push_back(DiscreteTorus(random_value));
          b += secret[i] * DiscreteTorus(random_value); 
      }
      tlwe.v.push_back(b);
      return std::move(tlwe);
    }
};

#endif