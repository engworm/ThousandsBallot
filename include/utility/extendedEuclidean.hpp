#ifndef EXTENDED_EUCLIDEAN_HPP
#define EXTENDED_EUCLIDEAN_HPP

#include <cstdint>
#include <utility>

template <typename T>
inline std::pair<typename std::make_signed<T>::type, typename std::make_signed<T>::type> extendedEuclidean(T a, T b) {
  static_assert(std::is_integral<T>::value, "Template parameter must be an integral type");

  if (b==0) {
    return std::make_pair(1, 0);
  }

  auto r = extendedEuclidean(b, a%b);
  return std::make_pair(r.second, r.first - r.second*(a/b));
}

template <typename T>
inline bool isCoprime(T a, T b) {
  auto [s, t] = extendedEuclidean(a, b);
  return (s * a) + (t * b) == 1;
}

#endif