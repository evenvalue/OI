#include <bits/stdc++.h>
using namespace std;

#define int long long

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
}//namespace read

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;
constexpr int kMaxN = 2e5 + 10;

int mod(int x) {
  while (x < 0) {
    x += kMod;
  }
  x -= (x >= kMod ? kMod : 0);
  return x;
}

struct section {
  int h;
  int w;
};

const section point = {0, 0};

int nC2(const int x) {
  return (x * 1LL * (x - 1) / 2) % kMod;
}

int fancy(const section s) {
  const int h = nC2(s.h + 1);
  const int w = nC2(s.w + 1);
  return (h * 1LL * w) % kMod;
}

int fancy(vector<section> a) {
  const int n = a.size();

  a.insert(a.begin(), point);
  vector<int> w_sum(n + 1);
  w_sum.back() = a.back().w;
  for (int i = n - 1; i >= 0; i--) {
    w_sum[i] = mod(w_sum[i + 1] + a[i].w);
  }

  int64 ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += fancy({a[i].h, w_sum[i]}) - fancy({a[i - 1].h, w_sum[i]});
    ans = mod(ans);
  }

  return ans;
}

inline void solution() {
  const int n = Read::Int();
  vector<section> a(n);
  for (int i = 0; i < n; i++) {
    a[i].h = Read::Int();
  }
  for (int i = 0; i < n; i++) {
    a[i].w = Read::Int();
  }

  a.push_back(point);

  int64 ans = 0;

  vector<section> stk = {point};
  for (section s : a) {
    int sum = 0;
    vector<section> rem;
    while (not stk.empty() and stk.back().h >= s.h) {
      rem.push_back(stk.back());
      sum = mod(sum + stk.back().w);
      stk.pop_back();
    }
    stk.push_back({s.h, (s.w + sum) % kMod});
    reverse(rem.begin(), rem.end());
    ans += fancy(rem) - (rem.empty() ? 0 : fancy({s.h, sum}));
    ans = mod(ans);
  }

  cout << ans << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  //freopen("in.txt", "r", stdin);
  //freopen(".out", "w", stdout);

  cout << fixed << setprecision(10);

  int testcases = 1;
  //cin >> testcases;
  while (testcases--) {
    solution();
  }
}
