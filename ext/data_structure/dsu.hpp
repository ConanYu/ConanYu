#pragma once

#include <numeric>
#include <vector>

namespace ext {
 
// 并查集
class Dsu {
 public:
  std::vector<int> anc, size;
  Dsu(int n) : anc(n), size(n, 0) {
    std::iota(anc.begin(), anc.end(), 0);
  }
  int operator[] (int x) {
    return x == anc[x] ? x : anc[x] = operator[](anc[x]);
  }
  bool operator() (int u, int v) {
    int a = operator[](u), b = operator[](v);
    if (a == b) return false;
    if (size[a] < size[b]) anc[a] = b;
    else anc[b] = a, size[a] += (size[a] == size[b]);
    return true;
  }
};
 
}  // namespace ext