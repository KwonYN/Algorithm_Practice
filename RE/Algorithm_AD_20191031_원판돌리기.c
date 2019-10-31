
// 20191031
// [BOJ. 17822] 원판 돌리기
#if 01
#include <stdio.h>
#define MAX	(60)

void Input(void);
void Rotate(int num, int dir, int cnt);
void Operation(void);
void Injub(void);
void Avg_Operation(void);
void Print_Result(void);
void Print_Board(void);

int N, M, T;
int X[MAX];	// 이 값의 배수의 원판을 돌려야 함
int D[MAX];	// 0 : 시계방향		1 : 반시계방향
int K[MAX];	// K칸 만큼 가는 것
int Board[MAX][MAX];
int d_other[4] = { 0, 0, -1, 1 };
int d_same[4] = { -1, 1, 0, 0 };
double avg;

int main(void)
{
	freopen("in.txt", "r", stdin);

	Input();
	Operation();
	Print_Result();

	return 0;
}

void Input(void)
{
	int i, j;

	scanf("%d %d %d", &N, &M, &T);
	for (i = 1; i <= N; i++) for (j = 1; j <= M; j++) scanf("%d", &Board[i][j]);
	for (i = 1; i <= T; i++) scanf("%d %d %d", &X[i], &D[i], &K[i]);
}

void Operation(void)
{
	int i, j, daesang;
	int cnt = 0;

	for (i = 1; i <= T; i++)
	{
		printf("Operation\n");
		printf("[%d]\n", ++cnt);
		Print_Board();
		getch();

		daesang = X[i];	// 몇의 배수인지?
		for (j = daesang; j <= M; j += daesang) Rotate(j, D[i], K[i]);	// 그 배수 번호가 붙은 원판 모두 다 돌려봄
		Injub();
	}
}

void Rotate(int num, int dir, int cnt)
{
	int i, cri;	// cri는 기준이라는 의미!
	int tmp[MAX] = { 0 };

	for (i = 1; i <= M; i++) tmp[i] = Board[num][i];	// 일단 num번째 tmp판의 수를 그대로 복사해줌
	for (i = 1; i <= M; i++) printf("%d ", tmp[i]);
	/*
	if (cnt > M / 2)
	{
		dir = !dir;
		cnt = M - cnt;

		printf("dir = %d <-> !dir = %d\n", dir, !dir);
		printf("cnt = %d <-> !cnt = %d\n", cnt, M - cnt);
	}
	*/
	if (dir)	// 반시계
	{
		printf("반시계\n");
		cri = 1;
		for (i = M + 1 - cnt; i <= M; i++)
		{
			printf("cri = %d\n", cri);
			Board[num][i] = tmp[cri++];
		}
		for (i = 1; i <= M - cnt; i++)
		{
			printf("cri = %d\n", cri);
			Board[num][i] = tmp[cri++];
		}
	}
	else        // 시계
	{
		printf("시계\n");
		cri = M;
		for (i = cnt; i >= 1; i--)
		{
			printf("cri = %d\n", cri);
			Board[num][i] = tmp[cri--];
		}
		for (i = M; i > cnt; i--)
		{
			printf("cri = %d\n", cri);
			Board[num][i] = tmp[cri--];
		}
	}
	printf("Rotate\n");
	Print_Board();
	getch();
}

void Injub(void)
{
	int i, j, d, same_flag = 0, avg_flag = 1;
	int ni, nj;

	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= M; j++)
		{
			if (Board[i][j] == 0) continue;
			same_flag = 0;
			for (d = 0; d < 4; d++)
			{
				ni = i + d_other[d];		nj = j + d_same[d];
				if (ni < 1 || ni > N) continue;
				if (nj < 1) nj = M;
				else if (nj > M) nj = 1;
				printf("ni = %d, nj = %d\n", ni, nj);
				if ( Board[i][j] == Board[ni][nj] )
				{
					printf("Board[i][j] = %d, Board[ni][nj] = %d\n", Board[i][j], Board[ni][nj]);
					Board[ni][nj] = 0;
					same_flag = 1;		avg_flag = 0;
				}
			}
			if (same_flag) Board[i][j] = 0;
		}
	}
	printf("Injub\n");
	Print_Board();
	getch();

	if ( avg_flag ) Avg_Operation();
}

void Avg_Operation(void)
{
	int i, j;
	int sum = 0, cnt = 0;
	double avg;

	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= M; j++)
		{
			if (Board[i][j] == 0) continue;
			sum += Board[i][j];
			cnt++;
		}
	}

	if ( cnt == 0 || sum == 0 ) return;
	avg = (1.0 * sum) / cnt;
	printf("sum = %d\n", sum);
	printf("avg = %lf\n", avg);

	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= M; j++)
		{
			if (Board[i][j] == 0) continue;
			if (Board[i][j] > avg) Board[i][j]--;
			else if (Board[i][j] < avg) Board[i][j]++;
		}
	}

	printf("Avg_Operation\n");
	Print_Board();
	getch();
}

void Print_Result(void)
{
	int i, j, sum = 0;

	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= M; j++)
		{
			sum += Board[i][j];
		}
	}
	printf("Print_Result\n");
	Print_Board();
	getch();

	printf("%d\n", sum);
}

void Print_Board(void)
{
	int i, j;
	printf("Print_Board\n");
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= M; j++)
		{
			printf("%2d ", Board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
#endif
