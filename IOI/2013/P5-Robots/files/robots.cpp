#include "robots.h"
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

struct Toy {
  int mass;
  int size;

  auto operator<(const Toy &other) const {
    return mass < other.mass;
  }
};

int putaway(const int n, const int m, const int t, int X[], int Y[], int W[], int S[]) {
  vector<int> weak(n);
  vector<int> small(m);

  for (int i = 0; i < n; i++) {
    weak[i] = X[i];
  }
  for (int i = 0; i < m; i++) {
    small[i] = Y[i];
  }

  sort(weak.rbegin(), weak.rend());
  sort(small.begin(), small.end());

  vector<Toy> toys(t);
  for (int i = 0; i < t; i++) {
    toys[i].mass = W[i];
    toys[i].size = S[i];
  }

  sort(toys.begin(), toys.end(), [](const auto b1, const auto b2) {
    return b1.size < b2.size;
  });

  auto check = [&](const int time) -> bool {
    max_heap<Toy> heap;

    int j = 0;
    for (int i = 0; i < m; i++) {
      while (j < t and toys[j].size < small[i]) {
        heap.push(toys[j]);
        j++;
      }
      for (int k = 0; k < time and not heap.empty(); k++) {
        heap.pop();
      }
    }

    while (j < t) {
      heap.push(toys[j]);
      j++;
    }

    for (const int x : weak) {
      if (heap.empty()) break;
      if (heap.top().mass >= x) return false;
      for (int k = 0; k < time and not heap.empty(); k++) {
        heap.pop();
      }
    }

    return heap.empty();
  };

  int lo = 0, hi = t + 1;
  while (lo < hi) {
    const int mid = (lo + hi) / 2;
    if (check(mid)) {
      hi = mid;
    } else {
      lo = mid + 1;
    }
  }

  return (lo == t + 1 ? -1 : lo);
}
