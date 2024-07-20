#include <bits/stdc++.h>
using namespace std;

using int64 = int64_t;

constexpr int kInf = 1e9 + 10;

template<typename T>
class CoordinateCompression {
  bool sorted = false;
  vector<T> v;

public:
  void add(const T &x) {
    v.push_back(x);
  }

  void compress() {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    sorted = true;
  }

  int get(const int x) {
    if (not sorted) assert(false);
    return distance(v.begin(), lower_bound(v.begin(), v.end(), x));
  }

  int size() {
    return v.size();
  }

  int operator[](const int i) {
    return v[i];
  }
};

struct edge {
  int x, y;
  int a, b;
  int c, d;
  int journey = 0;
};

void solution() {
  int n, m, p, target_time;
  cin >> n >> m >> p >> target_time;

  CoordinateCompression<int> times;
  times.add(0);
  times.add(target_time);

  vector<edge> edges(m);
  for (auto &[x, y, a, b, c, d, _] : edges) {
    cin >> x >> y >> a >> b >> c >> d;
    x--, y--;
    times.add(a);
    times.add(b);
    times.add(c);
    times.add(d);
  }

  times.compress();
  target_time = times.get(target_time);

  vector<vector<int>> leave(times.size());
  vector<vector<int>> reach(times.size());

  for (int i = 0; i < m; i++) {
    auto &[x, y, a, b, c, d, _] = edges[i];
    a = times.get(a);
    b = times.get(b);
    c = times.get(c);
    d = times.get(d);
    leave[a].push_back(i);
    reach[d].push_back(i);
  }

  vector<int> travel(n, -kInf);
  travel[0] = 0;

  for (int time = 0; time <= target_time; time++) {
    for (const int i : reach[time]) {
      auto &[x, y, a, b, c, d, journey] = edges[i];
      travel[y] = max(travel[y], journey);
    }
    for (const int i : leave[time]) {
      auto &[x, y, a, b, c, d, journey] = edges[i];
      journey = travel[x] + (times[c] - times[b]);
    }
  }

  const int ans = times[target_time] - travel[p - 1];
  cout << (ans >= kInf ? -1 : ans) << '\n';
}

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  //cin >> t;
  while (t--) {
    solution();
  }
}
