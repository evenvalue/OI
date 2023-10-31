#include <bits/stdc++.h>
using namespace std;

#ifdef evenvalue
  #include "debug.h"
  #define debug(...) print(#__VA_ARGS__, __VA_ARGS__)
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
}// namespace read

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;
constexpr int kMaxN = 2e5 + 10;

pair<int, int> diameter(const vector<vector<int>> &g) {
  auto bfs = [&](int start) -> pair<int, int> {
    const int n = g.size();
    vector<int> d(n, 0);
    vector<bool> visit(n, false);
    queue<int> q;
    q.push(start);
    while (not q.empty()) {
      int x = q.front();
      q.pop();
      visit[x] = true;
      for (int nbr : g[x]) {
        if (visit[nbr]) continue;
        q.push(nbr);
        d[nbr] = d[x] + 1;
      }
    }
    int far = distance(d.begin(), max_element(d.begin(), d.end()));
    return {d[far], far};
  };
  int x = bfs(0).second;
  return make_pair(x, bfs(x).second);
}

inline void solution() {
  const int n = read::Int();
  const int m = read::Int();

  if (m != n - 1) {
    cout << "NO\n";
    return;
  }

  if (n == 1) {
    cout << "YES\n";
    cout << 1 << '\n'
         << 1 << '\n';
    return;
  } else if (n == 2) {
    cout << "YES\n";
    cout << 2 << '\n';
    cout << 1 << ' ' << 1 << '\n';
    return;
  }

  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    const int x = read::Int() - 1;
    const int y = read::Int() - 1;
    g[x].push_back(y);
    g[y].push_back(x);
  }

  const auto ends = diameter(g);
  const int s = ends.first;
  const int t = ends.second;

  vector<int> ds(n);
  vector<int> dt(n);

  function<void(int, int, vector<int> &)> calc_dist = [&](const int x, const int p, vector<int> &d) {
    for (const int y : g[x]) {
      if (y == p) continue;
      d[y] = d[x] + 1;
      calc_dist(y, x, d);
    }
  };

  calc_dist(s, -1, ds);
  calc_dist(t, -1, dt);

  bool bad_star = false;
  for (int x = 0; x < n; x++) {
    bad_star |= (ds[x] + dt[x] == ds[t] + 6);
  }

  if (bad_star) {
    cout << "NO\n";
    return;
  }

  for (int x = 0; x < n; x++) {
    sort(g[x].begin(), g[x].end(), [&](const int y, const int z) {
      return ds[y] + dt[y] != ds[t];
    });
  }

  vector<int> order;

  function<void(int, int)> dfs = [&](const int x, const int p) {
    bool deviation = (ds[x] + dt[x] != ds[t]);
    bool pushed = false;
    for (const int y : g[x]) {
      if (y == p) continue;
      order.push_back(x);
      dfs(y, x);
      if (g[y].size() == 1 and (not deviation or (deviation == 1 and pushed))) {
        order.pop_back();
      }
      pushed = true;
    }
  };

  dfs(g[s][0], s);

  order.push_back(g[t][0]);
  for (int i = (int) order.size() - 1; i >= 0; i--) {
    order.push_back(order[i]);
  }

  cout << "YES\n";
  cout << order.size() << '\n';
  for (const int x : order) {
    cout << x + 1 << ' ';
  }
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
