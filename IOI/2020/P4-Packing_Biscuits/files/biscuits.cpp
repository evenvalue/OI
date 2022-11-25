//#include "biscuits.h"
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
constexpr int kBits = 60;

int64 calc(const vector<int64> &biscuits) {
  int64 ans = 1;
  for (int i = 0; i < biscuits.size(); i++) {
    ans += (1LL << i) * biscuits[i];
  }
  return ans;
}

int64 count_tastiness(int64 x, vector<int64> biscuits) {
  biscuits.push_back(0);

  assert(x == 1);

  vector<vector<int64>> segments = {{}};

  const int n = (int) biscuits.size();
  for (int64 i = 0, carry = 0; i < n; i++) {
    biscuits[i] += carry;
    carry = (biscuits[i] - 1) / 2;
    if (biscuits[i] == 0) {
      segments.emplace_back();
    } else {
      segments.back().push_back(biscuits[i] - carry * 2);
    }
  }

  int64 ans = 1;
  for (const auto &segment : segments) {
    ans *= calc(segment);
  }

  return ans;
}


int main() {
  int q;
  assert(scanf("%d", &q) == 1);
  vector<int> k(q);
  vector<long long> x(q);
  vector<vector<long long>> a(q);
  vector<long long> results(q);
  for (int t = 0; t < q; t++) {
    assert(scanf("%d%lld", &k[t], &x[t]) == 2);
    a[t] = vector<long long>(k[t]);
    for (int i = 0; i < k[t]; i++) {
      assert(scanf("%lld", &a[t][i]) == 1);
    }
  }
  fclose(stdin);

  for (int t = 0; t < q; t++) {
    results[t] = count_tastiness(x[t], a[t]);
  }
  for (int t = 0; t < q; t++) {
    printf("%lld\n", results[t]);
  }
  fclose(stdout);
  return 0;
}

