#include <bits/stdc++.h>
using namespace std;

#define int long long

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

namespace read {
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
}//namespace read

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;
constexpr int kMaxN = 2e5 + 10;

inline void solution() {
  const int n = read::Int();
  const int v = read::Int();

  vector<int> cost = read::Vec<int>(n);
  cost.push_back(0);

  vector<vector<int>> g(n + 1);
  for (int i = 0; i < n - 1; i++) {
    const int x = read::Int() - 1;
    const int y = read::Int() - 1;
    g[x].push_back(y);
    g[y].push_back(x);
  }

  vector<int> nbr(n);
  for (int x = 0; x < n; x++) {
    for (const int y : g[x]) {
      nbr[x] += cost[y];
    }
    g[x].push_back(n);
  }

  vector<vector<int>> up(n + 1, vector<int>(v + 1));
  vector<vector<int>> down(n + 1, vector<int>(v + 1));

  int ans = 0;

  auto calc_cross = [&](const int x) {
    for (const int y : g[x]) {
      for (int k = 1; k <= v; k++) {
        up[x][k] = max(up[y][k], up[y][k - 1] + nbr[x] - cost[y]);
        ans = max(ans, up[x][k] + down[x][v - k]);
      }
      for (int k = 1; k <= v; k++) {
        down[x][k] = max(down[x][k], down[y][k]);
      }
    }
  };

  function<void(int, int)> dfs = [&](const int x, const int p) {
    const int children_cost = nbr[x] - (p == -1 ? 0 : cost[p]);

    for (const int y : g[x]) {
      if (y == p) continue;
      dfs(y, x);
    }

    calc_cross(x);
    reverse(g[x].begin(), g[x].end());
    fill(down[x].begin(), down[x].end(), 0);
    calc_cross(x);

    for (const int y : g[x]) {
      for (int k = 1; k <= v; k++) {
        up[x][k] = max({up[x][k], up[y][k], up[y][k - 1] + nbr[x] - cost[y]});
      }
      for (int k = 1; k <= v; k++) {
        down[x][k] = max({down[x][k], down[y][k], down[y][k - 1] + children_cost});
      }
    }
  };

  dfs(0, -1);

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