#include <bits/stdc++.h>
using namespace std;

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
}//namespace read

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;

struct point {
  int x, y;

  point() = default;
  point(const int x, const int y) : x(x), y(y) {}

  bool operator<(const point other) const {
    return y < other.y;
  }

  bool operator==(const point &other) const {
    return (x == other.x) and (y == other.y);
  }
};

point intersect(const point p1, const point p2) {
  return {p1.x, p2.y};
}

struct box {
  array<point, 4> b;

  point &operator[](const int x) {
    assert(0 <= x and x < 4);
    return b[x];
  }
};

inline void solution() {
  const int n = read::Int();

  vector<point> points(n);
  for (point &p : points) {
    p.x = read::Int();
    p.y = read::Int();
  }

  auto CmpTop = [&](const point &p1, const point &p2) -> bool {
    return p1.y > p2.y;
  };

  auto CmpLeft = [&](const point &p1, const point &p2) -> bool {
    return p1.x < p2.x;
  };

  auto CmpDown = [&](const point &p1, const point &p2) -> bool {
    return p1.y < p2.y;
  };

  auto CmpRight = [&](const point &p1, const point &p2) -> bool {
    return p1.x > p2.x;
  };

  set<point, decltype(CmpTop)> top(points.begin(), points.end(), CmpTop);
  set<point, decltype(CmpLeft)> left(points.begin(), points.end(), CmpLeft);
  set<point, decltype(CmpDown)> down(points.begin(), points.end(), CmpDown);
  set<point, decltype(CmpRight)> right(points.begin(), points.end(), CmpRight);

  auto check_empty = [&]() {
    return top.empty() or
           left.empty() or
           down.empty() or
           right.empty();
  };

  auto in_range = [&](const point p, const point tl, const point dr) {
    return (tl.x < p.x and p.x < dr.x) and (dr.y < p.y and p.y < tl.y);
  };

  vector<box> anti_clockwise_boxes;
  vector<point> left_chain;
  vector<point> right_chain;
  for (int t = kInf, l = -1, d = -1, r = kInf; not check_empty();) {
    const point tl(l, t);
    const point dr(r, d);

    while (not check_empty() and not in_range(*top.begin(), tl, dr)) {
      top.erase(top.begin());
    }
    while (not check_empty() and not in_range(*left.begin(), tl, dr)) {
      left.erase(left.begin());
    }
    while (not check_empty() and not in_range(*down.begin(), tl, dr)) {
      down.erase(down.begin());
    }
    while (not check_empty() and not in_range(*right.begin(), tl, dr)) {
      right.erase(right.begin());
    }

    if (check_empty()) break;

    box b{};
    b[0] = *top.begin();
    b[1] = *left.begin();
    b[2] = *down.begin();
    b[3] = *right.begin();

    if (b[0] == b[1]) {
      right_chain.push_back(b[0]);
      top.erase(top.begin());
      left.erase(left.begin());
      continue;
    }
    if (b[0] == b[3]) {
      left_chain.push_back(b[0]);
      top.erase(top.begin());
      right.erase(right.begin());
      continue;
    }
    if (b[2] == b[1]) {
      left_chain.push_back(b[2]);
      down.erase(down.begin());
      left.erase(left.begin());
      continue;
    }
    if (b[2] == b[3]) {
      right_chain.push_back(b[2]);
      down.erase(down.begin());
      right.erase(right.begin());
      continue;
    }

    t = b[0].y;
    l = b[1].x;
    d = b[2].y;
    r = b[3].x;

    top.erase(top.begin());
    left.erase(left.begin());
    down.erase(down.begin());
    right.erase(right.begin());

    anti_clockwise_boxes.push_back(b);
  }

  vector<box> clockwise_boxes;
  for (const box b : anti_clockwise_boxes) {
    clockwise_boxes.push_back(b);
    auto &b2 = clockwise_boxes.back();
    swap(b2[1], b2[3]);
  }

  reverse(anti_clockwise_boxes.begin(), anti_clockwise_boxes.end());
  reverse(clockwise_boxes.begin(), clockwise_boxes.end());

  const int boxes = anti_clockwise_boxes.size();

  left_chain.emplace_back(0, 0);
  sort(left_chain.begin(), left_chain.end());
  sort(right_chain.begin(), right_chain.end());

  vector<point> ans = {left_chain[0]};
  for (int i = 0; i < left_chain.size() - 1; i++) {
    point p = ((i % 2) ? intersect(left_chain[i], left_chain[i + 1]) : intersect(left_chain[i + 1], left_chain[i]));
    ans.push_back(p);
  }
  ans.push_back(left_chain.back());

  if (not right_chain.empty()) {
    ans.push_back(intersect(ans.back(), right_chain[0]));
    ans.push_back(right_chain[0]);
    for (int i = 0; i < right_chain.size() - 1; i++) {
      point p = ((i % 2) ? intersect(right_chain[i], right_chain[i + 1]) : intersect(right_chain[i + 1], right_chain[i]));
      ans.push_back(p);
    }
    ans.push_back(right_chain.back());
  }

  point prev = ans.back();
  vector<point> spiral = {intersect(prev, point(0, 0))};
  for (int i = 0; i < boxes; i++) {
    auto &ab = anti_clockwise_boxes[i];
    auto &cb = clockwise_boxes[i];

    const point p = intersect(prev, ab[0]);
    auto &b = (ab[0].x <= p.x ? ab : cb);

    spiral.push_back(intersect(prev, b[0]));
    spiral.push_back(intersect(b[1], spiral.back()));
    spiral.push_back(intersect(spiral.back(), b[2]));
    spiral.push_back(intersect(b[3], spiral.back()));
    prev = b[3];
  }

  spiral.push_back(prev);

  ans.insert(ans.end(), spiral.begin(), spiral.end());

  while (*ans.begin() == point(0, 0)) {
    ans.erase(ans.begin());
  }

  cout << ans.size() << '\n';
  for (const point p : ans) {
    cout << p.x << " " << p.y << '\n';
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cout << fixed << setprecision(10);

  int testcases = 1;
  //cin >> testcases;
  while (testcases--) {
    solution();
  }
}