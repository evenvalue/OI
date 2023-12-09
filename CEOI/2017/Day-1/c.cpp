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
}//namespace read

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;
constexpr int kMaxN = 2e5 + 10;

inline void solution() {
  const int n = Read::Int();
  const int t = Read::Int() - 1;
  const int m = Read::Int() - 1;

  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    const int x = Read::Int() - 1;
    const int y = Read::Int() - 1;
    g[x].push_back(y);
    g[y].push_back(x);
  }

  vector<int> parent(n);
  function<void(int, int)> find_parent = [&](const int x, const int p) {
    parent[x] = p;
    for (const int y : g[x]) {
      if (y == p) continue;
      find_parent(y, x);
    }
  };

  function<int(int, int)> dfs = [&](const int x, const int p) {
    int mx1 = 0, mx2 = 0;
    int children = 0;
    for (const int y : g[x]) {
      if (y == p) continue;
      children++;
      const int score = dfs(y, x);
      if (score >= mx1) {
        mx2 = mx1;
        mx1 = score;
      } else {
        mx2 = max(mx2, score);
      }
    }
    return mx2 + children;
  };


  find_parent(t, -1);

  vector<bool> visit(n);
  for (int x = m; x != -1; x = parent[x]) {
    visit[x] = true;
  }

  vector<vector<int>> tree(n);
  for (int root = m; root != t; root = parent[root]) {
    for (const int x : g[root]) {
      if (visit[x]) continue;
      tree[root].push_back(dfs(x, root));
    }
  }

  function<int(int)> add = [&](const int x) {
    if (x == t) return 0;
    const int extra = add(parent[x]) + tree[x].size();
    for (int &val : tree[x]) {
      val += extra;
    }
    return extra;
  };
  add(m);


  auto check = [&](int score) {
    for (int x = m, cuts = 1; x != t; x = parent[x], cuts++) {
      int chops = 0;
      for (const int y : tree[x]) {
        if (y >= score) chops++;
      }
      if (cuts < chops) return true;
      score -= chops;
      cuts -= chops;
    }
    return (score <= 0);
  };

  for (int i = 0; i <= n; i++) {
    debug(i, check(i));
  }

  int lo = 0, hi = kInf;
  while (lo < hi) {
    const int mid = (lo + hi + 1) / 2;
    if (check(mid)) {
      lo = mid;
    } else {
      hi = mid - 1;
    }
  }

  cout << lo << '\n';
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
