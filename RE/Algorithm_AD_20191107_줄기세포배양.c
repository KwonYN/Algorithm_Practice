// 20191107
// [SWEA. 5653] 줄기세포 배양
#if 01
#include <stdio.h>
#define MAX	(370)

typedef struct { int y, x, life, total_life, dead_flag; }CELL;
CELL c[MAX*MAX];

void Input(void);
void Operation(void);
void Init_CHK(void);
void Init_Map(void);
void Print_Map(void);

int T, N, M, K;
int map[MAX][MAX];
chk[MAX][MAX];
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };
int root_cell;
int c_cnt;
int ymax, ymin, xmax, xmin;

int main(void)
{
	int i;

	freopen("in.txt", "r", stdin);
	
	scanf("%d", &T);
	for (i = 1; i <= T; i++)
	{
		Input();
		Operation();
		printf("#%d %d\n", i, root_cell);
		Init_Map();
	}

	return 0;
}

void Input(void)
{
	int i, j, tmp;

	ymax = xmax = 0;
	ymin = xmin = 987654321;
	c_cnt = root_cell = 0;
	scanf("%d %d %d", &N, &M, &K);
	N += 160;		M += 160;
	for (i = 161; i <= N; i++)
	{
		for (j = 161; j <= M; j++)
		{
			scanf("%d", &tmp);
			map[i][j] = tmp;
			if (tmp > 0)
			{
				if (ymax < i) ymax = i;
				if (ymin > i) ymin = i;
				if (xmax < j) xmax = j;
				if (xmin > j) xmin = j;
				c[++c_cnt] = (CELL) { i, j, tmp, 2 * tmp, 0 };
			}
		}
	}
	root_cell = c_cnt;	// root_cell은 총 세포의 개수
}

void Operation(void)
{
	int t, i, d, ny, nx;
	CELL tmp = (CELL){0, 0, 0, 0, 0};

	for (t = 1; t <= K; t++)
	{
		/*
		printf("현재 줄기세포 개수 = %d\n", root_cell);
		printf("[%d] ", t);
		Print_Map();
		getch();
		*/
		for (i = 1; i <= c_cnt; i++)
		{
			tmp = c[i];
			//printf("[%d] y = %d, x = %d, life = %d, total = %d, flag = %d\n", i, tmp.y, tmp.x, tmp.life, tmp.total_life, tmp.dead_flag);
			if ( tmp.dead_flag ) continue;
			//if (tmp.total_life - 1 == tmp.life) printf("[활성화!] y = %d, x = %d, life_left = %d\n", tmp.y, tmp.x, tmp.total_life - 1);
			if ( tmp.total_life-- == tmp.life ) // 활성이 되고 첫 1시간
			{
				for (d = 0; d < 4; d++)
				{
					ny = tmp.y + dy[d];		nx = tmp.x + dx[d];
					if ( map[ny][nx] ) continue;
					//printf("ny = %d, nx = %d\n", ny, nx);
					if (chk[ny][nx] < tmp.life)
					{
						chk[ny][nx] = tmp.life;
						if (ymax < ny) ymax = ny;
						if (ymin > ny) ymin = ny;
						if (xmax < nx) xmax = nx;
						if (xmin > nx) xmin = nx;
					}
				}
			}
			if ( tmp.total_life == 0 )
			{
				//printf("[죽음!] y = %d, x = %d, life_left = %d\n", tmp.y, tmp.x, tmp.total_life);
				tmp.dead_flag = 1;
				root_cell--;
			}
			c[i] = tmp;
		}
		Init_CHK();
	}
}


void Init_CHK(void)
{
	int i, j, tmp;

	for (i = ymin; i <= ymax; i++)
	{
		for (j = xmin; j <= xmax; j++)
		{
			tmp = chk[i][j];
			if (tmp)
			{
				//printf("[생성!] y = %d, x = %d, new_life = %d\n", i, j, tmp);
				map[i][j] = tmp;
				c[++c_cnt] = (CELL){ i, j, tmp, 2 * tmp, 0 };
				root_cell++;
				chk[i][j] = 0;
			}
		}
	}
}

void Init_Map(void)
{
	int i, j;

	for (i = ymin; i <= ymax; i++)
	{
		for (j = xmin; j <= xmax; j++)
		{
			map[i][j] = 0;
			c[i * MAX + j] = (CELL){ 0, 0, 0, 0, 0 };
		}
	}
}

void Print_Map(void)
{
	int i, j;
	printf("Print_Map\n");
	for (i = 155; i <= N + 6; i++)
	{
		for (j = 155; j <= M + 6; j++)
		{
			printf("%2d ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
#endif
