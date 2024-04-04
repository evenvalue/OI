#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
  #define debug(...)
#endif

using int64 = long long;
using ld = long double;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using max_heap = priority_queue<T, vector<T>, less<T>>;

template<typename T>
T read() {
  T x;
  cin >> x;
  return x;
}

template<typename T1, typename T2>
pair<T1, T2> read_pair() {
  pair<T1, T2> p;
  cin >> p.first;
  cin >> p.second;
  return p;
}

template<typename T>
vector<T> read_vec(const int n, const int index = 0) {
  vector<T> v(n + index);
  for (int i = index; i < n + index; i++) {
    v[i] = read<T>();
  }
  return v;
}

template<typename T>
vector<vector<T>> read_vec_vec(const int n, const int m, const int index_n = 0, const int index_m = 0) {
  vector<vector<T>> grid(n + index_n);
  for (int i = index_n; i < n + index_n; i++) {
    grid[i] = read_vec<T>(m, index_m);
  }
  return grid;
}

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;
constexpr int kMaxN = 2e5 + 10;

inline void solution() {
  const int kBits = read<int>();
  const int n = read<int>();
  auto a = read_vec<int>(n);
  a.insert(a.end(), a.begin(), a.end());

  vector<array<vector<int>, 2>> freq(kBits);
  for (int bit = 0; bit < kBits; bit++) {
    freq[bit][0].push_back(-1);
    freq[bit][1].push_back(-1);
    for (int i = 0; i < 2 * n; i++) {
      const int val = (a[i] >> bit) & 1;
      freq[bit][val].push_back(i);
    }
    freq[bit][0].push_back(kInf);
    freq[bit][1].push_back(kInf);
  }

  vector<array<int, 2>> first(kBits);
  vector<array<int, 2>> final(kBits);

  auto increment_first = [&](const int bit, const int val, const int l) {
    while (true) {
      const int i = first[bit][val];
      if (freq[bit][val][i] < l) {
        first[bit][val]++;
      }
      if (i == first[bit][val]) break;
    }
    return freq[bit][val][first[bit][val]];
  };

  auto increment_final = [&](const int bit, const int val, const int r) {
    while (true) {
      const int i = final[bit][val];
      if (freq[bit][val][i + 1] <= r) {
        final[bit][val]++;
      }
      if (i == final[bit][val]) break;
    }
    return freq[bit][val][final[bit][val]];
  };

  int64 ans = 0;
  for (int l = 0; l < n; l++) {
    const int r = l + n - 1;
    int left = l, right = r;
    for (int bit = 0; bit < kBits; bit++) {
      for (const int val : {0, 1}) {
        const int x = increment_first(bit, val, l);
        const int y = increment_final(bit, val, r);
        if (y < x) continue;
        if (x == y) {
          left = kInf;
          right = -1;
        } else {
          left = max(left, x);
          right = min(right, y);
        }
      }
    }
    ans += max(0, right - left);
  }

  cout << ans / 2 << '\n';
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