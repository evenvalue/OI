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
constexpr int kMaxN = 1e5 + 10;
constexpr int kMaxBet = 1e3;
constexpr int kScale = 1e4;

inline void solution() {
  const int n = Read::Int();

  vector<int> a(n);
  vector<int> b(n);

  for (int i = 0; i < n; i++) {
    a[i] = round(Read::Double() * kScale);
    b[i] = round(Read::Double() * kScale);
  }

  sort(a.rbegin(), a.rend());
  sort(b.rbegin(), b.rend());

  auto check = [&](const int64 profit) -> bool {
    int64 bought = 0;
    int64 second = 0, first = 0;

    for (int i = 0, j = 0; min(first, second) - bought < profit and (i < n or j < n);) {
      if (i != n and first == min(first, second)) {
        first += a[i++];
      } else if (j != n) {
        second += b[j++];
      } else {
        break;
      }
      bought += kScale;
    }
    return min(first, second) - bought >= profit;
  };

  int64 lo = 0, hi = kMaxN * 1LL * kMaxBet * 1LL * kScale;
  while (lo < hi) {
    const int64 mid = (lo + hi + 1) / 2;
    if (check(mid)) {
      lo = mid;
    } else {
      hi = mid - 1;
    }
  }

  cout << (ld)lo / kScale << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);

  cout << fixed << setprecision(4);

  int testcases = 1;
  //cin >> testcases;
  while (testcases--) {
    solution();
  }
}