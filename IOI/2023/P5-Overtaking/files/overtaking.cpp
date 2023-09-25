#include "overtaking.h"
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

struct Bus {
  int index;
  int64 depart; //the time taken by the bus to reach a checkpoint (aka the time it departs).
  int64 time; //the fastest time taken by the bus to travel 1km.

  bool operator<(const Bus &other) const {
    return (depart != other.depart ? depart < other.depart : time < other.time);
  }
};

struct Checkpoint {
  int stop; //distance from the airport
  vector<Bus> order; //order of buses coming into the checkpoint
};

int kLength;
int kBuses;
vector<Bus> buses;
int kCheckpoints;
vector<Checkpoint> checkpoints;
vector<vector<int>> position;
int64 kTime;

void init(int L, int N, vector<int64> T, vector<int> W, int X, int M, vector<int> S) {
  kLength = L;
  kTime = X;

  for (int i = 0, j = 0; i < N; i++) {
    if (W[i] <= X) continue;
    buses.push_back({j,T[i], W[i]});
    j++;
  }

  kBuses = buses.size();
  kCheckpoints = M;

  for (int i = 0; i < kCheckpoints; i++) {
    checkpoints.push_back({S[i]});
  }

  assert(checkpoints[0].stop == 0);

  for (int i = 0; i < kBuses; i++) {
    checkpoints[0].order.push_back(buses[i]);
  }
  sort(checkpoints[0].order.begin(), checkpoints[0].order.end());

  for (int i = 1; i < kCheckpoints; i++) {
    const int64 dist = checkpoints[i].stop - checkpoints[i - 1].stop;
    int64 prev = 0;
    for (const Bus &bus : checkpoints[i - 1].order) {
      const int64 reach = max(prev, dist * bus.time + bus.depart);
      checkpoints[i].order.push_back({bus.index, reach, bus.time});
      prev = reach;
    }
    sort(checkpoints[i].order.begin(), checkpoints[i].order.end());
  }

  position = vector<vector<int>>(kBuses, vector<int>(kCheckpoints));
  for (int i = 0; i < kCheckpoints; i++) {
    const vector<Bus> &order = checkpoints[i].order;
    for (int j = 0; j < kBuses; j++) {
      position[order[j].index][i] = j;
    }
  }
}

int binary_search(const vector<Bus> &order, const int64 time) {
  int lo = 0, hi = kBuses;
  while (lo < hi) {
    const int mid = (lo + hi) / 2;
    if (order[mid].depart >= time) {
      hi = mid;
    } else {
      lo = mid + 1;
    }
  }
  return lo;
}

int64 arrival_time(int64 Y) {
  int64 ans = Y;
  for (int i = 0; i < kCheckpoints - 1; i++) {
    const int dist = checkpoints[i + 1].stop - checkpoints[i].stop;
    const Checkpoint &checkpoint = checkpoints[i];
    int j = binary_search(checkpoint.order, ans);
    ans += dist * kTime;
    if (j != 0) {
      const int k = position[checkpoint.order[j - 1].index][i + 1];
      ans = max(ans, checkpoints[i + 1].order[k].depart);
    }
  }
  return ans;
}