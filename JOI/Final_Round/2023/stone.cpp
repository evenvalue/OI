#include <bits/stdc++.h>
using namespace std;

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

int main() {
  int n;
  cin >> n;

  CoordinateCompression<int> cc;
  vector<int> a(n);

  for (int &x : a) {
    cin >> x;
    cc.add(x);
  }

  cc.compress();
  vector<int> last(n, -1);

  vector<pair<int, int>> ans;
  for (int x : a) {
    x = cc.get(x);
    if (last[x] == -1) {
      last[x] = ans.size();
      ans.emplace_back(x, 1);
      continue;
    }
    int sum = 1;
    while (ans.size() != last[x]) {
      sum += ans.back().second;
      if (ans.back().first != x) last[ans.back().first] = -1;
      ans.pop_back();
    }
    last[x] = ans.size();
    ans.emplace_back(x, sum);
  }

  for (const auto &[x, sum] : ans) {
    for (int i = 0; i < sum; i++) {
      cout << cc[x] << ' ';
    }
  }
  cout << '\n';
}
