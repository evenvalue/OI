#include <bits/stdc++.h>
using namespace std;

#ifdef evenvalue
  #include "debug.h"
  #define debug(...) print(#__VA_ARGS__, __VA_ARGS__)
#else
  #define debug(...)
#endif

using int64 = long long;
using ld = long double;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using max_heap = priority_queue<T, vector<T>, less<T>>;

namespace read {
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
}// namespace read

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;
constexpr int kMaxN = 2e5 + 10;

struct repeat {
  int64 batch = 0;
  int64 count = 0;
};

vector<repeat> simulate(const vector<int> &fof, const vector<int> &keys) {
  bool ceil = false;
  vector<repeat> left;
  vector<repeat> right;
  for (const int b : keys) {
    const int c = fof[b];
    left.push_back({b, (c + ceil) / 2});
    right.push_back({b, (c + !ceil) / 2});
    ceil = ((c & 1) ? !ceil : ceil);
  }

  while (not right.empty()) {
    left.push_back(right.back());
    right.pop_back();
  }

  return left;
}

int64 formula(const int64 b, const int64 x, const int64 l, const int64 r) {
  const int64 part1 = l * r * x;
  const int64 part2 = b * l * x * x;
  const int64 part3 = (r - l + b * x) * b * x * (x - 1) / 2;
  const int64 part4 = b * b * x * (x - 1) * (2 * x - 1) / 6;
  return part1 + part2 + part3 - part4;
}

int64 diversities(const vector<int> &fof, const vector<int> &keys) {
  vector<repeat> repeats = simulate(fof, keys);

  const int kReps = repeats.size();
  vector<int64> pref(kReps);
  vector<int64> suff(kReps);
  for (int i = 1; i < kReps; i++) {
    pref[i] = pref[i - 1] + (repeats[i - 1].batch * repeats[i - 1].count);
  }
  for (int i = kReps - 2; i >= 0; i--) {
    suff[i] = suff[i + 1] + (repeats[i + 1].batch * repeats[i + 1].count);
  }

  const int64 n = suff[0] + repeats[0].batch * repeats[0].count;
  int64 ans = n * (n + 1) / 2;
  for (int i = 0; i < kReps; i++) {
    ans += formula(repeats[i].batch, repeats[i].count, pref[i], suff[i]);
  }

  return ans;
}

inline int64 hilbertOrder(int x, int y, int pow, int rotate) {
  if (pow == 0) {
    return 0;
  }
  int hpow = 1 << (pow - 1);
  int seg = (x < hpow) ? ((y < hpow) ? 0 : 3)
                       : ((y < hpow) ? 1 : 2);
  seg = (seg + rotate) & 3;
  const int rotateDelta[4] = {3, 0, 0, 1};
  int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
  int nrot = (rotate + rotateDelta[seg]) & 3;
  int64 subSquareSize = int64(1) << (2 * pow - 2);
  int64 ans = seg * subSquareSize;
  int64 add = hilbertOrder(nx, ny, pow - 1, nrot);
  ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
  return ans;
}


class mo_s {
  struct query {
    int l, r, v, t;
    int64 hilbert;
    int64 ans;

    query(const int l, const int r, const int v, const int t, const int64 h) : l(l), r(r), v(v), t(t), hilbert(h), ans(0) {}
  };

  const int kBlockSize = 550;

  const int n;
  const vector<int> a;
  vector<query> queries;

  [[nodiscard]] int block_of(const int i) const {
    return i / kBlockSize;
  }

public:
  explicit mo_s(const vector<int> &a) : n(a.size()), a(a) {}

  void add_query(const int l, const int r, const int v, const int t) {
    const int64 order = hilbertOrder(l, r, 20, 0);
    queries.emplace_back(l, r, v, t, order);
  }

  vector<int64> solve() {
    sort(queries.begin(), queries.end(), [&](const query &q1, const query &q2) {
      return q1.hilbert < q2.hilbert;
    });

    const int kDistinct = *max_element(a.begin(), a.end()) + 1;

    const int kMaxFreq = 3e5;
    vector<int> freq(kDistinct);
    vector<int> fof(kMaxFreq + 1);//frequency of frequencies
    vector<int> options;

    fof[0] = kDistinct;

    auto add = [&](const int i) {
      const int f = freq[a[i]]++;
      fof[f]--;
      fof[f + 1]++;
      options.push_back(f + 1);
    };

    auto rem = [&](const int i) {
      const int f = freq[a[i]]--;
      fof[f]--;
      fof[f - 1]++;
      options.push_back(f - 1);
    };

    for (int i = 0, l = 0, r = -1; i < queries.size(); i++) {
      while (l > queries[i].l) add(--l);
      while (r < queries[i].r) add(++r);
      while (l < queries[i].l) rem(l++);
      while (r > queries[i].r) rem(r--);

      options.erase(remove_if(options.begin(), options.end(), [&](const int x) {
                      return fof[x] == 0;
                    }),
                    options.end());
      sort(options.begin(), options.end());
      options.erase(unique(options.begin(), options.end()), options.end());

      queries[i].ans = diversities(fof, options);
    }

    sort(queries.begin(), queries.end(), [](const query &q1, const query &q2) {
      return q1.t < q2.t;
    });

    vector<int64> ans(queries.size());
    for (int i = 0; const query &q : queries) {
      ans[i++] = q.ans;
    }
    return ans;
  }
};

template<typename T>
class CoordinateCompression {
  bool sorted = false;
  vector<T> v;

public:
  void add(const T &x) {
    v.push_back(x);
  }

  void compress() {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    sorted = true;
  }

  int get(const int x) {
    if (not sorted) assert(false);
    return distance(v.begin(), lower_bound(v.begin(), v.end(), x));
  }

  int size() {
    return v.size();
  }
};

vector<int> compress(vector<int> a) {
  CoordinateCompression<int> cc;
  for (const int x : a) {
    cc.add(x);
  }
  cc.compress();
  for (int &x : a) {
    x = cc.get(x);
  }
  return a;
}

inline void solution() {
  const int n = read::Int();
  const int q = read::Int();
  const vector<int> a = compress(read::Vec<int>(n));

  mo_s mo(a);
  for (int i = 0; i < q; i++) {
    const int l = read::Int() - 1;
    const int r = read::Int() - 1;
    mo.add_query(l, r, 0, i);
  }

  vector<int64> ans = mo.solve();
  for (const int64 x : ans) {
    cout << x << '\n';
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