#include "plants.h"
#include <cassert>
#include <cstdio>
#include <string>
#include <vector>


int main() {
  int n, k, q;
  std::vector<int> r;
  std::vector<int> x;
  std::vector<int> y;
  std::vector<int> answer;

  assert(scanf("%d%d%d", &n, &k, &q) == 3);
  r.resize(n);
  answer.resize(q);
  for (int i = 0; i < n; i++) {
    int value;
    assert(scanf("%d", &value) == 1);
    r[i] = value;
  }
  x.resize(q);
  y.resize(q);
  for (int i = 0; i < q; i++) {
    assert(scanf("%d%d", &x[i], &y[i]) == 2);
  }

  init(k, r);
  for (int i = 0; i < q; i++) {
    answer[i] = compare_plants(x[i], y[i]);
  }

  for (int i = 0; i < q; i++) {
    printf("%d\n", answer[i]);
  }

  return 0;
}
