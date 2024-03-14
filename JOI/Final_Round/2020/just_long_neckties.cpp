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

struct elem {
  int x;
  int i;

  bool operator<(const elem &other) const {
    return x < other.x;
  }
};

inline void solution() {
  const int n = Read::Int();

  vector<elem> a(n + 1);
  for (int i = 0; i <= n; i++) {
    a[i].x = Read::Int();
    a[i].i = i;
  }

  vector<int> b = Read::Vec<int>(n);

  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  vector<int> pref(n);
  vector<int> suff(n);

  for (int i = 0; i < n; i++) {
    pref[i] = a[i].x - b[i];
    if (i != 0) pref[i] = max(pref[i], pref[i - 1]);
  }
  for (int i = n - 1; i >= 0; i--) {
    suff[i] = a[i + 1].x - b[i];
    if (i != n - 1) suff[i] = max(suff[i], suff[i + 1]);
  }

  vector<int> ans(n + 1);
  for (int i = 0; i <= n; i++) {
    const int part1 = (i == 0 ? 0 : pref[i - 1]);
    const int part2 = (i == n ? 0 : suff[i]);
    ans[a[i].i] = max({part1, part2, 0});
  }

  for (const int x : ans) {
    cout << x << ' ';
  }
  cout << '\n';
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
