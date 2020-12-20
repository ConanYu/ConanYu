#pragma once

#include <string>
#include <vector>

#include "cyu/string/kmp.hpp"

namespace cyu {

std::string Replace(const std::string& str, const std::string& from, const std::string& to) {
  std::vector<int> ids = cyu::KMP(str, from);
  std::string ret;
  ids.push_back(static_cast<int>(str.size()));
  int cur = 0;
  const int size = ids.size();
  for (int i = 0; i < size; i++) {
    // from = cur, to = ids[i] - 1
    ret.append(str.substr(cur, ids[i] - cur));
    if (i + 1 < size) {
      ret.append(to);
    }
    cur = ids[i] + from.size();
  }
  return ret;
}

}  // namespace cyu