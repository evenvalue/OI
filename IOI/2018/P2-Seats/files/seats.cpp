#include "seats.h"
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

struct node {
  int sum = 0;
  int mini = 0;
  int cnt = 0;
};

int n, m, total_seats;
vector<int> R, C;
SegTree<node> st;
vector<vector<int>> grid;

const vector<pair<int, int>> top_left = {
    {-1, -1},
    {-1, 0},
    {0, -1},
    {0, 0}};
const vector<pair<int, int>> nbr = {
    {0, 0},
    {0, 1},
    {1, 0},
    {1, 1}};

inline bool exists(const int row, const int col) {
  return (0 <= row and row < n and 0 <= col and col < m);
}

inline int calc_delta(const int x) {
  const int row = R[x], col = C[x];

  int delta = 0;
  vector<int> v;
  for (auto [r, c] : top_left) {
    r += R[x], c += C[x];
    for (const auto &[dr, dc] : nbr) {
      if (not exists(r + dr, c + dc)) continue;
      v.push_back(grid[r + dr][c + dc]);
    }
    sort(v.begin(), v.end());
    const int pos = (int)distance(v.begin(), find(v.begin(), v.end(), grid[row][col]));
    if (pos == 0) delta++;
    if (pos == 1) delta--;
    if (pos == 2) delta++;
    if (pos == 3) delta--;
    v.clear();
  }
  return delta;
}

void give_initial_chart(const int H, const int W, std::vector<int> R_, std::vector<int> C_) {
  n = H, m = W;
  total_seats = n * m;
  R = move(R_), C = move(C_);
  grid.resize(n, vector<int>(m));
  st = SegTree<node>(total_seats, node(), [&](const node &l, const node &r) {
    node ret{};
    ret.sum = l.sum + r.sum;
    if (l.mini == l.sum + r.mini) {
      ret.mini = l.mini;
      ret.cnt = l.cnt + r.cnt;
    } else if (l.mini < l.sum + r.mini) {
      ret.mini = l.mini;
      ret.cnt = l.cnt;
    } else {
      ret.mini = l.sum + r.mini;
      ret.cnt = r.cnt;
    }
    return ret;
  });

  for (int seat = 0; seat < total_seats; seat++) {
    grid[R[seat]][C[seat]] = seat;
  }

  for (int seat = 0; seat < total_seats; seat++) {
    const int delta = calc_delta(seat);
    st.set(seat, {delta, delta, 1});
  }
}

int swap_seats(const int x, const int y) {
  swap(grid[R[x]][C[x]], grid[R[y]][C[y]]);
  swap(R[x], R[y]);
  swap(C[x], C[y]);
  for (const int pt : {x, y}) {
    for (auto [r, c] : top_left) {
      r += R[pt], c += C[pt];
      for (const auto &[dr, dc] : nbr) {
        if (not exists(r + dr, c + dc)) continue;
        const int seat = grid[r + dr][c + dc];
        const int delta = calc_delta(seat);
        st.set(seat, {delta, delta, 1});
      }
    }
  }
  return st.get(0, total_seats - 1).cnt;
}
