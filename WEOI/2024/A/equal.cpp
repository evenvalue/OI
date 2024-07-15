#include "equal.h"
#include <bits/stdc++.h>
using namespace std;

void make_all_equal(int N, int Q_add, int Q_compare) {
  vector<vector<int>> idx(N);
  for (int i = 0; i < N; i++) {
    idx[i].push_back(i);
  }

  int lim = 19;

  vector<int> cur(N);
  iota(cur.begin(), cur.end(), 0);
  while (cur.size() != 1) {
    vector<int> sub;
    for (int i = 0; i < cur.size(); i += 2) {
      sub.insert(sub.end(), idx[cur[i]].begin(), idx[cur[i]].end());
    }
    for (int bit = lim; bit >= 0; bit--) {
      add(sub, (1 << bit));
    }
    vector<int> to_add;
    vector<int> tmp;
    for (int i = 0; i < cur.size(); i += 2) {
      if (not compare(idx[cur[i]][0], idx[cur[i + 1]][0])) {
        to_add.insert(to_add.end(), idx[cur[i]].begin(), idx[cur[i]].end());
      }
      tmp.push_back(cur[i]);
      idx[cur[i]].insert(idx[cur[i]].end(), idx[cur[i + 1]].begin(), idx[cur[i + 1]].end());
    }
    add(to_add, 1);
    swap(tmp, cur);
    lim++;
  }
}
