#include "closing.h"
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

pair<vector<int64>, vector<int>> dijkstra(const vector<vector<pair<int, int>>> &g, const int s) {
  const int n = (int) g.size();

  vector<int64> d(n, kInf);
  vector<int> p(n, -1);
  min_heap<pair<int64, int>> q;

  d[s] = 0;
  q.emplace(0, s);

  while (not q.empty()) {
    const auto [dist, x] = q.top();
    q.pop();
    if (d[x] < dist) continue;
    for (const auto &[y, w] : g[x]) {

      if (d[y] <= d[x] + w) continue;
      d[y] = d[x] + w;
      p[y] = x;
      q.emplace(d[y], y);
    }
  }

  return make_pair(d, p);
}

int max_score(const int n, const int s, const int t, const int64 kTime, const vector<int> U, const vector<int> V, const vector<int> W) {
  vector<vector<pair<int, int>>> g(n);
  for (int i = 0; i < U.size(); i++) {
    g[U[i]].emplace_back(V[i], W[i]);
    g[V[i]].emplace_back(U[i], W[i]);
  }

  vector<int64> ds = dijkstra(g, s).first;
  vector<int64> dt = dijkstra(g, t).first;

  vector<int64> d = ds;
  d.insert(d.end(), dt.begin(), dt.end());

  sort(d.begin(), d.end());

  int ans = 2 * n;
  int64 sum = accumulate(d.begin(), d.end(), 0LL);
  for (int i = 2 * n - 1; sum > kTime; i--) {
    ans--;
    sum -= d[i];
  }

  return ans;
}
