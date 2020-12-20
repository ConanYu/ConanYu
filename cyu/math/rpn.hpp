#pragma once

#include <cstdint>
#include <functional>
#include <vector>

namespace cyu {
 
// 表达式求值（内部采用后缀表达式求解）
template <typename Type>
class RPN {
 public:
  // tuple<操作符, 优先级, 计算函数>
  explicit RPN(const std::vector<std::tuple<char, int, std::function<Type(const Type&, const Type&)>>>& v)
    : kLeftBucket(-1), kRightBucket(-2) {
    for (const auto& o : v) {
      dict_[std::get<0>(o)] = std::make_pair(std::get<1>(o), std::get<2>(o));
    }
  }
  Type operator()(const std::string &str) {
    const int n = str.size();
    std::queue<Node> que;
    std::stack<std::pair<int, char>> stk;
    for(int i = 0; i < n; i++) {
      if(isdigit(str[i])) {
        Type cur = 0;
        int j = i;
        while(isdigit(str[j])) {
          cur = cur * 10 + str[j] - '0';
          j++;
        }
        i = j - 1;
        que.push(Node('\0', cur));
      } else {
        const int cur = Trans(str[i]);
        if(cur == kLeftBucket) {
          stk.emplace(cur, str[i]);
        } else if(cur == kRightBucket) {
          while(stk.top().second != kLeftBucket) {
            que.push(Node(stk.top().second));
            stk.pop();
          }
          stk.pop();
        } else {
          while(!stk.empty() && stk.top().first >= cur) {
            que.push(Node(stk.top().second));
            stk.pop();
          }
          stk.emplace(cur, str[i]);
        }
      }
    }
    while(!stk.empty()) {
      que.push(Node(stk.top().second));
      stk.pop();
    }
    std::stack<Type> for_calc;
    while(!que.empty()) {
      const Node cur = que.front();
      que.pop();
      if(cur.what_) {
        const Type b = for_calc.top(); for_calc.pop();
        const Type a = for_calc.top(); for_calc.pop();
        for_calc.push(dict_.at(cur.what_).second(a, b));
      } else {
        for_calc.push(cur.val_);
      }
    }
    return for_calc.top();
  }
 private:
  struct Node {
    char what_;
    Type val_;
    Node(char w = '\0', Type v = 0) : what_(w), val_(v) {}
  };
  const int kLeftBucket;
  const int kRightBucket;
  int Trans(const char c) {
    return dict_.at(c).first;
  }
  std::map<char, std::pair<int, std::function<Type(const Type&, const Type&)>>> dict_;
};
 
RPN<int64_t> rpn_demo({
  std::make_tuple('|', 11, [](const int64_t& x, const int64_t& y) { return x | y; }),
  std::make_tuple('^', 12, [](const int64_t& x, const int64_t& y) { return x ^ y; }),
  std::make_tuple('&', 13, [](const int64_t& x, const int64_t& y) { return x & y; }),
  std::make_tuple('+', 14, [](const int64_t& x, const int64_t& y) { return x + y; }),
  std::make_tuple('-', 14, [](const int64_t& x, const int64_t& y) { return x - y; }),
  std::make_tuple('*', 15, [](const int64_t& x, const int64_t& y) { return x * y; }),
  std::make_tuple('/', 15, [](const int64_t& x, const int64_t& y) { return x / y; }),
  std::make_tuple('%', 15, [](const int64_t& x, const int64_t& y) { return x % y; }),
});
 
}  // namespace cyu