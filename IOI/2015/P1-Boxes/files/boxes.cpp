#include "boxes.h"
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

long long delivery(int N, int K, int L, int p[]) {
  vector<int> pos(N + 1);
  for (int i = 1; i <= N; i++) {
    pos[i] = p[i - 1];
  }

  sort(pos.begin(), pos.end());

  vector<int64> l(N + 1);
  vector<int64> r(N + 2);
  for (int i = 1; i <= N; i++) {
    l[i] = l[max(0, i - K)] + 2 * pos[i];
  }
  for (int i = N; i > 0; i--) {
    r[i] = r[min(N + 1, i + K)] + 2 * (L - pos[i]);
  }

  int64 ans = min(r[1], l[N]);
  for (int i = 1; i < N; i++) {
    ans = min(ans, l[i] + r[i + 1]);
  }

  for (int i = 1; i <= N; i++) {
    const int64 lt = l[i - 1];
    const int64 rt = (i + K <= N ? r[i + K] : 0);
    ans = min(ans, lt + rt + L);
  }

  return ans;
}