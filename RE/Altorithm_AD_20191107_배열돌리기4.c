// 20191107
// [BOJ. 17406] 배열 돌리기 4
#if 01
#include <stdio.h>
#define MAX	(60)

typedef struct { int r, c, s; }OP;
OP op[10];
OP List[10];

void Input(void);
void DFS(int L);
void Copy_Arr(void);
void Operation(void);
int Get_AValue(void);
void Print_List(int L);

int N, M, K;
int A[MAX][MAX], B[MAX][MAX], chk[MAX];
int op_cnt;
int min_val;

int main(void)
{
	freopen("in.txt", "r", stdin);
	Input();
	DFS(1);
	printf("%d\n", min_val);

	return 0;
}

void Input(void)
{
	int i, j, r, c, s;

	min_val = 987654321;
	op_cnt = 0;
	scanf("%d %d %d", &N, &M, &K);
	for (i = 1; i <= N; i++) for (j = 1; j <= M; j++) scanf("%d", &A[i][j]);
	for (i = 1; i <= K; i++)
	{
		scanf("%d %d %d", &r, &c, &s);
		op[++op_cnt] = (OP){ r, c, s };
	}
}

void DFS(int L)
{
	int i, r;

	if (L > K)
	{
		/*
		Print_List(L);
		getch();
		*/
		Copy_Arr();
		Operation();
		r = Get_AValue();
		if (min_val > r) min_val = r;
		return;
	}

	for (i = 1; i <= K; i++)
	{
		if (chk[i]) continue;
		List[L] = op[i];
		chk[i] = 1;
		DFS(L + 1);
		chk[i] = 0;
		List[L] = (OP){0, 0, 0};
	}
}

void Copy_Arr(void)
{
	int i, j;

	for (i = 1; i <= N; i++) for (j = 1; j <= M; j++) B[i][j] = A[i][j];
}

void Operation(void)
{
	int sy, sx, ey, ex;
	int k, i, j;
	int tmp;

	for (k = 1; k <= K; k++)
	{
		sy = List[k].r - List[k].s;
		sx = List[k].c - List[k].s;
		ey = List[k].r + List[k].s;
		ex = List[k].c + List[k].s;
		for ( ; (sy < ey) && (sx < ex) ; sy++, sx++, ey--, ex--)
		{
			tmp = B[sy][sx];
			for (i = sy; i < ey; i++) B[i][sx] = B[i + 1][sx];
			for (j = sx; j < ex; j++) B[ey][j] = B[ey][j + 1];
			for (i = ey; i > sy; i--) B[i][ex] = B[i - 1][ex];
			for (j = ex; j > sx + 1; j--) B[sy][j] = B[sy][j - 1];
			B[sy][sx + 1] = tmp;
		}
	}
}

int Get_AValue(void)
{
	int i, j;
	int val[MAX] = { 0 };
	int min = 987654321;

	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= M; j++)
		{
			val[i] += B[i][j];
		}
	}

	for (i = 1; i <= N; i++)
	{
		if (min > val[i]) min = val[i];
	}

	return min;
}

void Print_List(int L)
{
	int i;
	printf("Print_List\n");
	for (i = 1; i < L; i++) printf("r = %d, c = %d, s = %d\n", List[i].r, List[i].c, List[i].s);
	printf("\n");
}
#endif
