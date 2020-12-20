#pragma once

#include <string>
#include <vector>

namespace cyu {

std::vector<int> GetFail(const std::string& s) {
  const int n = s.size();
  std::vector<int> fail(n + 1);
  for (int i = 0, j = fail[0] = -1; i < n; i++) {
    while (j != -1 && s[j] != s[i]) {
      j = fail[j];
    }
    fail[i + 1] = j + 1;
  }
  return fail;
}

int Match(const std::string& s, const std::string& t, std::vector<int> fail = std::vector<int>()) {
  if (fail.empty()) {
    fail = GetFail(t);
  }
  std::vector<int> ret;
  const int n = s.size(), m = t.size();
  for (int i = 0, j = 0; i < n; i++, j++) {
    while (j != -1 && s[i] != t[j]) {
      j = fail[j];
    }
    if (j + 1 == m) {
      return i + 1 - m;
    }
  }
  return -1;
}

std::vector<int> KMP(const std::string& s, const std::string& t, std::vector<int> fail = std::vector<int>()) {
  if (fail.empty()) {
    fail = GetFail(t);
  }
  std::vector<int> ret;
  const int n = s.size(), m = t.size();
  for (int i = 0, j = 0; i < n; i++, j++) {
    while (j != -1 && s[i] != t[j]) {
      j = fail[j];
    }
    if (j + 1 == m) {
      ret.push_back(i + 1 - m);
      j = -1;
    }
  }
  return ret;
}

}  // namespace cyu