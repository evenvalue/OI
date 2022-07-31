#include "werewolf.h"
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

class MergeSortTree {
  const int n;
  vector<vector<int>> t;

  void build(const int x, const int l, const int r, const vector<int> &a) {
    if (l == r) {
      t[x] = {a[l]};
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    build(x + 1, l, mid, a);
    build(y, mid + 1, r, a);
    merge(t[x + 1].begin(), t[x + 1].end(),
          t[y].begin(), t[y].end(),
          back_inserter(t[x]));
  }

  int query(const int x, const int l, const int r, const int ql, const int qr, const int lo, const int hi) {
    if (ql <= l and r <= qr) {
      return (int) distance(lower_bound(t[x].begin(), t[x].end(), lo),
                            upper_bound(t[x].begin(), t[x].end(), hi));
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (qr <= mid) {
      return query(x + 1, l, mid, ql, qr, lo, hi);
    } else if (mid < ql) {
      return query(y, mid + 1, r, ql, qr, lo, hi);
    } else {
      return query(x + 1, l, mid, ql, qr, lo, hi) +
             query(y, mid + 1, r, ql, qr, lo, hi);
    }
  }

public:
  explicit MergeSortTree(const vector<int> &a) : n((int) a.size()), t(2 * n - 1) {
    build(0, 0, n - 1, a);
  }

  int query(const int l, const int r, const int lo, const int hi) {
    return query(0, 0, n - 1, l, r, lo, hi);
  }
};

class dsu {
  vector<int> e;
  vector<pair<int, int>> val;
  vector<pair<int, int>> range;

  int find(const int x) {
    return (e[x] < 0 ? x : e[x] = find(e[x]));
  }

public:
  explicit dsu(const int n) : e(n, -1), val(n, {0, 0}), range(n) {
    for (int i = 0; i < n; i++) {
      range[i] = {i, i};
    }
  }

  bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x > y) swap(x, y);
    if (x == y) return false;
    val[y] = {x, -e[x]};
    range[x] = {min(range[x].first, range[y].first),
                max(range[x].second, range[y].second)};
    e[x] += e[y];
    e[y] = x;
    return true;
  }

  vector<int> order() {
    vector<int> new_order(val.size());
    for (int i = 0; i < new_order.size(); i++) {
      new_order[i] = new_order[val[i].first] + val[i].second;
    }
    return new_order;
  }

  pair<int, int> get_range(const int x) {
    return range[find(x)];
  }
};

struct query {
  int s, e, l, r, i;
  int human_l, human_r;
  int werewolf_l, werewolf_r;
};

void humans(const vector<vector<int>> &g, vector<query> &queries, const vector<int> &order_human) {
  const int n = (int) g.size();
  sort(queries.begin(), queries.end(), [&](const query &q1, const query &q2) {
    return q1.l > q2.l;
  });
  dsu d(n);
  for (int l = n - 1, j = 0; l >= 0; l--) {
    for (const int y : g[l]) {
      if (y < l) continue;
      d.unite(order_human[l], order_human[y]);
    }
    while (j < queries.size() and queries[j].l == l) {
      const auto &[x, y] = d.get_range(order_human[queries[j].s]);
      queries[j].human_l = x;
      queries[j].human_r = y;
      j++;
    }
  }
}

void werewolfs(const vector<vector<int>> &g, vector<query> &queries, const vector<int> &order_werewolf) {
  const int n = (int) g.size();
  sort(queries.begin(), queries.end(), [&](const query &q1, const query &q2) {
    return q1.r < q2.r;
  });
  dsu d(n);
  for (int r = 0, j = 0; r < n; r++) {
    for (const int y : g[r]) {
      if (y > r) continue;
      d.unite(order_werewolf[r], order_werewolf[y]);
    }
    while (j < queries.size() and queries[j].r == r) {
      const auto &[x, y] = d.get_range(order_werewolf[queries[j].e]);
      queries[j].werewolf_l = x;
      queries[j].werewolf_r = y;
      j++;
    }
  }
}

void print_vec(const vector<int> &v, const string &name = "") {
  cerr << name << (name.empty() ? "" : ": ");
  for (const int x : v) {
    cerr << x << ' ';
  }
  cerr << '\n';
}

vector<int> check_validity(int n, vector<int> X, vector<int> Y, vector<int> S, vector<int> E, vector<int> L, vector<int> R) {
  const int m = (int) X.size();//number of edges
  const int q = (int) S.size();//number of queries
  vector<vector<int>> g(n);
  for (int i = 0; i < m; i++) {
    const int x = X[i], y = Y[i];
    g[x].push_back(y);
    g[y].push_back(x);
  }
  vector<query> queries(q);
  for (int i = 0; i < q; i++) {
    queries[i] = {S[i], E[i], L[i], R[i], i};
  }
  dsu human(n), werewolf(n);
  for (int l = n - 1; l >= 0; l--) {
    for (const int y : g[l]) {
      if (y < l) continue;
      human.unite(l, y);
    }
  }
  for (int r = 0; r < n; r++) {
    for (const int y : g[r]) {
      if (y > r) continue;
      werewolf.unite(r, y);
    }
  }
  vector<int> v(n);
  vector<int> order_human = human.order();
  vector<int> order_werewolf = werewolf.order();
  for (int i = 0; i < n; i++) {
    v[order_human[i]] = order_werewolf[i];
  }
  humans(g, queries, order_human);
  werewolfs(g, queries, order_werewolf);
  sort(queries.begin(), queries.end(), [&](const query &q1, const query &q2) {
    return q1.i < q2.i;
  });
  vector<int> ans(q);
  MergeSortTree mst(v);
  for (int i = 0; i < q; i++) {
    const auto &[s, e, l, r, idx,
                 hl, hr, wl, wr] = queries[i];
    ans[i] = (mst.query(hl, hr, wl, wr) > 0);
  }
  return ans;
}
