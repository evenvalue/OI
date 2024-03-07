#include "game.h"
#include <bits/stdc++.h>
using namespace std;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using max_heap = priority_queue<T, vector<T>, less<T>>;

using int64 = long long;
using ld = long double;

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;

class dsu {
  int n;
  std::vector<int> e;

  int pfind(const int x) {
    return (e[x] < 0 ? x : e[x] = pfind(e[x]));
  }

public:
  dsu() : n(0), comp(0) {}
  explicit dsu(const int n) : n(n), comp(n), e(n, -1) {}

  int comp;

  int find(const int x) {
    assert(0 <= x and x < n);
    return pfind(x);
  }

  bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    if (e[x] > e[y]) swap(x, y);
    e[x] += e[y];
    e[y] = x;
    comp--;
    return true;
  }

  bool same(const int x, const int y) {
    return (find(x) == find(y));
  }

  int size(const int x) {
    return -e[find(x)];
  }

  std::vector<std::vector<int>> components() {
    std::vector<std::vector<int>> res(n);
    for (int x = 0; x < n; x++) {
      res[pfind(x)].push_back(x);
    }
    res.erase(
        std::remove_if(res.begin(), res.end(), [&](const std::vector<int> &v) { return v.empty(); }),
        res.end());
    return res;
  }
};

int n;
dsu d;
vector<vector<int>> edges;

void initialize(const int N) {
  n = N;
  d = dsu(n);
  edges = vector<vector<int>>(n, vector<int>(n));
}

int hasEdge(int x, int y) {
  x = d.find(x);
  y = d.find(y);

  edges[x][y]++, edges[y][x]++;
  const int cur = edges[x][y];
  const int req = d.size(x) * d.size(y);

  if (cur == req) {
    d.unite(x, y);
    if (x != d.find(x)) swap(x, y);
    for (int z = 0; z < n; z++) {
      if (d.find(z) != z) continue;
      edges[x][z] += edges[y][z];
      edges[z][x] += edges[z][y];
    }
  }

  return (cur == req);
}