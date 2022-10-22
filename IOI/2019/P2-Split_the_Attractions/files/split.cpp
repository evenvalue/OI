#include "split.h"
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

vector<int> sort_ABC(int &A, int &B, int &C) {
  vector<pair<int, int>> v = {{A, 1}, {B, 2}, {C, 3}};
  sort(v.begin(), v.end());
  A = v[0].first, B = v[1].first, C = v[2].first;

  vector<int> mapping = {v[0].second, v[1].second, v[2].second};
  return mapping;
}

vector<int> find_split(int n, int A, int B, int C, vector<int> P, vector<int> Q) {
  vector<int> mapping = sort_ABC(A, B, C);

  const int m = P.size();

  vector<vector<int>> g(n);
  for (int i = 0; i < m; i++) {
    const int x = P[i], y = Q[i];
    g[x].push_back(y);
    g[y].push_back(x);
  }

  int start = 0;
  for (int x = 0; x < n; x++) {
    if (g[x].size() == 1) start = x;
  }

  vector<int> ans(n, mapping[2]);
  int assign = mapping[0];

  function<pair<int, int>(int, int, int)> dfs = [&](const int x, const int p, const int sz) {
    if (sz == 0) return make_pair(x, p);
    ans[x] = assign;
    for (const int y : g[x]) {
      if (y == p) continue;
      return dfs(y, x, sz - 1);
    }
    assert(false);
  };

  const auto &[start2, p] = dfs(start, -1, A);
  assign = mapping[1];
  dfs(start2, p, B);
  return ans;
}