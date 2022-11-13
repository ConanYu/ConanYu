#include <string>
#include <vector>

namespace ext {
 
class Manacher {
 public:
  Manacher(const std::string& t) {
    std::string s = "$#";
    for (auto c : t) {
      s += c, s += "#";
    }
    const int n = (int) s.length();
    int ans = 0, ind = 0, right = 0;
    dp_ = std::vector<int>(n, 1);
    for (int i = 1; i < n; i++) {
      if (i < right) {
        dp_[i] = std::min(right - i, dp_[2 * ind - i]);
      }
      while (i + dp_[i] < n && s[i + dp_[i]] == s[i - dp_[i]]) {
        ++dp_[i];
      }
      ans = std::max(ans, dp_[i] - 1);
      if (i + dp_[i] > right) {
        ind = i, right = i + dp_[i];
      }
    }
    max_length_ = ans;
  }
  int GetMaxLength() {
    return max_length_;
  }
  bool CheckIsPalindrome(int from, int to) {
    from++;
    to++;
    return dp_[from + to] - 1 >= to - from + 1;
  }
 private:
  std::vector<int> dp_;
  int max_length_;
};
 
}  // namespace ext
