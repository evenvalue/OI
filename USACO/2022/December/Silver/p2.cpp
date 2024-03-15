#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

namespace read {
int Int() {
  int x;
  cin >> x;
  return x;
}
template<typename T>
vector<T> Vec(const int n) {
  vector<T> v(n);
  for (T &x : v) {
    cin >> x;
  }
  return v;
}
}//namespace read

constexpr int kMaxA = 5e6 + 5;
constexpr int kInf = 1e9 + 10;

inline void solution(const vector<int> &rounds) {
  const int n = read::Int();
  vector<int> a = read::Vec<int>(n);

  int mn = kInf;
  for (int &x : a) {
    if (abs(rounds[x]) < abs(mn)) {
      mn = rounds[x];
    }
  }

  cout << "Farmer " << (mn > 0 ? "John" : "Nhoj") << '\n';
}

vector<int> sieve(const int n) {
  vector<bool> is_prime(n + 1, true);
  is_prime[0] = is_prime[1] = false;
  vector<int> primes;
  for (int i = 2; i <= n; i++) {
    if (not is_prime[i]) continue;
    for (int64 j = i * 1LL * i; j <= n; j += i) {
      is_prime[j] = false;
    }
    primes.push_back(i);
  }
  return primes;
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<int> primes = sieve(kMaxA);

  vector<int> one_mod4;
  vector<int> three_mod4;

  for (const int p : primes) {
    if (p % 4 == 1) {
      one_mod4.push_back(p);
    } else if (p % 4 == 3) {
      three_mod4.push_back(p);
    }
  }

  vector<int> rounds(kMaxA, -1);
  rounds[0] = -1;
  rounds[1] = 1;
  rounds[2] = 1;
  rounds[3] = 1;
  rounds[4] = -2;

  int last1 = 1, last3 = 3;
  for (int i = 5, j = 0, k = 1; i < kMaxA; i++) {
    if (j != one_mod4.size() and i == one_mod4[j]) {
      last1 = i;
      j++;
    }
    if (k != three_mod4.size() and i == three_mod4[k]) {
      last3 = i;
      k++;
    }
    if (i % 2 == 0) {
      if (i % 4 == 0) {
        rounds[i] = rounds[i - 4] - 1;
      } else {
        rounds[i] = -rounds[i - 2];
      }
    } else {
      if (i % 4 == 1) {
        rounds[i] = -rounds[i - last1];
      } else {
        rounds[i] = -rounds[i - last3];
      }
    }
  }

  int t = read::Int();
  while (t--) {
    solution(rounds);
  }
}