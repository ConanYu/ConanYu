#pragma once

#include <tuple>
#include <vector>

#include "cyu/math/exgcd.hpp"

namespace cyu {
 
class Combine {
 public:
  Combine(int mod, int max_size) : mod_(mod), max_size_(max_size + 5) {
    fac_.resize(max_size_);
    inv_.resize(max_size_);
    fac_[0] = 1;
    for (int i = 1; i < max_size_; i++) {
      fac_[i] = 1ll * fac_[i - 1] * i % mod;
    }
    inv_[max_size_ - 1] = std::get<0>(ExGcd(fac_[max_size_ - 1], mod_));
    if (inv_[max_size_ - 1] < 0) {
      inv_[max_size_ - 1] += mod_;
    }
    for (int i = max_size_ - 2; i >= 0; i--) {
      inv_[i] = 1ll * inv_[i + 1] * (i + 1) % mod_;
    }
  }
  int GetFac(int index) {
    return fac_[index];
  }
  int GetInv(int index) {
    return inv_[index];
  }
  int operator()(int n, int m) {
    return 1ll * fac_[n] * inv_[m] % mod_ * inv_[n - m] % mod_;
  }
 private:
  const int mod_;
  const int max_size_;
  std::vector<int> fac_, inv_;
};
 
}  // namespace cyu
