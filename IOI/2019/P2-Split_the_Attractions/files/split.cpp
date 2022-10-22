#include "split.h"
#include <bits/stdc++.h>
using namespace std;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using max_heap = priority_queue<T, vector<T>, less<T>>;

using int64 = long long;
using ld = long double;

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;

bool checker(vector<vector<int>> &g, const vector<int> &ans) {
  const int n = g.size();
  if (ans == vector<int>(n)) return true;

  vector<bool> visit(n);

  function<void(int, int)> dfs = [&](const int x, const int i) {
    visit[x] = true;
    for (const int y : g[x]) {
      if (visit[y] or ans[y] != i) continue;
      dfs(y, i);
    }
  };

  int cnt = 0;
  for (int i = 1; i <= 3; i++) {
    const int s = distance(ans.begin(), find(ans.begin(), ans.end(), i));
    dfs(s, i);
    bool flag = true;
    for (int x = 0; x < n; x++) {
      if (ans[x] != i) continue;
      flag &= (visit[x]);
    }
    cnt += flag;
  }
  return cnt >= 2;
}

vector<int> sort_ABC(int &A, int &B, int &C) {
  vector<pair<int, int>> v = {{A, 1}, {B, 2}, {C, 3}};
  sort(v.begin(), v.end());
  A = v[0].first, B = v[1].first, C = v[2].first;

  vector<int> mapping = {v[0].second, v[1].second, v[2].second};
  return mapping;
}

vector<int> find_split(int n, int A, int B, int C, vector<int> P, vector<int> Q) {
  vector<int> mapping = sort_ABC(A, B, C);

  const int m = P.size();

  vector<vector<int>> g(n);
  for (int i = 0; i < m; i++) {
    const int x = P[i], y = Q[i];
    g[x].push_back(y);
    g[y].push_back(x);
  }

  vector<vector<int>> t(n);
  vector<int> depth(n);
  vector<int> back(n);
  vector<int> ss(n, 1);
  vector<bool> visit(n);

  function<int(int, int)> dfs = [&](const int x, const int p) {
    visit[x] = true;
    for (const int y : g[x]) {
      if (y == p) continue;
      if (visit[y]) {
        back[x] = min(back[x], depth[y]);
        continue;
      }
      t[x].push_back(y);
      depth[y] = back[y] = depth[x] + 1;
      ss[x] += dfs(y, x);
      back[x] = min(back[x], back[y]);
    }
    return ss[x];
  };

  dfs(0, -1);

  auto valid = [&](const int p1, const int p2) -> bool {
    return min(p1, p2) >= A;
  };

  vector<int> ans(n);
  function<void(int, int, int &, vector<bool> &)> mark = [&](const int x, const int i, int &occ, vector<bool> &to_mark) {
    if (occ == 0) return;
    ans[x] = i;
    occ--;
    to_mark[x] = false;
    for (const int y : g[x]) {
      if (not to_mark[y]) continue;
      mark(y, i, occ, to_mark);
    }
  };

  function<void(int, vector<int> &)> get_set = [&](const int x, vector<int> &s) {
    s.push_back(x);
    for (const int y : t[x]) {
      get_set(y, s);
    }
  };

  auto find_ans = [&](const int x) {
    vector<bool> p1(n), p2(n, true);
    int sz = ss[x];
    p1[x] = true;
    p2[x] = false;
    for (const int y : t[x]) {
      vector<int> s;
      get_set(y, s);
      bool in_p2 = back[y] < depth[x] and sz - ss[y] >= A;
      if (in_p2) {
        sz -= ss[y];
      } else {
        for (const int u : s) {
          p1[u] = true;
          p2[u] = false;
        }
      }
    }

    fill(ans.begin(), ans.end(), mapping[2]);

    assert(valid(std::count(p1.begin(), p1.end(), true), std::count(p2.begin(), p2.end(), true)));

    if (p1 <= p2) {
      mark(x, mapping[0], A, p1);
      mark(0, mapping[1], B, p2);
    } else {
      mark(0, mapping[0], A, p1);
      mark(x, mapping[1], B, p2);
    }
  };

  function<bool(int)> dfs2 = [&](const int x) {
    if (ss[x] < A) return false;
    for (const int y : t[x]) {
      if (dfs2(y)) return true;
    }
    int p1 = ss[x], p2 = n - ss[x];
    for (const int y : t[x]) {
      if (back[y] < depth[x] and p1 - ss[y] >= A) {
        p1 -= ss[y];
        p2 += ss[y];
      }
    }
    if (valid(p1, p2)) {
      find_ans(x);
      return true;
    }
    return false;
  };

  dfs2(0);

  assert(checker(g, ans));

  return ans;
}