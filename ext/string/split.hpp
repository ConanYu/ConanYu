#pragma once

#include <string>
#include <vector>

#include "ext/string/kmp.hpp"

namespace ext {
 
std::vector<std::string> Split(const std::string& str, const std::string& split_str = " ", bool ignore_empty = false) {
  std::vector<int> ids = KMP(str, split_str);
  ids.push_back(static_cast<int>(str.size()));
  std::vector<std::string> ret;
  int cur = 0;
  const int size = ids.size();
  for (int i = 0; i < size; i++) {
    // from = cur, to = ids[i] - 1
    if ((ignore_empty && ids[i] > cur) || !ignore_empty) {
      ret.push_back(str.substr(cur, ids[i] - cur));
    }
    cur = ids[i] + split_str.size();
  }
  return ret;
}
 
}  // namespace ext