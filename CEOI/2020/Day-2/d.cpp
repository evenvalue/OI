#include <bits/stdc++.h>
using namespace std;

#define int long long

#ifdef evenvalue
  #include "debug.h"
#else
  #define debug(...)
#endif

using int64 = long long;
using ld = long double;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using max_heap = priority_queue<T, vector<T>, less<T>>;

namespace read {
int Int() {
  int x;
  cin >> x;
  return x;
}
int64 Int64() {
  int64 x;
  cin >> x;
  return x;
}
char Char() {
  char c;
  cin >> c;
  return c;
}
string String() {
  string s;
  cin >> s;
  return s;
}
double Double() {
  return stod(String());
}
ld LongDouble() {
  return stold(String());
}
template<typename T1, typename T2>
pair<T1, T2> Pair() {
  pair<T1, T2> p;
  cin >> p.first >> p.second;
  return p;
}
template<typename T>
vector<T> Vec(const int n) {
  vector<T> v(n);
  for (T &x : v) {
    cin >> x;
  }
  return v;
}
template<typename T>
vector<vector<T>> VecVec(const int n, const int m) {
  vector<vector<T>> v(n);
  for (vector<T> &vec : v) {
    vec = Vec<T>(m);
  }
  return v;
}
}//namespace read

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1000000000;
constexpr int kMod = 1e9 + 7;
constexpr int kMaxN = 2e5 + 10;
constexpr int kBlockSize = 50;

struct edge {
  int x;
  int y;
};

struct shaman {
  vector<pair<int, int>> curse;
  vector<pair<int, int>> time;
  vector<vector<int>> nbr;
};

inline void solution() {
  const int n = read::Int();
  const int d = read::Int();
  const int u = read::Int();
  int q = read::Int();

  vector<int> height = read::Vec<int>(n);

  vector<shaman> shamans(n);
  for (int time = 1; time <= u; time++) {
    edge cur{};
    cur.x = read::Int();
    cur.y = read::Int();

    shamans[cur.x].curse.emplace_back(cur.y, time);
    shamans[cur.y].curse.emplace_back(cur.x, time);
  }

  for (shaman &man : shamans) {
    man.time.emplace_back(0, 0);
    man.nbr.emplace_back();

    vector<int> nbr;
    for (int i = 0; i < man.curse.size(); ) {
      int time = -1;
      int j = i;
      for (; j < min((int)man.curse.size(), i + kBlockSize); j++) {
        const auto [x, t] = man.curse[j];
        if (const auto it = find(nbr.begin(), nbr.end(), x); it != nbr.end()) {
          nbr.erase(it);
        } else {
          nbr.push_back(x);
        }
        time = t;
      }
      i = j;
      man.time.emplace_back(time, i);
      man.nbr.push_back(nbr);
    }
  }

  auto get_nbr = [&](const int x, const int t) {
    int i = shamans[x].time.size() - 1;
    for (; i >= 0; i--) {
      if (shamans[x].time[i].first <= t) {
        break;
      }
    }
    vector<int> nbr = shamans[x].nbr[i];
    for (int j = shamans[x].time[i].second; j < shamans[x].curse.size(); j++) {
      if (shamans[x].curse[j].second > t) break;
      const auto [y, _] = shamans[x].curse[j];
      if (const auto it = find(nbr.begin(), nbr.end(), y); it != nbr.end()) {
        nbr.erase(it);
      } else {
        nbr.push_back(y);
      }
    }

    return nbr;
  };

  auto cmp = [&](const int i, const int j) {
    return height[i] < height[j];
  };

  auto calc_score = [&](vector<int> &v1, vector<int> &v2) {
    sort(v1.begin(), v1.end(), cmp);
    sort(v2.begin(), v2.end(), cmp);

    int ans = kInf64;
    for (int i = 0, j = 0; i < v1.size() and j < v2.size(); ) {
      ans = min(ans, abs(height[v1[i]] - height[v2[j]]));
      if (height[v1[i]] <= height[v2[j]]) {
        i++;
      } else {
        j++;
      }
    }

    return ans;
  };

  while (q--) {
    const int x = read::Int();
    const int y = read::Int();
    const int t = read::Int();
    auto nbr_x = get_nbr(x, t);
    auto nbr_y = get_nbr(y, t);


    cout << calc_score(nbr_x, nbr_y) << endl;
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);

  cout << fixed << setprecision(10);

  int testcases = 1;
  //cin >> testcases;
  while (testcases--) {
    solution();
  }
}