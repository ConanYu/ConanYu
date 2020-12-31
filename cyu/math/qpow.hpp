#pragma once

namespace cyu {
 
template<typename T = int>
int qpow(int a, T b, int mod) {
  int ans = 1;
  for (; b > 0; b >>= 1, a = 1ll * a * a % mod) {
    if (b & 1) {
      ans = 1ll * ans * a % mod;
    }
  }
  return ans;
}
 
}  // namespace cyu
