#include "supertrees.h"
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
    return (e[x] < 0 ? x : pfind(e[x]));
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

vector<vector<int>> ways;
vector<vector<int>> ans;

void connect(const int x, const int y) {
  ans[x][y] = 1;
  ans[y][x] = 1;
}

bool connect1(const vector<int> &nodes) {
  if (nodes.size() < 2) return false;
  for (int i = 0; i < nodes.size() - 1; i++) {
    connect(nodes[i], nodes[i + 1]);
  }
  return true;
}

bool connect2(const vector<int> &nodes) {
  if (nodes.size() < 3) return false;
  connect1(nodes);
  connect(nodes.front(), nodes.back());
  return true;
}

bool solve(const vector<int> &nodes) {
  const int n = (int) nodes.size();

  dsu d(n);
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      const int way = ways[nodes[i]][nodes[j]];
      if (way == 1) {
        d.unite(i, j);
      } else if (way == 3) {
        return false;
      }
    }
  }

  const vector<vector<int>> lines = d.components();
  for (auto line : lines) {
    for (int i = 0; i < line.size(); i++) {
      for (int j = i + 1; j < line.size(); j++) {
        const int x = nodes[line[i]];
        const int y = nodes[line[j]];
        if (ways[x][y] != 1) return false;
      }
    }
    for (int &i : line) {
      i = nodes[i];
    }
    connect1(line);
  }

  if (lines.size() == 1) return true;

  vector<int> cycle;
  for (const auto &line : lines) {
    cycle.push_back(nodes[line[0]]);
  }

  return connect2(cycle);
}

int construct(vector<std::vector<int>> p) {
  const int n = (int) p.size();
  ways = p;

  dsu d(n);
  vector<pair<int, int>> disjoint;
  for (int x = 0; x < n; x++) {
    for (int y = x + 1; y < n; y++) {
      if (p[x][y] == 0) {
        disjoint.emplace_back(x, y);
      } else {
        d.unite(x, y);
      }
    }
  }

  for (const auto &[x, y] : disjoint) {
    if (d.same(x, y)) return false;
  }

  ans.assign(n, vector<int>(n));

  const auto components = d.components();
  for (const auto &component : components) {
    if (not solve(component)) return false;
  }

  build(ans);
  return true;
}
