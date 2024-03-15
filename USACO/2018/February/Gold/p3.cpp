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
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;

inline void solution() {
  const int n = read::Int();
  vector<int> a = read::Vec<int>(n);

  vector<vector<int>> ans(n, vector<int>(n + 1, kInf));
  vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n, kInf)));

  dp[0][0][0] = (a[0] != 0);
  ans[0][0] = dp[0][0][0];
  for (int i = 1; i < n; i++) {
    dp[i][0][i] = dp[i - 1][0][i - 1] + (a[i] != i);
    ans[i][0] = dp[i][0][i];
    for (int breakouts = 1; breakouts <= i; breakouts++) {
      for (int reading = 0; reading < n; reading++) {
        if (reading > 0) {
          dp[i][breakouts][reading] = dp[i - 1][breakouts][reading - 1] + (a[i] != reading);
        } else {
          dp[i][breakouts][reading] = ans[i - 1][breakouts - 1] + (a[i] != reading);
        }
        ans[i][breakouts] = min(ans[i][breakouts], dp[i][breakouts][reading]);
      }
    }
  }

  for (int breakouts = 0; breakouts < n; breakouts++) {
    cout << ans[n - 1][breakouts] << '\n';
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  freopen("taming.in", "r", stdin);
  freopen("taming.out", "w", stdout);

  cout << fixed << setprecision(10);

  int testcases = 1;
  //cin >> testcases;
  while (testcases--) {
    solution();
  }
}