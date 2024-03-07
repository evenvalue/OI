#include <bits/stdc++.h>
using namespace std;

#ifdef evenvalue
  #include "debug.h"
#else
  #define debug(...)
#endif

using int64 = long long;
using ld = long double;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using max_heap = priority_queue<T, vector<T>, less<T>>;

namespace Read {
int Int() {
  int x;
  cin >> x;
  return x;
}
int64 Int64() {
  int64 x;
  cin >> x;
  return x;
}
char Char() {
  char c;
  cin >> c;
  return c;
}
string String() {
  string s;
  cin >> s;
  return s;
}
double Double() {
  return stod(String());
}
ld LongDouble() {
  return stold(String());
}
template<typename T1, typename T2>
pair<T1, T2> Pair() {
  pair<T1, T2> p;
  cin >> p.first >> p.second;
  return p;
}
template<typename T>
vector<T> Vec(const int n) {
  vector<T> v(n);
  for (T &x : v) {
    cin >> x;
  }
  return v;
}
template<typename T>
vector<vector<T>> VecVec(const int n, const int m) {
  vector<vector<T>> v(n);
  for (vector<T> &vec : v) {
    vec = Vec<T>(m);
  }
  return v;
}
}//namespace Read

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e16 + 10;
constexpr int kMod = 1e9 + 7;
constexpr int kMaxN = 2e5 + 10;

auto dijkstra(const vector<vector<pair<int, int64>>> &g, const vector<int> &s) {
  const int n = (int) g.size();

  vector<int64> d(n, kInf64);
  vector<vector<int>> p(n);
  min_heap<pair<int64, int>> q;

  for (const int x : s) {
    d[x] = 0;
    q.emplace(0, x);
  }

  while (not q.empty()) {
    const auto [dist, x] = q.top();
    q.pop();
    if (d[x] < dist) continue;
    for (const auto &[y, w] : g[x]) {
      if (d[y] > d[x] + w) {
        d[y] = d[x] + w;
        p[y].clear();
        q.emplace(d[y], y);
      }
      if (d[y] == d[x] + w) {
        p[y].push_back(x);
      }
    }
  }

  return make_pair(d, p);
}

inline void solution() {
  const auto n = Read::Int();
  const auto m = Read::Int();
  const auto s = Read::Int() - 1;
  const auto t = Read::Int() - 1;
  const auto u = Read::Int() - 1;
  const auto v = Read::Int() - 1;

  vector<vector<pair<int, int64>>> g(n);
  for (int i = 0; i < m; i++) {
    const auto x = Read::Int() - 1;
    const auto y = Read::Int() - 1;
    const auto w = Read::Int();
    g[x].emplace_back(y, w);
    g[y].emplace_back(x, w);
  }

  const auto foo = dijkstra(g, {s});
  const auto &ds = foo.first;
  const auto &p = foo.second;
  const auto dt = dijkstra(g, {t}).first;
  const auto du = dijkstra(g, {u}).first;
  const auto dv = dijkstra(g, {v}).first;

  vector<vector<int>> dag(n);
  for (int y = 0; y < n; y++) {
    if (ds[y] + dt[y] != ds[t]) continue;
    for (const int x : p[y]) {
      if (ds[x] + dt[x] != ds[t]) continue;
      dag[x].push_back(y);
    }
  }

  auto topsort = [&]() {
    vector<int> order;
    vector<bool> visit(n);

    function<void(int)> dfs = [&](const int x) {
      visit[x] = true;
      for (const int y : dag[x]) {
        if (not visit[y]) dfs(y);
      }
      order.push_back(x);
    };

    for (int x = 0; x < n; x++) {
      if (ds[x] + dt[x] != ds[t]) continue;
      if (not visit[x]) dfs(x);
    }

    return order;
  };

  const auto order = topsort();

  vector<int64> best_u = du;
  vector<int64> best_v = dv;

  int64 ans = du[v];
  for (const int x : order) {
    for (const int y : dag[x]) {
      best_u[x] = min(best_u[x], best_u[y]);
      best_v[x] = min(best_v[x], best_v[y]);
    }
    ans = min(ans, best_u[x] + dv[x]);
    ans = min(ans, best_v[x] + du[x]);
  }

  cout << ans << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);

  cout << fixed << setprecision(10);

  int testcases = 1;
  //cin >> testcases;
  while (testcases--) {
    solution();
  }
}