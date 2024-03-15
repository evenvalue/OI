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

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;

struct edge {
  int x;
  int y;
  int64 w;
};

inline void solution() {
  const int n = read::Int();
  vector<int64> hay = read::Vec<int64>(n);

  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    const int x = read::Int() - 1;
    const int y = read::Int() - 1;
    g[x].push_back(y);
    g[y].push_back(x);
  }

  vector<int> subtree_size(n, 1);
  function<void(int, int)> dfs1 = [&](const int x, const int p) {
    for (const int y : g[x]) {
      if (y == p) continue;
      dfs1(y, x);
      hay[x] += hay[y];
      subtree_size[x] += subtree_size[y];
    }
  };

  dfs1(0, -1);

  const int64 total_hay = hay[0];
  const int64 each = total_hay / n;
  for (int x = 0; x < n; x++) {
    hay[x] -= each * subtree_size[x];
  }

  for (int x = 0; x < n; x++) {
    sort(g[x].begin(), g[x].end(), [&](const int i, const int j) {
      return hay[i] > hay[j];
    });
  }

  vector<edge> ans;
  function<void(int, int)> dfs2 = [&](const int x, const int p) {
    for (const int y : g[x]) {
      if (y == p) continue;
      if (hay[y] > 0) {
        dfs2(y, x);
        ans.push_back({y, x, hay[y]});
      } else if (hay[y] < 0) {
        ans.push_back({x, y, -hay[y]});
        dfs2(y, x);
      } else {
        dfs2(y, x);
      }
    }
  };

  dfs2(0, 0);

  cout << ans.size() << '\n';
  for (const auto [x, y, w] : ans) {
    cout << x + 1 << ' ' << y + 1 << ' ' << w << '\n';
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  solution();
}