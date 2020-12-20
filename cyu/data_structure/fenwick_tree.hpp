#pragma once

#include <vector>

namespace cyu {
 
// 树状数组
// index from 1
template<typename Type = int>
class FenwickTree {
 public:
  FenwickTree(const int size) {
    std::vector<Type> vec(size, Type());
    Init(vec);
  }
  FenwickTree(const int size, const Type& init_value) {
    std::vector<Type> vec(size, init_value);
    Init(vec);
  }
  FenwickTree(const std::vector<Type>& vec) {
    Init(vec);
  }
  void Add(int position, const Type& value) {
    for (int i = position; i <= n_; i += i & (-i)) {
      fenwick_tree_[i] += value;
    }
  }
  Type Query(int index) const {
    Type ret = Type();
    for (int i = index; i > 0; i -= i & (-i)) {
      ret += fenwick_tree_[i];
    }
    return ret;
  }
  Type Query(int left, int right) const {
    return Query(right) - Query(left - 1);
  }
 private:
  void Init(const std::vector<Type>& vec) {
    n_ = vec.size();
    fenwick_tree_.resize(vec.size() + 1);
    for (int i = 1; i <= n_; i++) {
      Add(i, vec[i - 1]);
    }
  }
  int n_;
  std::vector<Type> fenwick_tree_;
};
 
}  // namespace cyu