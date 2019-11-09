#pragma warning (disable: 4996)

// 20191108
// [SWEA. 5656] 벽돌 깨기
#if 01
#include <stdio.h>
#define MAX	(20)

typedef struct { int y, x, life; }BD;
BD queue[MAX*MAX*2];

void Input(void);
void DFS(int L);
void Copy_map(int L);
void Reverse_map(int L);
void BFS(int s);
void Gravity(void);
void InQ(int yy, int xx, int ll);
BD * OutQ(void);
int Last_cnt(void);
void Init_map(void);

void Print_list(int L);
void Print_cpy(int L);
void Print_map(void);

int T, N, W, H;
int map[MAX][MAX];
int cpymap[6][MAX][MAX];
int min_bricks;
int wp, rp;
int list[6];
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

int main(void)
{
	int i;

	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (i = 1; i <= T; i++)
	{
		Input();
		DFS(1);
		printf("#%d %d\n", i, min_bricks);
		Init_map();
	}
	
	return 0;
}

void Input(void)
{
	int i, j;

	min_bricks = 987654321;
	scanf("%d %d %d", &N, &W, &H);
	for (i = 1; i <= H; i++) for (j = 1; j <= W; j++) scanf("%d", &map[i][j]);
}

void DFS(int L)
{
	int i, r;

	if (L > N)
	{
		/*
		Print_map();
		getch();
		*/
		r = Last_cnt();
		if (min_bricks > r) min_bricks = r;
		return;
	}

	for (i = 1; i <= W; i++)
	{
		list[L] = i;
		Copy_map(L);
		/*
		printf("L = %d => ", L);
		Print_cpy(L);
		*/
		BFS(i);
		Gravity();

		DFS(L + 1);
		/*
		printf("L = %d => ", L);
		Print_cpy(L);
		getch();
		*/
		Reverse_map(L);
		list[L] = 0;
	}
}

void Copy_map(int L)
{
	int i, j;

	for (i = 1; i <= H; i++) for (j = 1; j <= W; j++) cpymap[L][i][j] = map[i][j];
}

void Reverse_map(int L)
{
	int i, j;

	for (i = 1; i <= H; i++)
	{
		for (j = 1; j <= W; j++)
		{
			map[i][j] = cpymap[L][i][j];
			cpymap[L][i][j] = 0;
		}
	}
}

void BFS(int s)
{
	int i, j;
	int sy, sx, sl, ny, nx;
	BD * out = (BD *)0x0;

	for (i = 1; i <= H; i++) if (map[i][s]) break;

	if (i > H) return;
	wp = rp = 0;
	InQ(i, s, map[i][s] - 1);
	map[i][s] = 0;
	while (wp > rp)
	{
		out = OutQ();
		sy = out->y;		sx = out->x;		sl = out->life;
		for (i = 0; i < 4; i++)
		{
			for (j = 1; j <= sl; j++)
			{
				ny = sy + dy[i] * j;	nx = sx + dx[i] * j;
				if (ny < 1 || ny > H || nx < 1 || nx > W ) continue;
				if (map[ny][nx])
				{
					InQ(ny, nx, map[ny][nx] - 1);
					map[ny][nx] = 0;
				}
			}
		}
	}
}

void Gravity(void)
{
	int i, j, cri;

	for (j = 1; j <= W; j++)
	{
		cri = H;
		for (i = H; i >= 1; i--)
		{
			if (map[i][j] == 0) continue;
			map[cri--][j] = map[i][j];
		}
		for (i = cri; i >= 1; i--) map[i][j] = 0;
	}
}

void InQ(int yy, int xx, int ll)
{
	queue[wp].y = yy;
	queue[wp].x = xx;
	queue[wp++].life = ll;
}

BD * OutQ(void) { return &(queue[rp++]); }

int Last_cnt(void)
{
	int i, j, cnt = 0;

	for (j = 1; j <= W; j++)
	{
		for (i = H; i >= 1; i--)
		{
			if (map[i][j]) cnt++;
			else break;
		}
	}

	return cnt;
}

void Init_map(void)
{
	int i, j;

	for (i = 1; i <= H; i++) for (j = 1; j <= W; j++) map[i][j] = 0;
}

void Print_list(int L)
{
	int i;
	printf("Print_list\n");
	for (i = 1; i < L; i++) printf("%d ", list[i]);
	printf("\n");
}

void Print_cpy(int L)
{
	int i, j;
	printf("Print_cpy\n");
	for (i = 1; i <= H; i++)
	{
		for (j = 1; j <= W; j++)
		{
			printf("%d ", cpymap[L][i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void Print_map(void)
{
	int i, j;
	printf("Print_map\n");
	for (i = 1; i <= H; i++)
	{
		for (j = 1; j <= W; j++)
		{
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
#endif
