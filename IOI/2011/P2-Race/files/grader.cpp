#include "race.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500000

static int N, K;
static int H[MAX_N][2];
static int L[MAX_N];

void read_input()
{
  int i;
  scanf("%d %d",&N,&K);
  for(i=0; i<N-1; i++)
    scanf("%d %d %d",&H[i][0],&H[i][1],&L[i]);
}

int main()
{
  int ans;
  read_input();
  ans = best_path(N,K,H,L);
  printf("%d\n", ans);
  return 0;
}
