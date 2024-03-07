#include "game.h"
#include <bits/stdc++.h>
using namespace std;

static char ans[1500 * 1500];

int main() {
  int n, u, v, i;
  cin >> n;
  initialize(n);
  for (i = 0; i < n * (n - 1) / 2; i++) {
    cin >> u >> v;
    if (hasEdge(u, v)) ans[i] = '1';
    else
      ans[i] = '0';
  }
  puts(ans);
  return 0;
}
