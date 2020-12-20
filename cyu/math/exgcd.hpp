#pragma once

#include <cstdint>
#include <tuple>

namespace cyu {
 
// find a, b, g that a * x + b * y = g
// g = gcd(x, y)
// return std::tuple<a, b, g>
template<typename Type = int64_t>
std::tuple<Type, Type, Type> ExGcd(const Type& x, const Type& y) {
  if (y == 0) return std::make_tuple(1, 0, x);
  Type a, b, g;
  std::tie(a, b, g) = ExGcd(y, x % y);
  return std::make_tuple(b, a - x / y * b, g);
}
 
}  // namespace cyu