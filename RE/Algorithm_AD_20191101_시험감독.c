// 20191101
// [BOJ. 13458] 시험 감독
#if 0
#include <stdio.h>
#define MAX	(1000100)

void Input(void);
void Operation(void);

int N, B, C;
int A[MAX];
long long int manager;

int main(void)
{
	freopen("in.txt", "r", stdin);

	Input();
	Operation();
	printf("%lld\n", manager);

	return 0;
}

void Input(void)
{
	int i;

	scanf("%d", &N);
	for (i = 1; i <= N; i++) scanf("%d", &A[i]);
	scanf("%d %d", &B, &C);
}

void Operation(void)
{
	int i, j;

	manager = N;
	for (i = 1; i <= N; i++)
	{
		A[i] -= B;
		if (A[i] <= 0) continue;
		if ( A[i] % C != 0 ) manager++;
		manager += (A[i] / C);
	}
}
#endif
