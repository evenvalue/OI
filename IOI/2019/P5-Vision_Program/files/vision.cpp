#include "vision.h"
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

struct foo {
  int black1;
  int black2;
};

int check(const vector<foo> &a, const int k) {
  auto add = [&](deque<int> &d, const int i) {
    d.push_back(i);
  };

  auto rem = [&](deque<int> &d, const int i) {
    assert(d.front() == i);
    d.pop_front();
  };

  auto get_vec = [&](deque<int> &d) -> vector<int> {
    return {d.begin(), d.end()};
  };

  deque<int> one;
  deque<int> two;

  for (int i = 0; i < k; i++) {
    add(one, a[i].black1);
    add(two, a[i].black2);
  }

  vector<int> consider;
  for (int i = k; i < a.size(); i++) {
    add(one, a[i].black1);
    add(two, a[i].black2);

    const int x = add_or(get_vec(one));
    const int y = add_xor(get_vec(one));
    const int z = add_xor(get_vec(two));
    consider.push_back(add_xor({x, y, z}));

    rem(one, a[i - k].black1);
    rem(two, a[i - k].black2);
  }

  assert(not consider.empty());
  return add_or(consider);
}

void construct_network(int H, int W, int K) {
  auto cell = [&](const int row, const int col) {
    assert(0 <= row and row < H);
    assert(0 <= col and col < W);
    return row * W + col;
  };

  vector<foo> left_diagonal(H + W - 1);
  for (int sum = 0; sum < H + W - 1; sum++) {
    vector<int> cells;
    for (int r = 0, c = sum; r < H; r++, c--) {
      if (0 > c or c >= W) continue;
      cells.push_back(cell(r, c));
    }
    left_diagonal[sum].black1 = add_or(cells);
    left_diagonal[sum].black2 = add_xor({
        left_diagonal[sum].black1,
        add_xor(cells)
    });
  }

  vector<foo> right_diagonal(H + W - 1);
  for (int diff = 1 - W; diff < H; diff++) {
    vector<int> cells;
    for (int r = 0, c = r - diff; r < H; r++, c++) {
      if (0 > c or c >= W) continue;
      cells.push_back(cell(r, c));
    }
    right_diagonal[diff + W - 1].black1 = add_or(cells);
    right_diagonal[diff + W - 1].black2 = add_xor({
        right_diagonal[diff + W - 1].black1,
        add_xor(cells)
    });
  }

  const int w = check(left_diagonal, K);
  const int x = check(right_diagonal, K);
  const int y = check(left_diagonal, K - 1);
  const int z = check(right_diagonal, K - 1);

  add_and({
      add_and({w, x}),
      add_not(add_and({y, z}))
  });
}