#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

namespace read {
int Int() {
  int x;
  cin >> x;
  return x;
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

constexpr int kMaxA = 5e6 + 5;
constexpr int kInf = 1e9 + 10;

inline void solution() {
  const int n = read::Int();
  vector<vector<int>> diff(n, vector<int>(n));

  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      diff[i][j] = read::Int();
    }
  }

  vector<int> ans(n);
  for (int i = 1; i < n; i++) {
    vector<int> options = {
        ans[i - 1] + diff[i - 1][i],
        ans[i - 1] - diff[i - 1][i]};

    int a[2][2] = {
        {options[0], ans[i - 1]},
        {ans[i - 1], options[1]}};

    for (int j = i - 1; j >= 0; j--) {
      for (int k = 0; k < 2; k++) {
        a[k][0] = max(a[k][0], ans[j]);
        a[k][1] = min(a[k][1], ans[j]);
        if (a[k][0] - a[k][1] != diff[j][i]) {
          options.erase(options.begin() + k);
          break;
        }
      }
      if (options.size() == 1) break;
    }
    ans[i] = options[0];
  }

  const int mn = *min_element(ans.begin(), ans.end());
  for (int i = 0; i < n; i++) {
    cout << ans[i] - mn << (i == n - 1 ? "" : " ");
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  solution();
}