#include "secret.h"
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

int n;
array<array<int, 1000>, 1000> ans;

void Init(int N, int A[]) {
  n = N;

  function<void(int, int)> dnc = [&](const int l, const int r) {
    if (l == r) {
      ans[l][r] = A[l];
      return;
    }
    const int mid = (l + r) / 2;
    dnc(l, mid);
    dnc(mid + 1, r);
    for (int i = mid - 1; i >= l; i--) {
      ans[i][mid] = Secret(ans[i][i], ans[i + 1][mid]);
    }
    for (int i = mid + 2; i <= r; i++) {
      ans[mid + 1][i] = Secret(ans[mid + 1][i - 1], ans[i][i]);
    }
  };

  dnc(0, n - 1);
}

int Query(int L, int R) {
  if (L == R) return ans[L][R];
  int l = 0, r = n - 1;
  while (l < r) {
    const int mid = (l + r) / 2;
    if (R <= mid) {
      r = mid;
    } else if (mid < L) {
      l = mid + 1;
    } else {
      return Secret(ans[L][mid], ans[mid + 1][R]);
    }
  }
  assert(false);
}
