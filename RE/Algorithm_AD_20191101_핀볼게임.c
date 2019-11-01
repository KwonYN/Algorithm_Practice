// 20191101
// [SWEA. 5650] [모의 SW 역량테스트] 핀볼 게임
#if 01
#include <stdio.h>
#define MAX	(110)

typedef struct { int y, x; }NODE;
NODE wh[12][3];

void Init(void);
void Input(void);
void Operation(void);
int Move_Ball(int y, int x, int d);

void Print_Board(void);
void Print_Hole(void);

int T, N;
int Board[MAX][MAX];
int Score;
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };
int dir[6][4] = { { 0, 0, 0, 0 },
				  { 1, 3, 0, 2 },
			      { 3, 0, 1, 2 },
				  { 2, 0, 3, 1 },
				  { 1, 2, 3, 0 },
				  { 1, 0, 3, 2 } };
int main(void)
{
	int i;

	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (i = 1; i <= T; i++)
	{
		Input();
		Operation();
		printf("#%d %d\n", i, Score);
		//Print_Board();
		//Print_Hole();
		Init();
	}
	
	return 0;
}

void Input(void)
{
	int i, j, tmp;
	int cnt[12] = { 0 };

	Score = 0;
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			scanf("%d", &tmp);
			Board[i][j] = tmp;
			if (tmp >= 6 && tmp <= 10) wh[tmp][cnt[tmp]++] = (NODE){ i, j };
		}
	}
	for (i = 1; i <= N; i++) Board[0][i] = Board[N + 1][i] = Board[i][0] = Board[i][N + 1] = 5;
}

void Operation(void)
{
	int i, j, d, r;

	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			if (Board[i][j] != 0) continue;
			for (d = 0; d < 4; d++)
			{
				r = Move_Ball(i, j, d);
				if (Score < r) Score = r;
			}			
		}
	}
}

int Move_Ball(int y, int x, int d)
{
	int ny, nx, nd;
	int score = 0;
	int ey = y, ex = x;
	int block;

	//printf("[새로운 시작!!]\n");
	for ( ; ; )
	{
		nd = d;		ny = y + dy[nd];	nx = x + dx[nd];
		/*
		getch();
		printf("현재 공의 위치 : y = %d, x = %d // dir = %d\n", y, x, d);
		printf("		▼\n");
		printf("어떤 블럭을 만났지? : %d\n", Board[ny][nx]);
		*/
		block = Board[ny][nx];	// 변수 선언의 중요성!!!
		if (block >= 1 && block <= 5)
		{
			nd = dir[block][nd];		score++;
		}
		else if (block == -1 || (ny == ey && nx == ex)) break;
		else if (block >= 6)
		{
			if (wh[block][0].y == ny && wh[block][0].x == nx)
			{
				ny = wh[block][1].y;	nx = wh[block][1].x;
			}
			else
			{
				ny = wh[block][0].y;	nx = wh[block][0].x;
			}
		}
		y = ny;		x = nx;		d = nd;
		/*
		printf("		▼\n");
		printf("이동한 공 위치 : y = %d, x = %d // dir = %d\n", y, x, d);
		printf("===========================================\n");
		*/
	}

	return score;
}

void Init(void)
{
	int i, j;

	for (i = 0; i <= N + 1; i++) for (j = 0; j <= N + 1; j++) Board[i][j] = 0;
	for (i = 6; i <= 10; i++) for (j = 0; j < 2; j++) wh[i][j] = (NODE){ 0, 0 };
}

void Print_Board(void)
{
	int i, j;
	printf("Print_Board\n");
	for (i = 0; i <= N + 1; i++)
	{
		for (j = 0; j <= N + 1; j++)
		{
			printf("%2d ", Board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void Print_Hole(void)
{
	int i, j;
	printf("====================\n");
	printf("Print_WormHole\n");
	for (i = 6; i <= 10; i++) for (j = 0; j < 2; j++) printf("[%d번] [%d번째] y = %d, x = %d\n", i, j, wh[i][j].y, wh[i][j].x);
	printf("====================\n");
}
#endif
