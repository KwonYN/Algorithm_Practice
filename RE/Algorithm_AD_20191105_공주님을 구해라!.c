// 20191105
// [BOJ. 17836] 공주님을 구해라!
#if 01
#include <stdio.h>
#define MAX	(110)
#define INF	(987654321)
#define ABS(a)	( ( (a) < 0 ) ? -(a) : (a) )
#define DIST(a, b, c, d)	( ABS( (a) - (b) ) + ABS( (c) - (d) ) )

typedef struct { int y, x; }NODE;
NODE Que[MAX * MAX];

void Input(void);
int BFS(int sy, int sx);
void InQ(int yy, int xx);
NODE * OutQ(void);
void Init_Visit(void);

int N, M, T;
int castle[MAX][MAX], visit[MAX][MAX];
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };
int wp, rp;
int time;

int main(void)
{
	freopen("in.txt", "r", stdin);
	Input();
	time = BFS(1, 1);
	if (time > T) printf("Fail\n");
	else printf("%d\n", time);

	return 0;
}

void Input(void)
{
	int i, j;

	time = 0;
	scanf("%d %d %d", &N, &M, &T);
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= M; j++)
		{
			scanf("%d", &castle[i][j]);
		}
	}
}

int BFS(int sy, int sx)
{
	int i, ny, nx;
	NODE * out = (NODE *)0x0;
	int get_time = INF, get_gram = INF, result;
	int end_flag = 0;

	Init_Visit();

	wp = rp = 0;
	InQ(sy, sx);
	visit[sy][sx] = 0;
	while (wp > rp)
	{
		out = OutQ();
		sy = out->y;		sx = out->x;
		for (i = 0; i < 4; i++)
		{
			ny = sy + dy[i];	nx = sx + dx[i];
			if (ny < 1 || ny > N || nx < 1 || nx > M) continue;
			if ( castle[ny][nx] != 1 && visit[ny][nx] == -1 )
			{
				visit[ny][nx] = visit[sy][sx] + 1;
				if (castle[ny][nx] == 2)
				{
					get_gram = visit[ny][nx] + DIST(ny, N, nx, M);
				}
				else
				{
					if (ny == N && nx == M)
					{
						get_time = visit[ny][nx];
						end_flag = 1;
						break;
					}
					InQ(ny, nx);
				}
			}
		}
		if (end_flag) break;
	}
	result = (get_time < get_gram) ? get_time : get_gram;
	
	return result;
}

void InQ(int yy, int xx)
{
	Que[wp].y = yy;
	Que[wp++].x = xx;
}

NODE * OutQ(void){ return &(Que[rp++]); }

void Init_Visit(void)
{
	int i, j;

	for (i = 1; i <= N; i++) for (j = 1; j <= M; j++) visit[i][j] = -1;
}
#endif
