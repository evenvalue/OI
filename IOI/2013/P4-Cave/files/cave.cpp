#include "cave.h"
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

void exploreCave(int n) {
  int S[n], D[n];
  memset(S, 0, sizeof S);
  memset(D, -1, sizeof D);

  vector<int> locked(n);
  iota(locked.begin(), locked.end(), 0);

  auto colour = [&](const vector<int> &indices, const int l, const int r, const int c) {
    for (int i = l; i <= r; i++) {
      S[indices[i]] = c;
    }
  };

  for (int i = 0; i < n; i++) {
    int lo = 0, hi = locked.size() - 1;

    colour(locked, lo, hi, 0);
    const bool closed = (tryCombination(S) == i);

    while (lo < hi) {
      const int mid = (lo + hi) / 2;
      colour(locked, lo, mid, 1);
      colour(locked, mid + 1, hi, 0);
      const bool closed2 = (tryCombination(S) == i);
      if (closed == closed2) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }

    const int pos = locked[lo];
    locked.erase(locked.begin() + lo);
    S[pos] = (closed ? 1 : 0);
    D[pos] = i;
  }

  answer(S, D);
}