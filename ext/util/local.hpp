#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <tuple>
#include <unordered_set>
#include <unordered_map>

template <typename F, typename S>
std::ostream& operator << (std::ostream& s, const std::pair<F, S>& p);

template <typename T, typename A>
std::ostream& operator << (std::ostream& s, const std::vector<T, A>& a);

template <typename T, typename A>
std::ostream& operator << (std::ostream& s, const std::set<T, A>& a);

template <typename T, typename H, typename P, typename A>
std::ostream& operator << (std::ostream& s, const std::unordered_set<T, H, P, A>& a);

template <typename K, typename T, typename C, typename A>
std::ostream& operator << (std::ostream& s, const std::map<K, T, C, A>& a);

template <typename K, typename T, typename H, typename P, typename A>
std::ostream& operator << (std::ostream& s, const std::unordered_map<K, T, H, P, A>& a);

template <typename ...Args>
std::ostream& operator << (std::ostream& s, const std::tuple<Args...>& p);

template <typename F, typename S>
std::ostream& operator << (std::ostream& s, const std::pair<F, S>& p) {
  s << '<' << p.first << ", " << p.second << '>';
  return s;
}

template <typename T, typename A>
std::ostream& operator << (std::ostream& s, const std::vector<T, A>& a) {
  s << '[';
  for (size_t i = 0; i < a.size(); i++) {
    s << a[i];
    if (i + 1 < a.size()) {
      s << ", ";
    }
  }
  s << ']';
  return s;
}

template <typename T, typename A>
std::ostream& operator << (std::ostream& s, const std::set<T, A>& a) {
  s << '{';
  bool i = false;
  for (const auto &x : a) {
    if (i) {
      s << ", ";
    }
    s << x;
    i = true;
  }
  s << '}';
  return s;
}


template <typename T, typename H, typename P, typename A>
std::ostream& operator << (std::ostream& s, const std::unordered_set<T, H, P, A>& a) {
  s << '{';
  bool i = false;
  for (const auto &x : a) {
    if (i) {
      s << ", ";
    }
    s << x;
    i = true;
  }
  s << '}';
  return s;
}

template <typename K, typename T, typename C, typename A>
std::ostream& operator << (std::ostream& s, const std::map<K, T, C, A>& a) {
  s << '{';
  bool i = false;
  for (const auto &[x, y] : a) {
    if (i) {
      s << ", ";
    }
    s << '{' << x << ": " << y << '}';
    i = true;
  }
  s << '}';
  return s;
}

template <typename K, typename T, typename H, typename P, typename A>
std::ostream& operator << (std::ostream& s, const std::unordered_map<K, T, H, P, A>& a) {
  s << '{';
  bool i = false;
  for (const auto &[x, y] : a) {
    if (i) {
      s << ", ";
    }
    s << '{' << x << ": " << y << '}';
    i = true;
  }
  s << '}';
  return s;
}

namespace __debug_detail {

template <int pos, typename ...Args>
struct __TuplePrinter {
  static std::ostream& __print_tuple(std::ostream& s, const std::tuple<Args...>& p, int size) {
    __TuplePrinter<pos - 1, Args...>::__print_tuple(s, p, size);
    s << std::get<pos>(p);
    if (pos + 1 != size) {
      s << ", ";
    }
    return s;
  }
};

template <typename ...Args>
struct __TuplePrinter<0, Args...> {
  static std::ostream& __print_tuple(std::ostream& s, const std::tuple<Args...>& p, int size) {
    s << std::get<0>(p);
    if (0 + 1 != size) {
      s << ", ";
    }
    return s;
  }
};

}

template <typename ...Args>
std::ostream& operator << (std::ostream& s, const std::tuple<Args...>& p) {
  constexpr int size = std::tuple_size<std::tuple<Args...>>{};
  s << '<';
  __debug_detail::__TuplePrinter<size - 1, Args...>::__print_tuple(s, p, size);
  s << '>';
  return s;
}

namespace __debug_detail {

void _print() {}

template <typename T, typename... U>
void _print(const T &head, const U &...tail) {
  std::cout << head << (sizeof...(tail) ? ' ' : '\n');
  _print(tail...);
}

}


#define DEBUG(...) __debug_detail::_print(__VA_ARGS__)