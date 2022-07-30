#include "highway.h"
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using max_heap = priority_queue<T, vector<T>, less<T>>;

using int64 = long long;
using ld = long double;

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;

int find_hidden_node(const vector<vector<pair<int, int>>> &g, const int root, const int64 all_a, const vector<int> &template_w) {
  const int n = (int) g.size();

  vector<int> match(n, -1);
  vector<int> edge(n, -1);
  function<int(int, int, int)> postorder = [&](int x, int p, int v) {
    for (const auto &[y, i] : g[x]) {
      if (y == p) continue;
      v = postorder(y, x, v) + 1;
      edge[y] = i;
    }
    match[v] = x;
    return v;
  };

  int lo = 0, hi = postorder(root, -1, 0);
  while (lo < hi) {
    vector<int> w = template_w;
    const int mid = (lo + hi) / 2;
    for (int i = lo; i <= mid; i++) {
      w[edge[match[i]]] = 1;
    }
    if (ask(w) > all_a) {
      hi = mid;
    } else {
      lo = mid + 1;
    }
  }

  return match[lo];
}

void find_pair(const int n, const vector<int> U, const vector<int> V, const int a, const int b) {
  const int m = (int) U.size();

  vector<int> w(m);
  const int64 all_a = ask(w);

  int lo = 0, hi = m - 1;
  while (lo < hi) {
    const int mid = (lo + hi) / 2;
    for (int i = 0; i < m; i++) {
      w[i] = (i <= mid);
    }
    if (ask(w) > all_a) {
      hi = mid;
    } else {
      lo = mid + 1;
    }
  }

  vector<vector<pair<int, int>>> g(n);
  for (int i = 0; i < m; i++) {
    g[U[i]].emplace_back(V[i], i);
    g[V[i]].emplace_back(U[i], i);
  }

  auto bfs = [&g](const int s) {
    vector<int> dist(g.size(), kInf);
    dist[s] = 0;
    queue<int> q;
    q.push(s);

    while (not q.empty()) {
      const int x = q.front();
      for (const auto &[y, _] : g[x]) {
        if (dist[y] < kInf) continue;
        q.push(y);
        dist[y] = dist[x] + 1;
      }
      q.pop();
    }

    return dist;
  };

  auto bfs_tree = [&](const int s, vector<int> near) -> vector<vector<pair<int, int>>> {
    queue<int> q;
    q.push(s);
    vector<vector<pair<int, int>>> tree(n);

    near[s] = 0;
    while (not q.empty()) {
      const int x = q.front();
      for (const auto &[y, i] : g[x]) {
        if (near[y] == 0) continue;
        q.push(y);
        tree[x].emplace_back(y, i);
        near[y] = 0;
      }
      q.pop();
    }

    return tree;
  };

  const int x = U[lo], y = V[lo];
  const vector<int> distx = bfs(x), disty = bfs(y);

  vector<int> nearx(n), neary(n);
  for (int i = 0; i < n; i++) {
    nearx[i] = (distx[i] < disty[i]);
    neary[i] = (disty[i] < distx[i]);
  }

  const auto tx = bfs_tree(x, nearx);
  const auto ty = bfs_tree(y, neary);

  vector<int> template_w(m, 1);
  template_w[lo] = 0;
  for (int u = 0; u < n; u++) {
    for (const auto &[_, i] : tx[u]) {
      template_w[i] = 0;
    }
    for (const auto &[_, i] : ty[u]) {
      template_w[i] = 0;
    }
  }

  const int s = find_hidden_node(tx, x, all_a, template_w);
  const int t = find_hidden_node(ty, y, all_a, template_w);
  answer(s, t);
}