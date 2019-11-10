// 20191110
// [BOJ. 17069] 파이프 옮기기 1
#if 01
#include <stdio.h>
#define MAX	(20)

void Input(void);
void DFS(int ey, int ex, int type);

void Print_pipe(int ey, int ex);
void Print_map(void);

int N;
int map[MAX][MAX];
int dy[3] = { 0, 1, 1 };
int dx[3] = { 1, 1, 0 };	
int c1[3] = { 0, 2, 1 };
int cnt;

int main(void)
{
	freopen("in.txt", "r", stdin);
	Input();
	DFS(1, 2, 0);
	printf("%d\n", cnt);
	//Print_map();

	return 0;
}

void Input(void)
{
	int i, j;

	cnt = 0;
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			scanf("%d", &map[i][j]);
		}
	}
	for (i = 1; i <= N; i++) map[i][0] = map[i][N+1] = map[0][i] = map[N+1][i] = 1;
}

void DFS(int ey, int ex, int type)
{
	int j, ny, nx;
	int cnt1 = 0;

	/*
	printf("cnt = %d\n", cnt);
	if (type == 0) printf("type = %s\n", "가로");
	else if(type == 1) printf("type = %s\n", "대각선");
	else printf("type = %s\n", "세로");
	printf("ey = %d, ex = %d \n", ey, ex);
	Print_pipe(ey, ex);
	getch();
	*/

	if ( (ey == N) && (ex == N) )
	{
		cnt++;
		return;
	}

	switch (type)
	{
		// 가로
		case 0:
			for (j = 0; j < 3; j++)
			{
				ny = ey + dy[j];	nx = ex + dx[j];
				if (map[ny][nx]) return;
				if (j == 0) DFS(ny, nx, j);
			}
			DFS(ey + dy[1], ex + dx[1], 1);
			break;
		// 대각선
		case 1:
			for (j = 0; j < 3; j++)
			{
				ny = ey + dy[c1[j]];	nx = ex + dx[c1[j]];
				if (map[ny][nx]) cnt1++;
				else if (c1[j] == 0 && !map[ny][nx]) DFS(ny, nx, c1[j]);
				else if (c1[j] == 2 && !map[ny][nx]) DFS(ny, nx, c1[j]);
			}
			if (cnt1 == 0) DFS(ey + dy[1], ex + dx[1], 1);
			break;
		//세로
		default:
			for (j = 2; j >= 0; j--)
			{
				ny = ey + dy[j];	nx = ex + dx[j];
				if (map[ny][nx]) return;
				if (j == 2) DFS( ny, nx, j);
			}
			DFS(ey + dy[1], ex + dx[1], 1);
			break;
	}
}


void Print_pipe(int ey, int ex)
{
	int i, j;
	printf("Print_pipe\n");
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			if (i == ey && j == ex) printf("2 ");
			else if (map[i][j]) printf("%d ", map[i][j]);
			else  printf("0 ");
		}
		printf("\n");
	}
	printf("\n");
}

void Print_map(void)
{
	int i, j;
	printf("Print_map\n");
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
#endif
