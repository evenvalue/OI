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

vector<int> reject(const int n) {
  vector<int> v(n);
  return v;
}

vector<int> find_split(int n, int A, int B, int C, vector<int> P, vector<int> Q) {
  vector<int> v = {A, B, C};
  sort(v.begin(), v.end());
  A = v[0], B = v[1], C = v[2];

  const int m = P.size();

  vector<vector<int>> g(n);
  for (int i = 0; i < m; i++) {
    const int x = P[i], y = Q[i];
    g[x].push_back(y);
    g[y].push_back(x);
  }

  vector<int> ss(n, 1);
  int U = -1, V = -1;
  function<int(int, int)> dfs = [&](const int x, const int p) {
    for (const int y : g[x]) {
      if (y == p) continue;
      ss[x] += dfs(y, x);
    }
    if (ss[x] >= A and n - ss[x] >= A) {
      U = x;
      V = p;
    }
    return ss[x];
  };

  dfs(0, -1);

  if (U == -1) return reject(n);

  if (ss[U] > n - ss[U]) {
    swap(U, V);
  }

  vector<int> assign(n, 3);

  function<void(int, int, int, int)> dfs2 = [&](const int x, const int p, const int i, const int sz) {
    assign[x] = i;
    if (sz == 1) return;
    for (const int y : g[x]) {
      if (y == p) continue;
      dfs2(y, x, i, sz - 1);
    }
  };

  dfs2(U, V, 1, A);
  dfs2(V, U, 2, B);

  return assign;
}