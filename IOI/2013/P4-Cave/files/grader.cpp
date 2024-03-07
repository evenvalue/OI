#include "cave.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5000
#define MAX_CALLS 70000

static int N;
static int realS[MAX_N];
static int realD[MAX_N];
static int inv[MAX_N];
static int num_calls;

void answer(int S[], int D[]) {
  int i;
  for (i = 0; i < N; ++i)
    if (S[i] != realS[i] || D[i] != realD[i]) {
      printf("INCORRECT\nWrong answer:");
      if (S[i] != realS[i])
        printf("S[%d] != realS[%d]", i, i);
      else
        printf("D[%d] != realD[%d]", i, i);
      exit(0);
    }

  printf("CORRECT\n");
  exit(0);
}

int tryCombination(int S[]) {
  int i;

  if (num_calls >= MAX_CALLS) {
    printf("INCORRECT\nToo many calls to tryCombination().\n");
    exit(0);
  }
  ++num_calls;

  for (i = 0; i < N; ++i)
    if (S[inv[i]] != realS[inv[i]])
      return i;
  return -1;
}

int init() {
  int i;

  assert(scanf("%d", &N) == 1);

  for (i = 0; i < N; ++i) {
    assert(scanf("%d", &realS[i]) == 1);
  }
  for (i = 0; i < N; ++i) {
    assert(scanf("%d", &realD[i]) == 1);
    inv[realD[i]] = i;
  }

  num_calls = 0;
  return N;
}

int main() {
  int N;
  N = init();
  exploreCave(N);
  printf("INCORRECT\nYour solution did not call answer().\n");
  return 0;
}
