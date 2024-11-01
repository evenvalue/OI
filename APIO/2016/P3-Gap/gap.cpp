#include "gap.h"
#include <bits/stdc++.h>
using namespace std;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using max_heap = priority_queue<T, vector<T>, less<T>>;

#define int long long

constexpr int kInf = 1e18;
constexpr int kMod = 1e9 + 7;

pair<int, int> ask(const int l, const int r) {
  int mn, mx;
  MinMax(l, r, &mn, &mx);
  return {mn, mx};
}

int subtask1(const int n) {
  vector<int> l, r;

  int a = 0, b = kInf;
  while (l.size() + r.size() < n) {
    const auto [x, y] = ask(a, b);
    l.push_back(x);
    r.push_back(y);
    a = x + 1, b = y - 1;
  }

  for (int i = r.size() - 1; i >= 0; i--) {
    l.push_back(r[i]);
  }

  int ans = 0;
  for (int i = 1; i < l.size(); i++) {
    ans = max(ans, l[i] - l[i - 1]);
  }

  return ans;
}

int subtask2(const int n) {
  auto [l, r] = ask(0, kInf);
  if (r - l + 1 == n) return 1;

  const int each = (r - l - 1) / (n - 1);
  const int extra = (r - l - 1) % (n - 1);

  int last = l;
  vector<int> elems = {l};
  for (int i = 1; i <= n - 1; i++) {
    const int len = each + (i <= extra);
    const int a = last + 1;
    const int b = a + len - 1;
    const auto [x, y] = ask(a, b);
    if (x != -1) elems.push_back(x);
    if (y != -1) elems.push_back(y);
    last = b;
  }

  elems.push_back(r);

  int ans = 0;
  for (int i = 1; i < elems.size(); i++) {
    ans = max(ans, elems[i] - elems[i - 1]);
  }

  return ans;
}

int findGap(int32_t T, int32_t n) {
  if (T == 1) return subtask1(n);
  if (T == 2) return subtask2(n);
  assert(false);
}