#include "shoes.h"
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

template<class node, class F = std::function<node(const node &, const node &)>>
class SegTree {
  int n = 0;
  std::vector<node> t;
  F unite;

  void build(const int x, const int l, const int r, const std::vector<node> &a) {
    if (l == r) {
      t[x] = a[l];
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    build(x + 1, l, mid, a);
    build(y, mid + 1, r, a);
    t[x] = unite(t[x + 1], t[y]);
  }

  void update(const int x, const int l, const int r, const int p, const node &v) {
    if (l == p and p == r) {
      t[x] = v;
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (p <= mid) {
      update(x + 1, l, mid, p, v);
    } else {
      update(y, mid + 1, r, p, v);
    }
    t[x] = unite(t[x + 1], t[y]);
  }

  [[nodiscard]] node query(const int x, const int l, const int r, const int ql, const int qr) const {
    if (ql <= l and r <= qr) {
      return t[x];
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (qr <= mid) {
      return query(x + 1, l, mid, ql, qr);
    } else if (mid < ql) {
      return query(y, mid + 1, r, ql, qr);
    } else {
      return unite(query(x + 1, l, mid, ql, qr), query(y, mid + 1, r, ql, qr));
    }
  }

  void debug_node(const int x, const vector<int> &path) const {
    for (int i = 0; i < path.size(); i++) {
      cerr << path[i] << (i == path.size() - 1 ? ": " : " -> ");
    }
    cerr << t[x] << '\n';
  }

  void debug(const int x, const int l, const int r, vector<int> path) const {
    path.push_back(x);
    if (l == r) {
      debug_node(x, path);
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    debug(x + 1, l, mid, path);
    debug(y, mid + 1, r, path);
    debug_node(x, path);
  }

public:
  SegTree() = default;
  explicit SegTree(const int n, const node e, F f) : n(n), t(2 * n - 1, e), unite(std::move(f)) {}
  explicit SegTree(const std::vector<node> &a, F f) : n(a.size()), t(2 * (a.size()) - 1), unite(std::move(f)) {
    build(0, 0, n - 1, a);
  }

  void set(const int p, const node &v) {
    assert(0 <= p and p < n);
    update(0, 0, n - 1, p, v);
  }

  [[nodiscard]] node get(const int l, const int r) const {
    assert(0 <= l and l <= r and r < n);
    return query(0, 0, n - 1, l, r);
  }

  void debug() const {
    debug(0, 0, n - 1, {});
    cerr << "----------\n\n";
  }
};

int64 count_swaps(std::vector<int> S) {
  const int shoes = S.size();
  const int n = shoes / 2;

  vector<vector<int>> occ(shoes + 1);

  auto get = [&](const int i) -> vector<int> & {
    return occ[i + n];
  };

  vector<int> final(shoes);
  vector<int> seen(n + 1);
  for (int i = 0, j = 0; i < shoes; i++) {
    get(S[i]).push_back(i);
    const int shoe = abs(S[i]);
    seen[shoe] += (S[i] < 0 ? -1 : 1);
    if (max(seen[shoe], S[i]) >= 0 and min(seen[shoe], S[i]) <= 0) continue;
    final[j] = -shoe;
    final[j + 1] = shoe;
    j += 2;
  }

  for (vector<int> &v : occ) {
    sort(v.rbegin(), v.rend());
  }

  SegTree<int> st(shoes, 0, [](const int a, const int b) {
    return a + b;
  });

  for (int i = 0; i < shoes; i++) {
    st.set(i, 1);
  }

  int64 swaps = 0;
  for (int i = 0; i < shoes; i++) {
    const int idx = get(final[i]).back();
    get(final[i]).pop_back();
    st.set(idx, 0);
    swaps += st.get(0, idx);
  }
  return swaps;
}