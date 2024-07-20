#include "boxes.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, K, L, i;
    cin >> N >> K >> L;

    int *p = (int*)malloc(sizeof(int) * (unsigned int)N);

    for (i = 0; i < N; i++) {
      cin >> p[i];
    }
    
    cout << delivery(N, K, L, p) << '\n';
    return 0;
}
