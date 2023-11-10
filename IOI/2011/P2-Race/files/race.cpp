#include "race.h"
#include <bits/stdc++.h>
using namespace std;

#ifdef evenvalue
  #include "debug.h"
#else
  #define debug(...)
#endif

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using max_heap = priority_queue<T, vector<T>, less<T>>;

using int64 = long long;
using ld = long double;

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;

int best_path(const int n, const int k, int H[][2], int L[]) {
  vector<vector<pair<int, int>>> g(n);
  for (int i = 0; i < n - 1; i++) {
    const int x = H[i][0];
    const int y = H[i][1];
    const int w = L[i];
    g[x].emplace_back(y, w);
    g[y].emplace_back(x, w);
  }

  vector<int> sz(n);
  vector<bool> decomposed(n);

  function<int(int, int)> subtree_size = [&](const int x, const int p) {
    sz[x] = 1;
    for (const auto [y, w] : g[x]) {
      if (decomposed[y] or y == p) continue;
      sz[x] += subtree_size(y, x);
    }
    return sz[x];
  };

  function<int(int, int, int)> centroid = [&](const int x, const int p, const int size) {
    int c = x;
    for (const auto [y, w] : g[x]) {
      if (decomposed[y] or y == p) continue;
      if (2 * sz[y] < size) continue;
      c = centroid(y, x, size);
      break;
    }
    return c;
  };

  int ans = kInf;

  struct Dist {
    int weight_dist;
    int edge_dist;
  };

  auto calc_dist = [&](const int root, const int parent, Dist d) -> vector<Dist> {
    vector<Dist> distances;
    function<void(int, int, Dist)> rec = [&](int x, int p, Dist d) {
      if (d.weight_dist > k) return;
      distances.push_back(d);
      for (const auto [y, w] : g[x]) {
        if (decomposed[y] or y == p) continue;
        rec(y, x, Dist{ d.weight_dist + w, d.edge_dist + 1});
      }
    };
    rec(root, parent, d);
    return distances;
  };

  vector<pair<int, int>> path(k + 1, {kInf, -1});

  function<void(int)> decompose = [&](int x) {
    x = centroid(x, -1, subtree_size(x, -1));
    decomposed[x] = true;
    path[0] = {0, x};

    for (const auto [y, w] : g[x]) {
      if (decomposed[y]) continue;
      vector<Dist> distances = calc_dist(y, x, Dist{w, 1});
      for (const auto [weight_dist, edge_dist] : distances) {
        if (0 <= weight_dist and weight_dist <= k and path[k - weight_dist].second == x) {
          ans = min(ans, path[k - weight_dist].first + edge_dist);
        }
      }
      for (const auto [weight_dist, edge_dist] : distances) {
        if (0 <= weight_dist and weight_dist <= k) {
          if (path[weight_dist].second != x or path[weight_dist].first >= edge_dist) {
            path[weight_dist].first = edge_dist;
            path[weight_dist].second = x;
          }
        }
      }
    }

    for (const auto [y, w] : g[x]) {
      if (decomposed[y]) continue;
      decompose(y);
    }
  };

  decompose(0);
  return (ans == kInf ? -1 : ans);
}
