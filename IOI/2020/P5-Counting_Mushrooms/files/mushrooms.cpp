#include "mushrooms.h"
#include <bits/stdc++.h>
using namespace std;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using max_heap = priority_queue<T, vector<T>, less<T>>;

using int64 = long long;
using ld = long double;

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;
constexpr int kConst = 169;

int count_mushrooms(int n) {
  if (n == 2) {
    return 1 + (1 - use_machine({0, 1}));
  }

  auto next_two = [&](const vector<int> &s, const int x, const int y) {
    assert(s.size() >= 2);
    return use_machine({x, s[0], y, s[1]});
  };

  bool same;

  auto get_next = [&](const vector<int> &s, const int l) -> pair<int, int> {
    vector<int> query;
    for (int i = l, j = 0; i < n and j < s.size(); i++, j++) {
      query.push_back(i);
      query.push_back(s[j]);
    }
    const int x = use_machine(query);
    same = (x % 2 == 0);
    int ans = (not same) + (x / 2);
    return make_pair(ans, query.size() / 2);
  };

  vector<int> zero = {0}, ones;
  for (int x : {1, 2}) {
    if (use_machine({0, x}) == 0) {
      zero.push_back(x);
    } else {
      ones.push_back(x);
    }
  }

  for (int i = 3; i < min(n, kConst); i += 2) {
    if (i == n - 1) {
      if (use_machine({0, i}) == 0) {
        zero.push_back(i);
      } else {
        ones.push_back(i);
      }
      break;
    }
    if (zero.size() > ones.size()) {
      const int x = next_two(zero, i, i + 1);
      ((x & 1) == 0 ? zero : ones).push_back(i);
      ((x & 2) == 0 ? zero : ones).push_back(i + 1);
    } else {
      const int x = next_two(ones, i, i + 1);
      ((x & 1) == 0 ? ones : zero).push_back(i);
      ((x & 2) == 0 ? ones : zero).push_back(i + 1);
    }
  }

  int ans = zero.size();
  for (int i = kConst; i < n;) {
    if (zero.size() > ones.size()) {
      const auto &[inc, used] = get_next(zero, i);
      (same ? zero : ones).push_back(i);
      ans += used - inc;
      i += used;
    } else {
      const auto &[inc, used] = get_next(ones, i);
      (same ? ones : zero).push_back(i);
      ans += inc;
      i += used;
    }
  }

  return ans;
}