#include "walk.h"
#include <bits/stdc++.h>
using namespace std;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using max_heap = priority_queue<T, vector<T>, less<T>>;

using int64 = long long;
using ld = long double;

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e17 + 10;
constexpr int kMod = 1e9 + 7;

class LazySegTree {
  const int n;
  vector<int> t;

  void push(const int x, const int l, const int r) {
    if (t[x] == -1) return;
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    for (const int child : {x + 1, y}) {
      t[child] = t[x];
    }
    t[x] = -1;
  }

  void update(const int x, const int l, const int r, const int ql, const int qr, const int i) {
    if (ql <= l and r <= qr) {
      t[x] = i;
      return;
    }
    push(x, l, r);
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (ql <= mid) {
      update(x + 1, l, mid, ql, qr, i);
    }
    if (mid < qr) {
      update(y, mid + 1, r, ql, qr, i);
    }
  }

  int query(const int x, const int l, const int r, const int p) {
    if (l == r) {
      return t[x];
    }
    push(x, l, r);
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (p <= mid) {
      return query(x + 1, l, mid, p);
    } else {
      return query(y, mid + 1, r, p);
    }
  }

public:
  explicit LazySegTree(const int n) : n(n), t(2 * n - 1, -1) {}

  void update(const int l, const int r, const int i) {
    update(0, 0, n - 1, l, r, i);
  }

  int query(const int p) {
    return query(0, 0, n - 1, p);
  }
};


pair<vector<int64>, vector<int>> dijkstra(const vector<vector<pair<int, int>>> &g, const int s) {
  const int n = (int) g.size();

  vector<int64> d(n, kInf64);
  vector<int> p(n, -1);
  min_heap<pair<int64, int>> q;

  d[s] = 0;
  q.push({0, s});

  while (not q.empty()) {
    const auto [dist, x] = q.top();
    q.pop();
    if (d[x] < dist) continue;
    for (const auto &[y, w] : g[x]) {
      if (d[y] <= d[x] + w) continue;
      d[y] = d[x] + w;
      p[y] = x;
      q.push({d[y], y});
    }
  }

  return make_pair(d, p);
}

struct building {
  int x;
  int h;
};

struct skywalk {
  int l;
  int r;
  int h;

  set<pair<int, int>> nodes;

  skywalk() = default;
  skywalk(const int l, const int r, const int h) : l(l), r(r), h(h) {}

  bool operator<(const skywalk &other) const {
    if (h != other.h) return h < other.h;
    if (l != other.l) return l < other.l;
    return r < other.r;
  }

  void add_node(const int node, const int x) {
    nodes.insert({x, node});
  }

  pair<int, int> get_prev(const int x) const {
    return *prev(nodes.upper_bound({x, kInf}));
  }

  pair<int, int> get_next(const int x) const {
    return *nodes.upper_bound({x, -1});
  }
};

int64 subtask4(const vector<building> &buildings, vector<skywalk> &skywalks, int S, int G) {
  const int n = buildings.size();

  sort(skywalks.begin(), skywalks.end());

  vector<vector<pair<int, int>>> g(n);
  LazySegTree st(n);

  auto add_node = [&]() -> int {
    g.emplace_back();
    return g.size() - 1;
  };

  auto add_edge = [&](const int x, const int y, const int w) -> void {
    g[x].emplace_back(y, w);
    g[y].emplace_back(x, w);
  };

  auto add_vert = [&](const int i, const int h, const int u) {
    const int x = buildings[i].x;
    const int s = st.query(i);
    if (s == -1) {
      add_edge(u, i, h);
      return;
    }

    const int v = add_node();

    auto before = skywalks[s].get_prev(x);
    add_edge(before.second, v, x - before.first);

    auto after = skywalks[s].get_next(x);
    add_edge(after.second, v, after.first - x);

    add_edge(u, v, h - skywalks[s].h);

    skywalks[s].add_node(v, x);
  };

  for (int i = 0; i < skywalks.size(); i++) {
    skywalk &s = skywalks[i];

    const int l = s.l;
    const int r = s.r;
    const int h = s.h;

    const int x = add_node();
    const int y = add_node();

    add_edge(x, y, buildings[r].x - buildings[l].x);
    add_vert(l, h, x);
    add_vert(r, h, y);

    s.add_node(x, buildings[l].x);
    s.add_node(y, buildings[r].x);

    st.update(l, r, i);
  }

  const int64 ans = dijkstra(g, S).first[G];
  return (ans == kInf64 ? -1 : ans);
}

int64 min_distance(vector<int> X, vector<int> H, vector<int> L, vector<int> R, vector<int> Y, int S, int G) {
  const int n = X.size();
  int m = L.size();

  vector<building> buildings(n);
  for (int i = 0; i < n; i++) {
    buildings[i].h = H[i];
    buildings[i].x = X[i];
  }

  vector<skywalk> skywalks(m);
  for (int j = 0; j < m; j++) {
    skywalks[j].l = L[j];
    skywalks[j].r = R[j];
    skywalks[j].h = Y[j];
  }

  auto add_skywalks = [&](const int x) {
    vector<pair<int, int>> A = {{kInf, -1}};
    for (int i = 0; i <= x; i++) {
      while (A.back().first < H[i]) {
        A.pop_back();
      }
      A.emplace_back(H[i], i);
    }

    vector<pair<int, int>> B = {{kInf, -1}};
    for (int i = n - 1; i >= x; i--) {
      while (B.back().first < H[i]) {
        B.pop_back();
      }
      B.emplace_back(H[i], i);
    }

    vector<skywalk> temp;
    swap(temp, skywalks);
    for (const skywalk &s : temp) {
      if (not(s.l < x and x < s.r)) {
        skywalks.push_back(s);
        continue;
      }
      const int a = lower_bound(A.rbegin(), A.rend(), make_pair(s.h, -1))->second;
      const int b = lower_bound(B.rbegin(), B.rend(), make_pair(s.h, -1))->second;
      skywalks.emplace_back(s.l, a, s.h);
      skywalks.emplace_back(a, b, s.h);
      skywalks.emplace_back(b, s.r, s.h);
    }
  };

  add_skywalks(S);
  add_skywalks(G);

  return subtask4(buildings, skywalks, S, G);
}
