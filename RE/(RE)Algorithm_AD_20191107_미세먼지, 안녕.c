// 20191107
// [BOJ. 17144] 미세먼지야, 안녕!
#if 01
#include <stdio.h>
#define MAX	(60)

void Input(void);
void Operation(void);
void Clear_Air(void);
void Init(void);
int Get_Dust(void);
void Print_A(void);
void Print_B(void);

int R, C, T;
int A[MAX][MAX], B[MAX][MAX];
int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };
int ac[5];
int ac_cnt;

int main(void)
{
	freopen("in.txt", "r", stdin);
	Input();
	Operation();
	printf("%d\n", Get_Dust());

	return 0;
}

void Input(void)
{
	int i, j;

	ac_cnt = 0;
	scanf("%d %d %d", &R, &C, &T);
	for (i = 1; i <= R; i++)
	{
		for (j = 1; j <= C; j++)
		{
			scanf("%d", &A[i][j]);
			if (A[i][j] == -1) ac[++ac_cnt] = i;
		}
	}
}

void Operation(void)
{
	int r, c, d, t, A_tmp;
	int cnt, nr, nc;

	for (t = 1; t <= T; t++)
	{
		/*
		Print_A();
		getch();
		*/
		for (r = 1; r <= R; r++)
		{
			for (c = 1; c <= C; c++)
			{
				if (A[r][c] <= 0) continue;
				A_tmp = A[r][c];
				cnt = 0;
				for (d = 0; d < 4; d++)
				{
					nr = r + dr[d];		nc = c + dc[d];
					if (nr < 1 || nr > R || nc < 1 || nc > C || A[nr][nc] == -1) continue;
					B[nr][nc] += (A_tmp / 5);
					cnt++;
				}
				B[r][c] += A_tmp - (A_tmp / 5) * cnt;
			}
		}
		Clear_Air();
		Init();
	}
}

void Clear_Air(void)
{
	int i, j;
	int y1 = ac[1], y2 = ac[2];
	/*
	Print_B();
	getch();
	*/
	// 이 부분에서 부등호 주의..!!
	for (i = y1 - 1; i > 1; i--) B[i][1] = B[i - 1][1];
	for (j = 1; j < C; j++) B[1][j] = B[1][j+1];
	for (i = 1; i < y1; i++) B[i][C] = B[i + 1][C];
	for (j = C; j > 2; j--) B[y1][j] = B[y1][j - 1];
	B[y1][2] = 0;

	for (i = y2 + 1; i < R; i++) B[i][1] = B[i + 1][1];
	for (j = 1; j < C; j++) B[R][j] = B[R][j + 1];
	for (i = R; i > y2; i--) B[i][C] = B[i - 1][C];
	for (j = C; j > 2; j--) B[y2][j] = B[y2][j - 1];
	B[y2][2] = 0;
}

void Init(void)
{
	int i, j;

	for (i = 1; i <= R; i++)
	{
		for (j = 1; j <= C; j++)
		{
			if (A[i][j] == -1) continue;
			A[i][j] = B[i][j];
			B[i][j] = 0;
		}
	}
}

int Get_Dust(void)
{
	int i, j, dust = 0;

	for (i = 1; i <= R; i++)
	{
		for (j = 1; j <= C; j++)
		{
			if (A[i][j] <= 0) continue;
			dust += A[i][j];
		}
	}

	return dust;
}

void Print_A(void)
{
	int i, j;
	printf("[후] Print_A\n");
	for (i = 1; i <= R; i++)
	{
		for (j = 1; j <= C; j++)
		{
			printf("%2d ", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void Print_B(void)
{
	int i, j;
	printf("[전]Print_B\n");
	for (i = 1; i <= R; i++)
	{
		for (j = 1; j <= C; j++)
		{
			printf("%2d ", B[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
#endif
