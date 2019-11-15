#pragma warning(disable : 4996)

#if 01
#include <stdio.h>
#define MAX	(550)

void Input(void);
void Operation(void);
int Move_Signal(int y, int x, int d);
void Print(void);
void Print_grid(void);

int N, M;
int grid[MAX][MAX];
int dy[5] = { 0, -1, 0, 1, 0 };
int dx[5] = { 0, 0, 1, 0, -1 };	// 0 U R D L
int dir[4][5] = 
{
	{ 0, 1, 2, 3, 4 },
	{ 0, 2, 1, 4, 3 },
	{ 0, 4, 3, 2, 1 },
	{ 0, 0, 0, 0, 0 }
};
char result_char[5] = { '\0', 'U', 'R', 'D', 'L' };
int pr, pc;
int eter_flag;
int max_time;
int max_dir;

int main(void)
{
	freopen("n.txt", "r", stdin);
	Input();
	//Print_grid();
	Operation();
	Print();

	return 0;
}

void Input(void)
{
	int i, j;
	char tmp[MAX] = { 0 };

	eter_flag = 0;
	max_time = 0;	 max_dir = 0;
	scanf("%d %d", &N, &M);
	for (i = 1; i <= N; i++)
	{
		scanf("%s", &tmp[1]);
		for (j = 1; j <= M; j++)
		{
			if(tmp[j] == '.') grid[i][j] = 0;
			else if (tmp[j] == '/') grid[i][j] = 1;
			else if (tmp[j] == '\\') grid[i][j] = 2;
			else if (tmp[j] == 'C') grid[i][j] = 3;
		}
	}
	scanf("%d %d", &pr, &pc);
}

void Operation(void)
{
	int i, j, d, r;

	for (d = 1; d <= 4; d++)
	{
		r = Move_Signal(pr, pc, d);
		//printf("[%d] r.time = %d, r.dir = %c\n", d, r.time, result_char[r.dir]);
		if (r == 0)
		{
			max_dir = d;
			eter_flag = 1;
			break;
		}
		else if (max_time < r)
		{
			max_time = r;
			max_dir = d;
		}
	}
}

int Move_Signal(int y, int x, int d)
{
	int time = 1;
	int ny = y, nx = x, nd = d;

	//printf("\n\n[진행 시작!!]\n");
	for (;;)
	{
		/*
		Print_visit();
		getch();
		*/
		/*
		printf("y = %d, x = %d, dir = %d\n", ny, nx, d);
		printf("	▼\n");
		getch();
		*/

		ny += dy[nd];		nx += dx[nd];
		/*
		printf("y = %d, x = %d, dir = %d\n", ny, nx, d);
		printf("time = %d 경과\n", time);
		printf("=============================\n");
		*/

		if (ny < 1 || ny > N || nx < 1 || nx > M || (grid[ny][nx] == 3)) return time;
		if (ny == y && nx == x && nd == d) return 0;
		else if ( grid[ny][nx] )	// 1이거나 2일 때
		{
			//printf("방향이 dir = %d에서 ", d);
			nd = dir[ grid[ny][nx] ][nd];
			/*
			printf("dir = %d로 바뀌었음!!\n", d);
			getch();
			*/
		}	
		time++;
	}
}

void Print(void)
{
	printf("%c\n", result_char[max_dir]);
	if (eter_flag) printf("Voyager\n");
	else printf("%d\n", max_time);
}

void Print_grid(void)
{
	int i, j;
	printf("Print_grid\n");
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= M; j++)
		{
			printf("%d ", grid[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
#endif
