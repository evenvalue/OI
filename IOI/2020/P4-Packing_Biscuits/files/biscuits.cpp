#include "biscuits.h"
#include <bits/stdc++.h>
using namespace std;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using max_heap = priority_queue<T, vector<T>, less<T>>;

using int64 = long long;
using ld = long double;

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 2e18 + 10;
constexpr int kMod = 1e9 + 7;
constexpr int kBits = 61;

void merge_biscuits(const int64 x, vector<int64> &biscuits) {
  while (biscuits.size() <= kBits) biscuits.push_back(0);
  for (int i = 0; i < kBits; i++) {
    const int64 carry = max(0LL, biscuits[i] - x) / 2;
    biscuits[i] -= 2 * carry;
    biscuits[i + 1] += carry;
  }
}

int64 count_tastiness(int64 x, vector<int64> biscuits) {
  merge_biscuits(x, biscuits);

  vector<int64> s(kBits, biscuits[0]);
  for (int i = 1; i < kBits; i++) {
    s[i] = s[i - 1] + (1LL << i) * biscuits[i];
  }

  map<int64, int64> memo;
  memo[1] = 1;
  function<int64(int64)> dp = [&](const int64 n)-> int64 {
    if (n <= 0) return 0;
    if (memo[n] != 0) return memo[n];
    const int i = (int)ceil(log2(n) - 1);
    const int64 c = (1LL << i);
    memo[n] = dp(c) + dp(min(n, s[i] / x + 1) - c);
    return memo[n];
  };

  return dp(kInf64);
}
