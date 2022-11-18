#include "tickets.h"
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

struct ticket {
  int value;
  int color;
  int group;

  bool operator<(const ticket &other) const {
    return (value == other.value ? group < other.group : value < other.value);
  }

  bool operator>(const ticket &other) const {
    return (value == other.value ? group > other.group : value > other.value);
  }
};

struct ticket_pair {
  ticket one;
  ticket two;
  int priority;

  int value() const {
    return one.value + two.value;
  }

  bool operator<(const ticket_pair &other) const {
    return (value() == other.value() ? priority < other.priority : value() < other.value());
  }
};

int64 find_maximum(const int k, const vector<vector<int>> X) {
  const int n = (int) X.size();   //number of colours
  const int m = (int) X[0].size();//number of tickets
  const int choose = n * k;       //number of tickets to choose

  vector<vector<ticket>> tickets(n, vector<ticket>(m));
  for (int color = 0; color < n; color++) {
    for (int group = 0; group < m; group++) {
      tickets[color][group].value = X[color][group];
      tickets[color][group].color = color;
      tickets[color][group].group = group;
    }
  }

  vector<ticket_pair> pq;
  for (auto color : tickets) {
    sort(color.begin(), color.end());
    for (int i = 0; i < k; i++) {
      const int j = m - k + i;
      pq.push_back({color[i], color[j], i});
    }
  }

  sort(pq.begin(), pq.end());

  vector<vector<ticket>> positive(n);
  while (pq.size() > choose / 2) {
    const ticket t = pq.back().two;
    positive[t.color].push_back(t);
    pq.pop_back();
  }

  vector<vector<ticket>> negative(n);
  while (not pq.empty()) {
    const ticket t = pq.back().one;
    negative[t.color].push_back(t);
    pq.pop_back();
  }

  int64 score = 0;
  vector<vector<int>> s(n, vector<int>(m, -1));

  vector<int> color(n);
  iota(color.begin(), color.end(), 0);

  auto delta = [&](const int i) {
    return (int)positive[i].size() - (int)negative[i].size();
  };

  for (int round = 0; round < k; round++) {
    sort(color.begin(), color.end(), [&](const int i, const int j) {
      return delta(i) > delta(j);
    });

    for (int i = 0; i < n; i++) {
      auto &v = (i < n / 2 ? positive : negative);
      const ticket t = v[color[i]].back();
      s[t.color][t.group] = round;
      score += (i < n / 2 ? t.value : -t.value);
      v[color[i]].pop_back();
    }
  }

  allocate_tickets(s);
  return score;
}
