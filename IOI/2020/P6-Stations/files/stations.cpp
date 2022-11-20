#include "stations.h"
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

template<typename T>
class CoordinateCompression {
  vector<T> a;

public:
  void add(const T x) {
    a.push_back(x);
  }

  void add(const vector<T> &v) {
    a.insert(a.end(), v.begin(), v.end());
  }

  vector<T> compress() {
    vector<T> v = a;
    sort(a.begin(), a.end());
    for (int &x : v) {
      x = distance(a.begin(), lower_bound(a.begin(), a.end(), x));
    }
    return v;
  }
};

vector<int> label(int n, int k, vector<int> u, vector<int> v) {
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    g[u[i]].push_back(v[i]);
    g[v[i]].push_back(u[i]);
  }

  vector<int> depth(n);
  vector<int> tin(n, -1), tout(n, -1);
  function<int(int, int)> dfs = [&](int x, int p)-> int {
    int time = tin[x] + 1;
    for (const int y : g[x]) {
      if (y == p) continue;
      tin[y] = time;
      depth[y] = 1 - depth[x];
      time = dfs(y, x) + 1;
    }
    return tout[x] = time;
  };

  depth[0] = 0;
  tin[0] = tout[0] = 0;
  dfs(0, -1);

  vector<int> labels(n);
  for (int x = 0; x < n; x++) {
    labels[x] = (depth[x] == 0 ? tin[x] : tout[x]);
  }

  CoordinateCompression<int> cc;
  cc.add(labels);
  return cc.compress();
}

int find_next_station(int s, int t, vector<int> c) {
  if (c[0] > s) {
    sort(c.begin(), c.end());
    for (int i = 0; i < c.size() - 1; i++) {
      if (s < t and t <= c[i]) return c[i];
    }
    return c.back();
  } else {
    sort(c.rbegin(), c.rend());
    for (int i = 0; i < c.size() - 1; i++) {
      if (c[i] <= t and t < s) return c[i];
    }
    return c.back();
  }
}