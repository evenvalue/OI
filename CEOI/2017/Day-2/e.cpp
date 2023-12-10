#include <bits/stdc++.h>
using namespace std;

#define int long long

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
}//namespace read

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod1 = 1e9 + 7;
constexpr int kMod2 = 1e9 + 9;
constexpr int kMaxN = 2e5 + 10;
constexpr int kPrime = 137;

inline void solution() {
  const string s = read::String();
  const int n = s.size();

  auto to_int = [&](const char c) {
    return c - 'a' + 1;
  };

  int pref1 = 0, pref2 = 0;
  int suff1 = 0, suff2 = 0;

  int ans = 0;

  int i = 0, j = n - 1;
  for (int p1 = 1, p2 = 1; i < j; i++, j--) {
    pref1 += (to_int(s[i]) * p1) % kMod1;
    pref2 += (to_int(s[i]) * p2) % kMod2;

    pref1 %= kMod1;
    pref2 %= kMod2;

    suff1 = (to_int(s[j]) + (suff1 * kPrime) % kMod1) % kMod1;
    suff2 = (to_int(s[j]) + (suff2 * kPrime) % kMod2) % kMod2;

    if (pref1 == suff1 and pref2 == suff2) {
      pref1 = pref2 = 0;
      suff1 = suff2 = 0;
      p1 = p2 = 1;
      ans += 2;
    } else {
      p1 *= kPrime;
      p2 *= kPrime;
      p1 %= kMod1;
      p2 %= kMod2;
    }
  }

  ans += (pref1 != 0 or i == j);

  cout << ans << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);

  cout << fixed << setprecision(10);

  int testcases = 1;
  cin >> testcases;
  while (testcases--) {
    solution();
  }
}
