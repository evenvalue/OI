#include "doll.h"
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

vector<int> C;
vector<int> X, Y;

int add_switch(const int x = kInf, const int y = kInf) {
  X.push_back(x);
  Y.push_back(y);
  return -((int)X.size());
}

int calc_elements(const int n) {
  const int h = 32 - __builtin_clz(n) - (__builtin_popcount(n) == 1);
  return (1 << h);
}

void create_circuit(int m, std::vector<int> A) {
  C.resize(m + 1, -1);

  A.push_back(0);
  const int n = A.size();
  const int elems = calc_elements(n);
  const int unused = elems - n;

  vector<pair<int, int>> trigger_places(elems, {-1, -1});

  function<void(int, int, int, int, int)> dfs = [&](const int x, const int l, const int r, const int depth, int path) {
    const int mid = (l + r) / 2;
    //left child
    if (mid < unused) {
      X[x] = -1;
    } else if (l == mid) {
      X[x] = path;
      trigger_places[path] = {x, 0};
    } else {
      X[x] = add_switch();
      dfs(-X[x] - 1, l, mid, depth + 1, path);
    }
    //right child
    path += (1 << depth);
    if (mid + 1 == r) {
      Y[x] = path;
      trigger_places[path] = {x, 1};
    } else {
      Y[x] = add_switch();
      dfs(-Y[x] - 1, mid + 1, r, depth + 1, path);
    }
  };

  add_switch();
  dfs(0, 0, elems - 1, 0, 0);

  for (int i = 0, j = 0; i < elems; i++) {
    if (trigger_places[i] == make_pair(-1, -1)) continue;
    const auto [s, dir] = trigger_places[i];
    (dir == 0 ? X[s] : Y[s]) = A[j];
    j++;
  }

  answer(C, X, Y);
}