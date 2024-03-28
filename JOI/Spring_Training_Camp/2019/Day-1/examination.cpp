#include <bits/stdc++.h>
using namespace std;

#ifdef evenvalue
  #include "debug.h"
#else
  #define debug(...)
#endif

using int64 = long long;
using ld = long double;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using max_heap = priority_queue<T, vector<T>, less<T>>;

namespace Read {
int Int() {
  int x;
  cin >> x;
  return x;
}
int64 Int64() {
  int64 x;
  cin >> x;
  return x;
}
char Char() {
  char c;
  cin >> c;
  return c;
}
string String() {
  string s;
  cin >> s;
  return s;
}
double Double() {
  return stod(String());
}
ld LongDouble() {
  return stold(String());
}
template<typename T1, typename T2>
pair<T1, T2> Pair() {
  pair<T1, T2> p;
  cin >> p.first >> p.second;
  return p;
}
template<typename T>
vector<T> Vec(const int n) {
  vector<T> v(n);
  for (T &x : v) {
    cin >> x;
  }
  return v;
}
template<typename T>
vector<vector<T>> VecVec(const int n, const int m) {
  vector<vector<T>> v(n);
  for (vector<T> &vec : v) {
    vec = Vec<T>(m);
  }
  return v;
}
}//namespace Read

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;
constexpr int kMaxN = 2e5 + 10;

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

  int query(const int x, const int l, const int r, const int ql, const int qr, const int q) {
    if (ql <= l and r <= qr) {
      const auto it = lower_bound(t[x].begin(), t[x].end(), q);
      return distance(it, t[x].end());
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (qr <= mid) {
      return query(x + 1, l, mid, ql, qr, q);
    } else if (mid < ql) {
      return query(y, mid + 1, r, ql, qr, q);
    } else {
      return query(x + 1, l, mid, ql, qr, q) + query(y, mid + 1, r, ql, qr, q);
    }
  }

public:
  MergeSortTree(const vector<int> &a) : n(a.size()), t(2 * n - 1) {
    build(0, 0, n - 1, a);
  }

  int query(const int ql, const int qr, const int q) {
    if (ql > qr) return 0;
    return query(0, 0, n - 1, ql, qr, q);
  }
};

struct Student {
  int math;
  int info;

  bool operator<(const Student &other) const {
    return math < other.math;
  }
};

inline void solution() {
  const int n = Read::Int();
  const int m = Read::Int();

  vector<Student> students(n);
  for (auto &[a, b] : students) {
    a = Read::Int();
    b = Read::Int();
  }

  sort(students.begin(), students.end());

  vector<int> sum(n);
  for (int i = 0; i < n; i++) {
    sum[i] = students[i].math + students[i].info;
  }

  vector<int> informatics(n);
  for (int i = 0; i < n; i++) {
    informatics[i] = students[i].info;
  }

  auto get_range = [&](const int l, const int r) -> pair<int, int> {
    int lo = 0, hi = n;
    while (lo < hi) {
      const int mid = (lo + hi) / 2;
      if (students[mid].math >= l) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }
    const int left = lo;
    lo = -1, hi = n - 1;
    while (lo < hi) {
      const int mid = (lo + hi + 1) / 2;
      if (students[mid].math >= r) {
        hi = mid - 1;
      } else {
        lo = mid;
      }
    }
    const int right = lo;
    return {left, right};
  };

  MergeSortTree total(sum);
  MergeSortTree info(informatics);

  for (int qry = 0; qry < m; qry++) {
    const int a = Read::Int();
    const int b = Read::Int();
    const int c = Read::Int();
    const auto [l1, r1] = get_range(a, c - b);
    const auto [l2, r2] = get_range(max(a, c - b), kInf);
    cout << total.query(l1, r1, c) + info.query(l2, r2, b) << '\n';
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);

  cout << fixed << setprecision(10);

  int testcases = 1;
  //cin >> testcases;
  while (testcases--) {
    solution();
  }
}