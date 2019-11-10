// 20191110
// [SWEA. 1953] 탈주범 검거
/*
		처음에 틀렸던 부분!!: 
			if ( map[sy][sx] & now_dir[i] == 0 ) continue;
			와 if ( (map[sy][sx] & now_dir[i]) == 0 ) continue;의 차이는!?!?!?
				=> 연산자 우선순위!!!!!! 이거 붕어 문제 때도 많이 했잖아!!!!;;;;
*/
#if 01
#include <stdio.h>
#define MAX	(60)

typedef struct { int y, x; }LOC;
LOC loc[MAX * MAX * 2];

void Input(void);
int BFS(int sy, int sx);
void InQ(int yy, int xx);
LOC * OutQ(void);
void Init_map(void);

void Print_map(void);


int pipe[8] = { 0, 0xf, 0x5, 0xa, 0x9, 0xc, 0x6, 0x3 };
int T, N, M, R, C, L;
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };
//int dd[4] = { 1, 0, 3, 2 };
int now_dir[4] = { 1, 4, 2, 8 };
int next_dir[4] = { 4, 1, 8, 2 };
int map[MAX][MAX];
int visit[MAX][MAX];
int poss_loc;
int wp, rp;

int main(void)
{
	int i;

	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (i = 1; i <= T; i++)
	{
		Input();
		//Print_map();
		printf("#%d %d\n", i, BFS(R, C));
		Init_map();
	}

	return 0;
}

void Input(void)
{
	int i, j, tmp;

	poss_loc = 0;
	scanf("%d %d %d %d %d", &N, &M, &R, &C, &L);
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			scanf("%d", &tmp);
			map[i][j] = pipe[tmp];
		}
	}
}

int BFS(int sy, int sx)
{
	LOC * out = (LOC *)0x0;
	int i;
	int ny, nx;
	int cnt = 0;

	wp = rp = 0;
	InQ(sy, sx);
	visit[sy][sx] = 1;
	cnt++;
	while (wp > rp)
	{
		out = OutQ();
		sy = out->y;		sx = out->x;
		for (i = 0; i < 4; i++)
		{
			ny = sy + dy[i];		nx = sx + dx[i];
			if (ny < 0 || ny >= N || nx < 0 || nx >= M || visit[ny][nx]) continue;
			if ((map[sy][sx] & now_dir[i]) == 0) continue;
			if (map[ny][nx] & next_dir[i])
			{
				visit[ny][nx] = visit[sy][sx] + 1;
				if (visit[ny][nx] > L) continue;
				cnt++;
				InQ(ny, nx);
			}
		}
	}

	return cnt;
}

void InQ(int yy, int xx)
{
	loc[wp].y = yy;
	loc[wp++].x = xx;
}

LOC * OutQ(void)
{
	return &(loc[rp++]);
}

void Init_map(void)
{
	int i, j;
	for (i = 0; i < N; i++) for (j = 0; j < M; j++) map[i][j] = visit[i][j] = 0;
}


void Print_map(void)
{
	int i, j;
	printf("Print_map\n");
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			printf("%X ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
#endif
