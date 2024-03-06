#include "molecules.h"
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

struct Elem {
  int i;
  int x;

  bool operator<(const Elem &other) const {
    return x < other.x;
  }
};

vector<int> find_subset(int l, int r, vector<int> w) {
  const int n = w.size();

  vector<Elem> a(n);
  for (int i = 0; i < n; i++) {
    a[i].i = i;
    a[i].x = w[i];
  }

  sort(a.begin(), a.end());

  if (accumulate(w.begin(), w.end(), 0LL) < l) return {};
  if (a[0].x > r) return {};

  int64 sum = 0;
  vector<int> ans;

  for (const auto [i, x] : a) {
    sum += x;
    ans.push_back(i);
    if (l <= sum and sum <= r) goto FOUND;
    if (l < sum) {
      sum -= x;
      ans.pop_back();
      break;
    }
  }

  for (int i = ans.size() - 1, j = n - 1; i >= 0; i--, j--) {
    const int diff = a[j].x - a[i].x;
    sum += diff;
    ans[i] = a[j].i;
    if (l <= sum and sum <= r) goto FOUND;
  }

  return {};

FOUND:
  return ans;
}
