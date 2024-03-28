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
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;
constexpr int kMaxN = 2e5 + 10;
constexpr int kSqrtN = 150;

inline void solution() {
  const int n = Read::Int();
  const int m = Read::Int();
  const int q = Read::Int();

  vector<basic_string<int>> in(n);
  for (int i = 0; i < m; i++) {
    const int x = Read::Int() - 1;
    const int y = Read::Int() - 1;
    in[y].push_back(x);
  }

  vector<bool> busy(n);
  vector<vector<pair<int, int>>> best_paths(n);
  for (int x = 0; x < n; x++) {
    vector<pair<int, int>> best;
    if (not busy[x]) best.emplace_back(-1, x);
    for (const int y : in[x]) {
      best.insert(best.end(), best_paths[y].begin(), best_paths[y].end());
    }
    sort(best.rbegin(), best.rend());
    for (const auto [dist, y] : best) {
      if (busy[y]) continue;
      busy[y] = true;
      best_paths[x].emplace_back(dist + 1, y);
      if (best_paths[x].size() == kSqrtN) break;
    }
    for (const auto [dist, y] : best_paths[x]) {
      busy[y] = false;
    }
  }

  vector<int> dp(n);
  for (int qry = 0; qry < q; qry++) {
    const int x = Read::Int() - 1;
    const vector<int> nerds = Read::Vec<int>(Read::Int());

    for (const int nerd : nerds) {
      busy[nerd - 1] = true;
    }

    if (nerds.size() >= kSqrtN) {
      fill(dp.begin(), dp.begin() + x + 1, 0);
      for (const int nerd : nerds) {
        dp[nerd - 1] = -kInf;
      }
      for (int y = 0; y <= x; y++) {
        for (const int z : in[y]) {
          dp[y] = max(dp[y], dp[z] + 1);
        }
      }
      cout << max(dp[x], -1) << '\n';
    } else {
      bool found = false;
      for (const auto [dist, y] : best_paths[x]) {
        if (busy[y]) continue;
        found = true;
        cout << dist << '\n';
        break;
      }
      if (not found) cout << -1 << '\n';
    }

    for (const int nerd : nerds) {
      busy[nerd - 1] = false;
    }
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
