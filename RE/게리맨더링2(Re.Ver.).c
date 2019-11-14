// 20191114
// [BOJ. 17779] 게리맨더링2
#if 01
#include <stdio.h>

typedef struct { int y, x; }NODE;
NODE tips[6];

void Input(void);
void Operation(void);
void DFS(int L, int y, int x);
int Get_Diff(void);

void Print_visit(void);
void Print_A(void);

int N;
int A[25][25];
int dy[5] = { 0, -1, 1, 1, -1 };
int dx[5] = { 0, 1, 1, -1, -1 };
int visit[25][25];
int sy, sx;
int total;
int min_diff;

int main(void)
{
	freopen("in.txt", "r", stdin);
	Input();
	Operation();
	//Print_A();
	printf("%d\n", min_diff);

	return 0;
}

void Input(void)
{
	int i, j;

	total = 0;
	min_diff = 987654321;
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			visit[i][j] = 0;
			A[i][j] = 0;
			scanf("%d", &A[i][j]);
			total += A[i][j];
		}
	}
}

void SetData()

void Operation(void)
{
	int i, j;

	for (i = 2; i < N; i++)
	{
		for (j = 1; j <= N - 2; j++)
		{
			sy = i;		sx = j;
			visit[i][j] = 1;
			tips[1] = (NODE){ i, j };
			DFS(1, i, j);
			tips[1] = (NODE){ 0, 0 };
			visit[i][j] = 0;
		}
	}
}

void DFS(int L, int y, int x)
{
	int r;
	if (L >= 5) return;
	if (L == 4)
	{
		if ((sy + 1 == y) && (sx + 1 == x))
		{
			/*
			Print_visit();
			getch();
			*/
			r = Get_Diff();
			if (min_diff > r) min_diff = r;
			return;
		}
	}

	y += dy[L];		x += dx[L];
	if (y < 1 || y > N || x < 1 || x > N || visit[y][x]) return;
	visit[y][x] = 1;
	DFS(L, y, x);

	tips[L + 1] = (NODE) { y, x };
	DFS(L + 1, y, x);
	tips[L + 1] = (NODE) { 0, 0 };
	visit[y][x] = 0;
}

int Get_Diff(void)
{
	int i, j, tmp;
	int cnt[7] = { 0 };

	for (i = 1; i < tips[1].y; i++)
	{
		for (j = 1; j <= tips[2].x; j++)
		{
			if (visit[i][j]) break;
			cnt[1] += A[i][j];
		}
	}

	for (i = 1; i <= tips[3].y; i++)
	{
		for (j = N; j > tips[2].x; j--)
		{
			if (visit[i][j]) break;
			cnt[2] += A[i][j];
		}
	}

	for (i = N; i >= tips[1].y; i--)
	{
		for (j = 1; j < tips[4].x; j++)
		{
			if (visit[i][j]) break;
			cnt[3] += A[i][j];
		}
	}

	for (i = N; i > tips[3].y; i--)
	{
		for (j = N; j >= tips[4].x; j--)
		{
			if (visit[i][j]) break;
			cnt[4] += A[i][j];
		}
	}

	cnt[5] = total - (cnt[1] + cnt[2] + cnt[3] + cnt[4]);

	for (i = 1; i < 5; i++)
	{
		for (j = i + 1; j <= 5; j++)
		{
			if (cnt[i] > cnt[j])	// 오름차순
			{
				tmp = cnt[i];
				cnt[i] = cnt[j];
				cnt[j] = tmp;
			}
		}
	}

	return (cnt[5] - cnt[1]);
}

void Print_visit(void)
{
	int i, j;
	printf("Print_visit\n");
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			printf("%d ", visit[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void Print_A(void)
{
	int i, j;
	printf("Print_A\n");
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
#endif
