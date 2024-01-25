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

struct Point {
  int v;
  int x;
  int y;
  int z;

  auto operator<=>(const Point &other) const {
    return v <=> other.v;
  }
};

inline void solution() {
  const int n = Read::Int();
  const int m = Read::Int();
  const int k = Read::Int();
  const int q = Read::Int();

  int remain = q;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> x_axis(0, n - 1);
  std::uniform_int_distribution<> y_axis(0, m - 1);
  std::uniform_int_distribution<> z_axis(0, k - 1);

  vector<vector<vector<int>>> grid(n, vector<vector<int>>(m, vector<int>(k)));

  auto invalid_range = [&](const int x, const int y, const int z) {
    if (x < 0 or x >= n) return true;
    if (y < 0 or y >= m) return true;
    if (z < 0 or z >= k) return true;
    return false;
  };

  auto ask = [&](const int x, const int y, const int z) {
    if (invalid_range(x, y, z)) return 0;
    if (grid[x][y][z]) return grid[x][y][z];
    if (not remain) return 0;
    cout << "? " << x + 1 << ' ' << y + 1 << ' ' << z + 1 << endl;
    remain--;
    return (grid[x][y][z] = Read::Int());
  };

  auto say = [&](const int x, const int y, const int z) {
    assert(not invalid_range(x, y, z));
    cout << "! " << x + 1 << ' ' << y + 1 << ' ' << z + 1 << endl;
  };

  const vector<tuple<int, int, int>> diff = {
      {0, 0, 1},
      {0, 0, -1},
      {0, 1, 0},
      {0, -1, 0},
      {1, 0, 0},
      {-1, 0, 0}
  };

  auto check_max = [&](const Point &cur) {
    const auto &[v, x, y, z] = cur;

    for (const auto [dx, dy, dz] : diff) {
      const Point nbr = {
          .v = ask(x + dx, y + dy, z + dz),
          .x = x + dx,
          .y = y + dy,
          .z = z + dz
      };
      if (nbr > cur) return make_pair(false, nbr);
    }
    return make_pair(true, cur);
  };

  Point best = {0, -1, -1, -1};

  for (int i = 0; i < q / 2; i++) {
    const int x = x_axis(gen);
    const int y = y_axis(gen);
    const int z = z_axis(gen);
    best = max(best, {ask(x, y, z), x, y, z});
  }

  for (int i = 0; i < q; i++) {
    const auto [found, next] = check_max(best);
    if (found) {
      say(best.x, best.y, best.z);
      return;
    }
    best = next;
  }

  say(best.x, best.y, best.z);
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