#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
  #define debug(...)
#endif

using int64 = long long;
using ld = long double;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using max_heap = priority_queue<T, vector<T>, less<T>>;

template<typename T>
T read() {
  T x;
  cin >> x;
  return x;
}

template<typename T1, typename T2>
pair<T1, T2> read_pair() {
  pair<T1, T2> p;
  cin >> p.first;
  cin >> p.second;
  return p;
}

template<typename T>
vector<T> read_vec(const int n, const int index = 0) {
  vector<T> v(n + index);
  for (int i = index; i < n + index; i++) {
    v[i] = read<T>();
  }
  return v;
}

template<typename T>
vector<vector<T>> read_vec_vec(const int n, const int m, const int index_n = 0, const int index_m = 0) {
  vector<vector<T>> grid(n + index_n);
  for (int i = index_n; i < n + index_n; i++) {
    grid[i] = read_vec<T>(m, index_m);
  }
  return grid;
}

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;
constexpr int kMaxN = 2e5 + 10;

struct edge {
  int x;
  int y;
  int len;

  bool operator<(const edge &other) const {
    if (len != other.len) {
      return len > other.len;
    } else {
      return (x == other.x ? y < other.y : x < other.x);
    }
  }
};

inline void solution() {
  const int n = read<int>();
  const int m = read<int>();

  vector<edge> edges(m);
  vector<vector<int>> g(n);

  vector<vector<int>> add(n);
  vector<vector<int>> rem(n);

  for (int i = 0; i < m; i++) {
    auto &[x, y, _] = edges[i];
    x = read<int>() - 1;
    y = read<int>() - 1;
    g[x].push_back(y);
    add[x].push_back(i);
    rem[y].push_back(i);
  }

  auto topsort = [](vector<vector<int>> &g) {
    const int n = g.size();
    vector<int> visit(n);
    vector<int> order;
    function<void(int)> dfs = [&](const int x) {
      visit[x] = true;
      for (const int y : g[x]) {
        if (visit[y]) continue;
        dfs(y);
      }
      order.push_back(x);
    };
    for (int x = 0; x < n; x++) {
      if (not visit[x]) dfs(x);
    }
    reverse(order.begin(), order.end());
    return order;
  };

  auto order = topsort(g);

  vector<int> pref(n);
  vector<int> suff(n);

  vector<int> p_max(n);
  for (int i = 0; i < n; i++) {
    const int x = order[i];
    for (const int y : g[x]) {
      pref[y] = max(pref[y], pref[x] + 1);
    }
    if (i != 0) p_max[i] = max(p_max[i - 1], pref[order[i - 1]]);
  }

  vector<int> s_max(n);
  for (int i = n - 1; i >= 0; i--) {
    const int x = order[i];
    for (const int y : g[x]) {
      suff[x] = max(suff[x], suff[y] + 1);
    }
    if (i != n - 1) s_max[i] = max(s_max[i + 1], suff[order[i + 1]]);
  }

  multiset<edge> s;
  pair<int, int> ans = {kInf, -1};
  for (int i = 0; i < n; i++) {
    const int x = order[i];
    for (const int e : rem[x]) {
      s.erase(edges[e]);
    }
    auto dist = (s.empty() ? 0 : s.begin()->len);
    const int foo = max({dist, p_max[i], s_max[i]});
    ans = min(ans, make_pair(foo, x));
    for (const int e : add[x]) {
      edges[e].len = pref[edges[e].x] + 1 + suff[edges[e].y];
      s.insert(edges[e]);
    }
  }

  cout << ans.second + 1 << ' ' << ans.first << '\n';
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