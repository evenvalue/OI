#include <bits/stdc++.h>
using namespace std;

#define int long long

using mat = array<array<int, 2>, 2>;

constexpr int kInf = 1e16;

mat unite(const mat &x, const mat &y) {
  mat ans;
  for (auto &row : ans) {
    for (int &i : row) {
      i = kInf;
    }
  }
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        ans[i][k] = min(ans[i][k], x[i][j] + y[j][k]);
      }
    }
  }
  return ans;
}

constexpr int kLog = 20;
vector<vector<int>> st;
vector<vector<mat>> up;
vector<vector<mat>> down;
vector<int> depth;

void init(int32_t n, int32_t c, vector<int32_t> a, vector<int32_t> b, vector<int32_t> U, vector<int32_t> V) {
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    g[U[i]].push_back(V[i]);
    g[V[i]].push_back(U[i]);
  }

  auto init_mat = [&](const int x) {
    mat ans;
    ans[0][0] = min(a[x], b[x] + c);
    ans[0][1] = b[x] + c;
    ans[1][0] = min(a[x], c);
    ans[1][1] = c;
    return ans;
  };

  st = vector(n, vector<int>(kLog));
  up = vector(n, vector<mat>(kLog));
  down = vector(n, vector<mat>(kLog));
  depth = vector<int>(n);

  function<void(int, int)> dfs = [&](const int x, const int p) {
    st[x][0] = p;
    up[x][0] = init_mat(x);
    down[x][0] = init_mat(p);

    for (const int y : g[x]) {
      if (y == p) continue;
      depth[y] = depth[x] + 1;
      dfs(y, x);
    }
  };

  dfs(0, 0);
  for (int j = 1; j < kLog; j++) {
    for (int x = 0; x < n; x++) {
      const int anc = st[x][j - 1];
      st[x][j] = st[anc][j - 1];
      up[x][j] = unite(up[x][j - 1], up[anc][j - 1]);
      down[x][j] = unite(down[anc][j - 1], down[x][j - 1]);
    }
  }
}

long long query(int32_t x, int32_t y) {
  deque<mat> ascend;
  deque<mat> descend;

  if (depth[x] > depth[y]) {
    for (int bit = kLog - 1; bit >= 0; bit--) {
      if ((depth[x] - depth[y]) & (1 << bit)) {
        ascend.push_back(up[x][bit]);
        x = st[x][bit];
      }
    }
  }

  if (depth[y] > depth[x]) {
    for (int bit = kLog - 1; bit >= 0; bit--) {
      if ((depth[y] - depth[x]) & (1 << bit)) {
        descend.push_front(down[y][bit]);
        y = st[y][bit];
      }
    }
  }

  if (x != y) {
    for (int bit = kLog - 1; bit >= 0; bit--) {
      if (st[x][bit] == st[y][bit]) continue;
      ascend.push_back(up[x][bit]);
      descend.push_front(down[y][bit]);
      x = st[x][bit];
      y = st[y][bit];
    }
    ascend.push_back(up[x][0]);
    descend.push_front(down[y][0]);
  }

  mat ans;
  ans[0][0] = ans[1][1] = 0;
  ans[0][1] = ans[1][0] = kInf;
  for (const auto &m : ascend) {
    ans = unite(ans, m);
  }
  for (const auto &m : descend) {
    ans = unite(ans, m);
  }

  return min(ans[0][0], ans[0][1]);
}
