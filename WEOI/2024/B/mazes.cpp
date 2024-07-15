#include <vector>

using namespace std;

vector<vector<char>> solve(long long K) {
  const int n = 200;

  vector<vector<char>> ans(n, vector<char>(n, '#'));
  for (int bit = 0; bit < 60; bit++) {
    const int i = 3 * bit;
    const int j = bit;
    ans[i][j] = '.';
    for (const int d : {1, 2, 3}) {
      ans[i + d][j] = '.';
    }
    ans[i + 2][j + 1] = '.';
  }

  for (int i = 0; i < n; i++) {
    ans[i][n - 1] = '.';
  }

  for (int bit = 0; bit < 60; bit++) {
    if ((K & (1LL << bit)) == 0) continue;
    const int i = 3 * bit;
    for (int j = bit; j < n; j++) {
      ans[i][j] = '.';
    }
  }

  return ans;
}
