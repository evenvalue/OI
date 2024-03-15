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
string String() {
  string s;
  cin >> s;
  return s;
}
template<typename T>
vector<T> Vec(const int n) {
  vector<T> v(n);
  for (T &x : v) {
    cin >> x;
  }
  return v;
}
}//namespace read

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e18 + 10;
constexpr int kMod = 1e9 + 7;

inline void solution() {
  const int n = read::Int();
  const int k = read::Int();
  const int m = 2 * n + 1;

  vector<int> cows = read::Vec<int>(n);

  cows.insert(cows.end(), cows.begin(), cows.end());
  cows.insert(cows.begin(), 0);

  vector<int64> pref(m);
  for (int i = 1; i < m; i++) {
    pref[i] = pref[i - 1] + cows[i];
  }

  auto sum = [&](const int l, const int r) {
    return pref[r] - pref[l];
  };

  vector<vector<vector<int64>>> dp(m, vector<vector<int64>>(m, vector<int64>(k + 1, kInf64)));

  for (int i = 1; i < m; i++) {
    fill(dp[i][i].begin() + 1, dp[i][i].end(), 0);
    fill(dp[i][i - 1].begin(), dp[i][i - 1].end(), 0);
  }

  for (int len = 2; len < m; len++) {
    for (int keys = 1; keys <= k; keys++) {
      for (int l = 1; l + len <= m; l++) {
        const int r = l + len - 1;
        dp[l][r][keys] = dp[l][r][keys - 1];
        int64 travel = 0;
        for (int i = r; i >= l; i--) {
          travel += sum(i, r);
          dp[l][r][keys] = min(dp[l][r][keys], dp[l][i - 1][keys - 1] + travel);
        }
      }
    }
  }

  int64 ans = kInf64;
  for (int l = 1; l <= n; l++) {
    const int r = l + n - 1;
    ans = min(ans, dp[l][r][k]);
  }

  cout << ans << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  freopen("cbarn2.in", "r", stdin);
  freopen("cbarn2.out", "w", stdout);

  cout << fixed << setprecision(10);

  int testcases = 1;
  //cin >> testcases;
  while (testcases--) {
    solution();
  }
}