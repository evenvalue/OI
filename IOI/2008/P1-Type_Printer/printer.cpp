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

class Trie {
  static constexpr int kAlphaSize = 26;

  vector<array<int, kAlphaSize>> t;
  vector<bool> terminal;
  vector<int> max_depth;

  int add_node() {
    const int x = t.size();
    t.emplace_back();
    terminal.push_back(false);
    max_depth.push_back(0);
    t.back().fill(-1);
    return x;
  }

  void dfs1(const int x, const int d) {
    max_depth[x] = d;
    for (const int y : t[x]) {
      if (y == -1) continue;
      dfs1(y, d + 1);
      max_depth[x] = max(max_depth[x], max_depth[y]);
    }
  }

  void dfs2(const int x, string &ans) {
    vector<int> order(kAlphaSize);
    iota(order.begin(), order.end(), 0);

    sort(order.begin(), order.end(), [&](const int i, const int j) {
      const int a = t[x][i];
      const int b = t[x][j];
      if (a == -1) return false;
      if (b == -1) return true;
      return max_depth[a] < max_depth[b];
    });

    if (terminal[x]) {
      ans += 'P';
    }

    for (const int i : order) {
      if (t[x][i] == -1) continue;
      ans += ('a' + i);
      dfs2(t[x][i], ans);
      ans += '-';
    }
  }

public:
  Trie() {
    add_node();
  }

  void add(const string &s) {
    int x = 0;
    for (const char c : s) {
      const int i = c - 'a';
      if (t[x][i] == -1) t[x][i] = add_node();
      x = t[x][i];
    }
    terminal[x] = true;
  }

  string get_answer() {
    string ans;
    dfs1(0, 0);
    dfs2(0, ans);
    while (ans.back() == '-') {
      ans.pop_back();
    }
    return ans;
  }
};

inline void solution() {
  const int n = Read::Int();
  Trie t;
  for (int i = 0; i < n; i++) {
    t.add(Read::String());
  }
  const string ans = t.get_answer();
  cout << ans.size() << '\n';
  for (const char c : ans) {
    cout << c << '\n';
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