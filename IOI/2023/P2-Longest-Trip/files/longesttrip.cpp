#include "longesttrip.h"
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

std::vector<int> longest_trip(const int n, int D) {
  vector<vector<bool>> edge(n, vector<bool>(n));
  dsu g(n);
  for (int x = 0; x < n; x++) {
    for (int y = x + 1; y < n; y++) {
      if (not are_connected({x}, {y})) continue;
      edge[x][y] = edge[y][x] = true;
      g.unite(x, y);
    }
  }

  if (g.comp == 2) {
    auto comps = g.components();
    return (comps[0].size() > comps[1].size() ? comps[0] : comps[1]);
  }

  vector<int> path;
  vector<int> nbr;
  vector<bool> visit(n);

  path.push_back(0);
  visit[0] = true;

  for (int x = 0; x < n; x++) {
    if (edge[0][x]) nbr.push_back(x);
  }

  while (not nbr.empty()) {
    const int x = nbr.back();
    nbr.pop_back();

    if (visit[x]) continue;
    visit[x] = true;

    if (edge[x][path.front()]) {
      path.insert(path.begin(), x);
    } else if (edge[x][path.back()]) {
      path.insert(path.end(), x);
    } else {
      int y = 0;
      for (; y < n; y++) {
        if (not visit[y]) continue;
        if (not edge[x][y]) continue;
        break;
      }

      const auto it = find(path.begin(), path.end(), y);
      rotate(path.begin(), it, path.end());
      path.insert(path.begin(), x);
    }

    for (int y = 0; y < n; y++) {
      if (edge[y][x]) nbr.push_back(y);
    }
  }

  return path;
}
