// 20191110
// [BOJ. 1938] 통나무 옮기기
/*
	[오늘의 교훈!!]
	1. 범위 체크 매너리즘에 빠지지 말자.
		- 다른 범위 체크는 잘 해주었지만,
		  통나무를 돌릴 때, ㅡ -> ㅣ or ㅣ -> ㅡ 로 변환될 때,
		  가로/세로의 길이가 달라지므로 범위 체크를 다시 해주어야 함!
		  ==> 맵의 끝 부분에서 회전을 할 때 주의!!!
	
	2. 세 개가 동시에 움직인다고 해도, 그 패턴을 알 수 있기 때문에 중간에 있는 통나무 하나만 움직여봐도 알 수 있음
		- 게다가 회전은 중앙에 있는 통나무를 중심으로 움직이기 때문에 "s[2].y와 s[2].x"가 핵심임을 알 수 있음!!
*/
#if 01
#include <stdio.h>
#define MAX     (60)

typedef struct { int y, x; } TREE;
TREE s[5], e[5];

typedef struct { int y, x, type; } QUEUE;
QUEUE queue[MAX*MAX * 2];

void Input(void);
int BFS(int sy, int sx);
void InQ(int yy, int xx, int ty);
QUEUE * OutQ(void);

void Print_map(void);
void Print_visit(void);

int N;
int map[MAX][MAX];
int visit[3][MAX][MAX];
int wp, rp;
int s_cnt, e_cnt;
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

int main(void)
{
	freopen("in.txt", "r", stdin);
	Input();
	printf("%d\n", BFS(s[2].y, s[2].x));
	//Print_map();
	//Print_visit();

	return 0;
}

void Input(void)
{
	int i, j;
	char tmp[MAX];

	s_cnt = e_cnt = 0;
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		scanf("%s", &tmp[1]);
		for (j = 1; j <= N; j++)
		{
			if (tmp[j] == '0') map[i][j] = 0;
			else if (tmp[j] == '1') map[i][j] = 1;
			else if (tmp[j] == 'B')
			{
				s[++s_cnt] = (TREE){ i, j };
				//map[i][j] = 0xb;
			}
			else
			{
				e[++e_cnt] = (TREE){ i, j };
				//map[i][j] = 0xe;
			}
		}
	}
	//for (i = 1; i <= N; i++) map[0][i] = map[N+1][i] = map[i][0] = map[i][N+1] = 1;
}

int BFS(int sy, int sx)
{
	int i, ny, nx, st, et;
	QUEUE * out = (QUEUE *)0x0;

	if (e[1].x == e[2].x) et = 1; // 세로
	else et = 0;    // 가로

	wp = rp = 0;
	if (s[1].x == s[2].x) st = 1; // 세로
	else st = 0;    // 가로
	visit[st][sy][sx] = 1;
	InQ(sy, sx, st);
	while (wp > rp)
	{
		out = OutQ();
		sy = out->y;    sx = out->x;    st = out->type;

		//Print_visit();
		//getch();
		/*
		printf("s[2].y = %d, s[2].x = %d, ", sy, sx);
		if(st == 0) printf("type = %s\n", "가로");
		else printf("type = %s\n", "세로");
		printf("e[2].y = %d, e[2].x = %d, ", e[2].y, e[2].x);
		if(et == 0) printf("type = %s\n", "가로");
		else printf("type = %s\n", "세로");
		printf("               ▼\n");
		getch();
		*/
		if (sy == e[2].y && sx == e[2].x && st == et) return visit[st][sy][sx] - 1;
		if (st == 0)//가로
		{
			for (i = 0; i < 4; i++)
			{
				ny = sy + dy[i];  nx = sx + dx[i];
				if (ny < 1 || ny > N || nx - 1 < 1 || nx + 1 > N) continue;
				if (map[ny][nx - 1] || map[ny][nx] || map[ny][nx + 1]) continue;
				if (!visit[st][ny][nx])
				{
					InQ(ny, nx, st);
					visit[st][ny][nx] = visit[st][sy][sx] + 1;
				}
			}
			if (!map[sy - 1][sx - 1] && !map[sy - 1][sx] && !map[sy - 1][sx + 1] && !map[sy + 1][sx - 1] && !map[sy + 1][sx] && !map[sy + 1][sx + 1])
			{
				if (sy - 1 < 1 || sy + 1 > N || sx - 1 < 1 || sx + 1 > N) continue;
				if (!visit[1][sy][sx])
				{
					InQ(sy, sx, 1);
					visit[1][sy][sx] = visit[st][sy][sx] + 1;
				}
			}
		}
		else//세로
		{
			for (i = 0; i < 4; i++)
			{
				ny = sy + dy[i];  nx = sx + dx[i];
				if (nx < 1 || nx > N || ny - 1 < 1 || ny + 1 > N) continue;
				if (map[ny - 1][nx] || map[ny][nx] || map[ny + 1][nx]) continue;
				if (!visit[st][ny][nx])
				{
					InQ(ny, nx, st);
					visit[st][ny][nx] = visit[st][sy][sx] + 1;
				}
			}
			if (!map[sy - 1][sx - 1] && !map[sy][sx - 1] && !map[sy + 1][sx - 1] && !map[sy - 1][sx + 1] && !map[sy][sx + 1] && !map[sy + 1][sx + 1])
			{
				if (sy - 1 < 1 || sy + 1 > N || sx - 1 < 1 || sx + 1 > N) continue;
				if (!visit[0][sy][sx])
				{
					InQ(sy, sx, 0);
					visit[0][sy][sx] = visit[st][sy][sx] + 1;
				}
			}
		}
	}

	return 0;
}

void InQ(int yy, int xx, int ty)
{
	queue[wp].y = yy;
	queue[wp].x = xx;
	queue[wp++].type = ty;
}

QUEUE * OutQ(void)
{
	return &(queue[rp++]);
}



void Print_map(void)
{
	int i, j;
	printf("Print_map\n");
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			printf("%X ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void Print_visit(void)
{
	int i, j, t;
	printf("Print_visit\n");
	for (t = 0; t <2; t++)
	{
		printf("type = %d\n", t);
		for (i = 1; i <= N; i++)
		{
			for (j = 1; j <= N; j++)
			{
				printf("%d ", visit[t][i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
	printf("\n");
}
#endif
