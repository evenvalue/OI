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
}//namespace read

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;

enum class gravity {
  fall = 0,
  rise = 1
};

struct cell {
  int x;
  int y;
  gravity g;
};

inline void solution() {
  const int n = read::Int();
  const int m = read::Int();
  const int rows = n + 2;
  const int cols = m + 2;

  const int grid_size = rows * cols;

  cell captain{};
  cell doctor{};

  vector<string> grid(n + 2, string(m + 2, '.'));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      grid[i][j] = read::Char();
      if (grid[i][j] == 'C') {
        captain.x = i;
        captain.y = j;
        captain.g = gravity::fall;
      } else if (grid[i][j] == 'D') {
        doctor.x = i;
        doctor.y = j;
        doctor.g = gravity::fall;
      }
    }
  }

  auto valid = [&](const cell &c) {
    const bool good_rows = (0 <= c.x and c.x < rows);
    const bool good_cols = (0 <= c.y and c.y < cols);
    return good_rows and good_cols;
  };

  auto get_hash = [&](const cell &c) {
    const int hash = (grid_size * (c.g == gravity::rise)) + (cols * c.x) + c.y;
    return hash;
  };

  auto get_cell = [&](int hash) {
    cell ans{};
    ans.g = (hash < grid_size ? gravity::fall : gravity::rise);
    ans.x = (hash % grid_size) / cols;
    ans.y = ((hash % grid_size) % cols);
    return ans;
  };

  auto can_go = [&](const int hash)-> bool {
    const cell cur = get_cell(hash);
    if (not valid(cur)) return false;
    return (grid[cur.x][cur.y] != '#');
  };

  auto get_left = [&](const int hash) {
    cell cur = get_cell(hash);
    cur.y--;
    return get_hash(cur);
  };

  auto get_right = [&](const int hash) {
    cell cur = get_cell(hash);
    cur.y++;
    return get_hash(cur);
  };

  auto get_down = [&](const int hash) {
    cell cur = get_cell(hash);
    cur.x++;
    return get_hash(cur);
  };

  auto get_up = [&](const int hash) {
    cell cur = get_cell(hash);
    cur.x--;
    return get_hash(cur);
  };

  auto get_direction = [&](int hash) {
    if (hash < grid_size) {
      return get_down(hash);
    } else {
      return get_up(hash);
    }
  };

  auto gravity_flip = [&](const int hash) {
    cell cur = get_cell(hash);
    cur.g = (cur.g == gravity::fall ? gravity::rise : gravity::fall);
    return get_hash(cur);
  };

  vector<vector<pair<int, int>>> g(2 * grid_size);
  for (gravity dir : {gravity::fall, gravity::rise}) {
    for (int row = 1; row <= n; row++) {
      for (int col = 1; col <= m; col++) {
        cell c = {row, col, dir};
        const int x = get_hash(c);
        if (can_go(get_direction(x))) {
          g[x].emplace_back(get_direction(x), 0);
        } else {
          if (can_go(get_left(x))) {
            g[x].emplace_back(get_left(x), 0);
          }
          if (can_go(get_right(x))) {
            g[x].emplace_back(get_right(x), 0);
          }
          g[x].emplace_back(gravity_flip(x), 1);
        }
      }
    }
  }

  auto bfs01 = [&](const int source) {
    vector<int> dist(2 * grid_size, kInf);
    deque<int> q;

    dist[source] = 0;
    q.push_back(source);

    while (not q.empty()) {
      const int x = q.front();
      q.pop_front();
      for (const auto [y, w] : g[x]) {
        if (dist[y] > dist[x] + w) {
          dist[y] = dist[x] + w;
          (w == 0 ? q.push_front(y) : q.push_back(y));
        }
      }
    }
    return dist;
  };

  const cell doctor1 = {doctor.x, doctor.y, gravity::fall};
  const cell doctor2 = {doctor.x, doctor.y, gravity::rise};
  const vector<int> dist = bfs01(get_hash(captain));

  const int ans = min(dist[get_hash(doctor1)], dist[get_hash(doctor2)]);
  cout << (ans >= kInf ? -1 : ans) << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  freopen("gravity.in", "r", stdin);
  freopen("gravity.out", "w", stdout);

  cout << fixed << setprecision(10);

  int testcases = 1;
  //cin >> testcases;
  while (testcases--) {
    solution();
  }
}