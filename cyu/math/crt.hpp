#pragma once

#include <iostream>
#include <vector>

#include "cyu/math/exgcd.hpp"

namespace cyu {
 
// v里每个std::pair<Type, Type>中first为被模数，second为模数
template<typename Type>
std::pair<Type, Type> Crt(const std::vector<std::pair<Type, Type>>& v) {
  Type a = 1, r = 0;
  const int n = v.size();
  for (int i = 0; i < n; i++) {
    Type x, y; 
    std::tie(x, y, std::ignore) = ExGcd(a, v[i].first);
    Type g = a * x + v[i].first * y;
    if ((v[i].second - r) % g != 0) return std::make_pair(-1, -1);
    const Type p = v[i].first / g;
    Type t = (x * ((v[i].second - r) / g)) % p;
    if (t < 0) t += p;
    r += t * a;
    a *= p;
  }
  return std::make_pair(a, r);
}
 
}  // namespace cyu