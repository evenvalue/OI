#include "koninc.h"
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

struct node {
  int mini = kInf;
  int lazy = 0;
  int mature = 0;
};

class SegTree {
  int n;
  vector<node> t;

  static node unite(const node &l, const node &r) {
    node ans;
    ans.mini = min(l.mini, r.mini);
    ans.mature = l.mature + r.mature;
    return ans;
  }

  void push(const int x, const int l, const int r) {
    if (t[x].lazy == 0) return;
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    for (const int child : {x + 1, y}) {
      t[child].mini -= t[x].lazy;
      t[child].lazy += t[x].lazy;
    }
    t[x].lazy = 0;
  }

  void build(const int x, const int l, const int r, const vector<node> &a) {
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

  void decrease(const int x, const int l, const int r, const int ql, const int qr) {
    if (ql <= l and r <= qr and t[x].mini > 1) {
      t[x].mini--;
      t[x].lazy++;
      return;
    }
    if (l == r) {
      t[x].mini = kInf;
      t[x].lazy = 0;
      t[x].mature = 1;
      return;
    }
    push(x, l, r);
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (ql <= mid) {
      decrease(x + 1, l, mid, ql, qr);
    }
    if (mid < qr) {
      decrease(y, mid + 1, r, ql, qr);
    }
    t[x] = unite(t[x + 1], t[y]);
  }

  node query(const int x, const int l, const int r, const int ql, const int qr) {
    if (ql <= l and r <= qr) return t[x];
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    push(x, l, r);
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
  SegTree() : n(0) {}
  SegTree(vector<node> &a) : n(a.size()), t(2 * n - 1) {
    build(0, 0, n - 1, a);
  }

  void decrease(const int l, const int r) {
    decrease(0, 0, n - 1, l, r);
  }

  int query(const int l, const int r) {
    return query(0, 0, n - 1, l, r).mature;
  }
};

SegTree st;

void inicjuj(int N, int K, int *D) {
  vector<node> a(N);
  for (int i = 0; i < N; i++) {
    const int req = (D[i] < K ? K - D[i] : kInf);
    a[i].mini = req;
    a[i].mature = (req == kInf);
  }
  st = SegTree(a);
}

//water the plants
void podlej(int a, int b) {
  st.decrease(a, b);
}

//query mature
int dojrzale(int a, int b) {
  return st.query(a, b);
}
