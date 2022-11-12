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

  point prev = anti_clockwise_boxes[0][0];
  vector<point> ans = {intersect(prev, point(0, 0))};
  for (int i = 0; i < boxes; i++) {
    auto &ab = anti_clockwise_boxes[i];
    auto &cb = clockwise_boxes[i];

    const point p = intersect(prev, ab[0]);
    auto &b = (ab[0].x <= p.x ? ab : cb);

    ans.push_back(intersect(prev, b[0]));
    ans.push_back(intersect(b[1], ans.back()));
    ans.push_back(intersect(ans.back(), b[2]));
    ans.push_back(intersect(b[3], ans.back()));
    prev = b[3];
  }

  ans.push_back(prev);

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