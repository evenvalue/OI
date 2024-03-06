#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "robots.h"

#define MAX_A 50000
#define MAX_B 50000
#define MAX_T 500000

static int X[MAX_A];
static int Y[MAX_B];
static int W[MAX_T];
static int S[MAX_T];

int main() {
    int A, B, T, i;

	assert(scanf("%d", &A) == 1);
	assert(scanf("%d", &B) == 1);
	assert(scanf("%d", &T) == 1);

	for (i = 0; i < A; i++)
		assert(scanf("%d", &X[i]) == 1);
	for (i = 0; i < B; i++)
        assert(scanf("%d", &Y[i]) == 1);
	for (i = 0; i < T; i++)
        assert(scanf("%d%d", &W[i], &S[i]) == 2);

	int answer = putaway(A, B, T, X, Y, W, S);

	printf("%d\n", answer);

	return 0;
}
