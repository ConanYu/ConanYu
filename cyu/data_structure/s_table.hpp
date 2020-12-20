#include <vector>
#include <algorithm>

namespace cyu {
 
namespace detail {
 
template <typename Type, typename Comp = std::less<Type>>
class InnerMerger {
 public:
  Type operator()(const Type& lhs, const Type& rhs) const {
    return cmp(lhs, rhs) ? lhs : rhs;
  }
 private:
  const Comp cmp;
};
 
}  // namespace detail
 
template<typename Type, typename Merger = detail::InnerMerger<Type>>
class STable {
 public:
  explicit STable(const vector<Type>& arr) : merger() {
    const int n = static_cast<int>(arr.size());
    table.assign(n, vector<Type>(Log2(n) + 1));
    for (int i = 0; i < n; i++) {
      table[i][0] = arr[i];
    }
    for (int j = 1; (1 << j) <= n; j++) {
      for (int i = 0; i + (1 << j) - 1 < n; i++) {
        const Type x = table[i][j - 1], y = table[i + (1 << (j - 1))][j - 1];
        table[i][j] = merger(x, y);
      }
    }
  }
  Type Query(int l, int r) const {
    const int k = Log2(r - l + 1);
    const Type x = table[l][k], y = table[r - (1 << k) + 1][k];
    return merger(x, y);
  }
  Type operator()(int l, int r) const {
    return Query(l, r);
  }
 private:
  int Log2(int n) const {
    return 31 - __builtin_clz(static_cast<unsigned int>(n));
  }
  const Merger merger;
  std::vector<std::vector<Type>> table;
};
 
}  // namespace cyu