#include "meetings.h"
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
constexpr int kMaxHeight = 20;

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

  node query(const int x, const int l, const int r, const int ql, const int qr) const {
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
  explicit SegTree(const int n, const node e, F f) : n(n), t(2 * n - 1, e), unite(std::move(f)) {
    vector<node> a(n, e);
    build(0, 0, n - 1, a);
  }
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

struct node {
  int peak{};
  vector<int> left;
  vector<int> right;
  vector<int> costl;
  vector<int> costr;

  node() = default;
  explicit node(const int h) : left(h + 1), right(h + 1),
                               costl(h + 1, kInf), costr(h + 1, kInf) {}
};

vector<int64> subtask34(const vector<int> &H, const vector<int> &L, const vector<int> &R) {
  const int n = H.size(), q = L.size();

  vector<node> leaves(n, node(kMaxHeight));
  for (int i = 0; i < n; i++) {
    node &x = leaves[i];
    x.peak = H[i];
    for (int h = 0; h <= kMaxHeight; h++) {
      x.left[h] = max(h, H[i]);
      x.right[h] = max(h, H[i]);
    }
    x.costl[H[i]] = H[i];
    x.costr[H[i]] = H[i];
  }

  SegTree<node> st(leaves, [](const node &l, const node &r) {
    node ans(kMaxHeight);
    ans.peak = max(l.peak, r.peak);
    for (int i = 0; i <= kMaxHeight; i++) {
      ans.left[i] = l.left[i] + r.left[max(l.peak, i)];
      ans.right[i] = l.right[max(r.peak, i)] + r.right[i];
    }

    auto update = [&](const int max_left, const int max_right, const int cost) {
      if (max_left == ans.peak) {
        ans.costl[max_right] = min(ans.costl[max_right], cost);
      }
      if (max_right == ans.peak) {
        ans.costr[max_left] = min(ans.costr[max_left], cost);
      }
    };

    for (int i = 0; i <= kMaxHeight; i++) {
      //meeting point is in l
      update(l.peak, max(i, r.peak), l.costl[i] + r.left[i]);
      update(i, ans.peak, l.costr[i] + r.left[l.peak]);
      //meeting point is in r
      update(ans.peak, i, l.right[r.peak] + r.costl[i]);
      update(max(l.peak, i), r.peak, l.right[i] + r.costr[i]);
    }
    return ans;
  });

  vector<int64> ans(q);
  for (int i = 0; i < q; i++) {
    const node x = st.get(L[i], R[i]);
    ans[i] = min(*min_element(x.costl.begin(), x.costl.end()),
                 *min_element(x.costr.begin(), x.costr.end()));
  }

  return ans;
}

vector<int64> subtask12(const vector<int> &H, const vector<int> &L, const vector<int> &R) {
  const int n = H.size(), q = L.size();

  vector<int64> ans(q, kInf64);
  vector<int64> cost(n);

  auto initialise_cost = [&]() {
    for (int i = 0; i < n; i++) {
      cost[i] = -H[i];
    }
  };

  for (int query = 0; query < q; query++) {
    initialise_cost();
    vector<pair<int64, int>> stk = {{kInf64, 0}};
    int64 sum = 0;
    //left to right
    for (int i = L[query]; i <= R[query]; i++) {
      int cnt = 1;
      while (stk.back().first <= H[i]) {
        const auto &[h, c] = stk.back();
        cnt += c;
        sum -= h * 1LL * c;
        stk.pop_back();
      }
      stk.emplace_back(H[i], cnt);
      sum += H[i] * 1LL * cnt;
      cost[i] += sum;
    }
    stk = {{kInf64, 0}};
    sum = 0;
    //right to left
    for (int i = R[query]; i >= L[query]; i--) {
      int cnt = 1;
      while (stk.back().first <= H[i]) {
        const auto &[h, c] = stk.back();
        cnt += c;
        sum -= h * 1LL * c;
        stk.pop_back();
      }
      stk.emplace_back(H[i], cnt);
      sum += H[i] * 1LL * cnt;
      cost[i] += sum;
    }
    //store the answer
    ans[query] = *min_element(cost.begin() + L[query], cost.begin() + R[query] + 1);
  }
  return ans;
}

std::vector<long long> minimum_costs(std::vector<int> H, std::vector<int> L, std::vector<int> R) {
  const int maxHeight = *max_element(H.begin(), H.end());
  if (maxHeight <= 20) return subtask34(H, L, R);
  return subtask12(H, L, R);
}