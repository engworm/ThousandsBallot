#ifndef EXTENDED_EUCLIDEAN_HPP
#define EXTENDED_EUCLIDEAN_HPP

#include <cstdint>
#include <utility>

inline std::pair<int32_t, int32_t> extendedEuclidean(uint32_t a, uint32_t b) {
  if (b==0) {
    return std::pair<int32_t, int32_t> (1, 0);
  }
  std::pair<int32_t, int32_t> r = extendedEuclidean(b, a%b);
  int32_t s = r.first;
  int32_t t = r.second;
  return std::pair<int32_t, int32_t> (t, s - t*(a/b));
}

#endif