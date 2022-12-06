#include "plants.h"
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
constexpr int kLogN = 20;

class LazySegTree {
  struct Node {
    int val = kInf;
    int inc = 0;
  };

  const size_t n;
  vector<Node> t;

  static Node unite(const Node l, const Node r) {
    Node ans{};
    ans.val = min(l.val, r.val);
    ans.inc = 0;
    return ans;
  }

  void push(const int x, const int l, const int r) {
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    for (const int child : {x + 1, y}) {
      t[child].val += t[x].inc;
      t[child].inc += t[x].inc;
    }
    t[x].inc = 0;
  }

  void build(const int x, const int l, const int r, const vector<int> &a) {
    if (l == r) {
      t[x].val = a[l];
      t[x].inc = 0;
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    build(x + 1, l, mid, a);
    build(y, mid + 1, r, a);
    t[x] = unite(t[x + 1], t[y]);
  }

  int find_last_zero(const int x, const int l, const int r) {
    if (l == r) {
      return l;
    }
    push(x, l, r);
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (t[y].val == 0) {
      return find_last_zero(y, mid + 1, r);
    } else {
      return find_last_zero(x + 1, l, mid);
    }
  }

  int find_last_zero(const int x, const int l, const int r, const int ql, const int qr) {
    if (ql <= l and r <= qr) {
      return find_last_zero(x, l, r);
    }
    push(x, l, r);
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (mid < qr and t[y].val == 0) {
      const int ans = find_last_zero(y, mid + 1, r, ql, qr);
      if (ans != -1) return ans;
    }
    if (ql <= mid and t[x + 1].val == 0) {
      return find_last_zero(x + 1, l, mid, ql, qr);
    }
    return -1;
  }

  void update(const int x, const int l, const int r, const int ql, const int qr, const int value) {
    if (ql <= l and r <= qr) {
      t[x].val += value;
      t[x].inc += value;
      return;
    }
    push(x, l, r);
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (ql <= mid) {
      update(x + 1, l, mid, ql, qr, value);
    }
    if (mid < qr) {
      update(y, mid + 1, r, ql, qr, value);
    }
    t[x] = unite(t[x + 1], t[y]);
  }

  Node query(const int x, const int l, const int r, const int ql, const int qr) {
    if (ql <= l and r <= qr) {
      return t[x];
    }
    push(x, l, r);
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (qr <= mid) {
      return query(x + 1, l, mid, ql, qr);
    } else if (mid < ql) {
      return query(y, mid + 1, r, ql, qr);
    } else {
      return unite(query(x + 1, l, mid, ql, qr),
                   query(y, mid + 1, r, ql, qr));
    }
  }

public:
  explicit LazySegTree(const vector<int> &a) : n(a.size()), t(2 * n - 1) {
    build(0, 0, (int) n - 1, a);
  }

  int find_last_zero(const int l, const int r) {
    return find_last_zero(0, 0, (int) n - 1, l, r);
  }

  void update(const int l, const int r, const int x) {
    update(0, 0, (int) n - 1, l, r, x);
  }

  int query(const int l, const int r) {
    return query(0, 0, (int) n - 1, l, r).val;
  }
};

//Global Variables
int n = 0;
int k = 0;
vector<int> h;
vector<vector<int>> go_left, left_dist;
vector<vector<int>> go_right, right_dist;

vector<int> find_valid_arrangement(vector<int> r) {
  r.insert(r.end(), r.begin(), r.end());

  h.resize(n);
  int tall = n - 1;

  LazySegTree st(r);

  auto point_update = [&](const int i) {
    assert(n <= i and i < 2 * n);
    st.update(i, i, kInf);
    st.update(i - n, i - n, kInf);
  };

  auto range_update = [&](int i) {
    st.update(i - k + 1, i, -1);
    i -= n;
    const int j = i - k + 1;
    st.update(max(0, j), i, -1);
    if (j < 0) st.update(2 * n + j, 2 * n - 1, -1);
  };

  function<void(int)> find_height = [&](const int i) {
    assert(n <= i and i < 2 * n);
    while (st.query(i - k + 1, i - 1) == 0) {
      const int j = st.find_last_zero(i - k + 1, i - 1);
      find_height((j < n ? j + n : j));
    }
    h[i - n] = tall--;
    point_update(i);
    range_update(i);
  };

  while (tall >= 0) {
    assert(st.query(0, 2 * n - 1) == 0);
    const int i = st.find_last_zero(n, 2 * n - 1);
    find_height(i);
  }

  return h;
}

void init(const int _k, vector<int> r) {
  n = (int) r.size();
  k = _k;
  find_valid_arrangement(r);

  {
    const auto r_ = r;
    r.insert(r.end(), r_.begin(), r_.end());
    r.insert(r.end(), r_.begin(), r_.end());
  }

  go_left.assign(n, vector<int>(kLogN));
  go_right.assign(n, vector<int>(kLogN));
  left_dist.assign(n, vector<int>(kLogN));
  right_dist.assign(n, vector<int>(kLogN));

  set<pair<int, int>> lt, rt;

  lt.insert({-1, -1});
  for (int i = n - k + 1; i < n; i++) {
    lt.insert({h[i], i});
  }

  rt.insert({-1, -1});
  for (int i = n + 1; i < n + k; i++) {
    rt.insert({h[i % n], i});
  }

  for (int i = n; i < 2 * n; i++) {
    const int x = i - n;
    {
      auto [ht, y] = *prev(lt.lower_bound(make_pair(h[x], x)));
      go_left[x][0] = (y == -1 ? x : y % n);
      left_dist[x][0] = (y == -1 ? kInf : i - y);
    }
    {
      auto [ht, y] = *prev(rt.lower_bound(make_pair(h[x], x)));
      go_right[x][0] = (y == -1 ? x : y % n);
      right_dist[x][0] = (y == -1 ? kInf : y - i);
    }
    {
      lt.erase({h[(i - k + 1) % n], i - k + 1});
      rt.erase({h[(i + 1) % n], i + 1});

      lt.insert({h[x], i});
      rt.insert({h[(i + k) % n], i + k});
    }
  }

  for (int i = 1; i < kLogN; i++) {
    for (int x = 0; x < n; x++) {
      const int mid = go_left[x][i - 1];
      go_left[x][i] = go_left[mid][i - 1];
      left_dist[x][i] = min(kInf, left_dist[x][i - 1] + left_dist[mid][i - 1]);
    }
  }

  for (int i = 1; i < kLogN; i++) {
    for (int x = 0; x < n; x++) {
      const int mid = go_right[x][i - 1];
      go_right[x][i] = go_right[mid][i - 1];
      right_dist[x][i] = min(kInf, right_dist[x][i - 1] + right_dist[mid][i - 1]);
    }
  }
}

bool can_go_left(int x, const int y) {
  int d = (x >= y ? x - y : x + n - y);
  for (int j = kLogN - 1; j >= 0; j--) {
    if (d < left_dist[x][j]) continue;
    d -= left_dist[x][j];
    x = go_left[x][j];
  }
  return (d < k and h[x] >= h[y]);
}

bool can_go_right(int x, const int y) {
  int d = (x <= y ? y - x : y + n - x);
  for (int j = kLogN - 1; j >= 0; j--) {
    if (d < right_dist[x][j]) continue;
    d -= right_dist[x][j];
    x = go_right[x][j];
  }
  return (d < k and h[x] >= h[y]);
}

bool can_go(const int s, const int t) {
  return can_go_left(s, t) or can_go_right(s, t);
}

int compare_plants(int x, int y) {
  if (can_go(x, y)) return 1;
  if (can_go(y, x)) return -1;
  return 0;
}
