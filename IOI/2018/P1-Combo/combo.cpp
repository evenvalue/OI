#include "combo.h"
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag,
                              tree_order_statistics_node_update>;

template <typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
template <typename T> using max_heap = priority_queue<T, vector<T>, less<T>>;

using int64 = long long;
using ld = long double;

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;

string convert(string guess) {
  for (char &c : guess) {
    c = (c == '1' ? 'A' : c);
    c = (c == '2' ? 'B' : c);
    c = (c == '3' ? 'X' : c);
    c = (c == '4' ? 'Y' : c);
  }
  return guess;
}

int call_press(string s) { return press(convert(std::move(s))); }

string guess_sequence(const int N) {
  string s;
  if (const int x = call_press("12"); x == 0) {
    s += (call_press("3") ? '3' : '4');
  } else {
    s += (call_press("1") ? '1' : '2');
  }

  if (N == 1) return convert(s);

  const string choices = [](const char first) {
    string alphas = "1234";
    alphas.erase(alphas.find_first_of(first), 1);
    return alphas;
  }(s[0]);

  for (int i = 1; i < N - 1; i++) {
    string guess;
    for (int j = 0; j < 3; j++) {
      guess += s + choices[0] + choices[j];
    }
    guess += s + choices[1];
    if (const int x = call_press(guess); x == s.size()) {
      s.push_back(choices[2]);
    } else if (x == s.size() + 1) {
      s.push_back(choices[1]);
    } else {
      s.push_back(choices[0]);
    }
  }

  if (call_press(s + choices[0]) == N) {
    s += choices[0];
  } else if (call_press(s + choices[1]) == N) {
    s += choices[1];
  } else {
    s += choices[2];
  }

  return convert(s);
}