// 20191108
// [SWEA. 5656] 벽돌 깨기

/*
	[오늘의 교훈]
	1. visit배열의 의미!! : visit 배열은 0으로 풀어주기 전까지 같은 곳을 중복해서 또 방문할 수 없다는 의미!!
					- 그래서 visit으로 막힌 다음에 (바로 뒤로 돌아가는 행동만 있는 것이 아니니)
					   어떻게 진행되는지 살펴보자!!
					- 이 문제에서 visit은 이미 InQ를 해줬으니, 다시 할 필요가 없다는 의미!
					  ( 만약 map이 0이라면, 어차피 if( map[ny][nx] ) 라는 조건에 충족하지 않아 인큐도 되지 않을 것! )
			       && greedy => 가장 좋은 경험을 저장시켜주는 용도!!
			       		- 특히 -1이나 엄청나게 큰 수로 초기화를 시켜놓고
					  최소값을 갱신하는데 사용함!
		==> 이렇게 크게 두 가지 의미가 있으니 까먹지 말 것!
		
	2. 배열의 범위 - Segmentation Fault
		- 프로젝트 때 뿐만이 아니라, 알고리즘에서도 배열의 잘못된 인덱스를 참조하는 일이 많음!
		- 이 문제에서는 queue에 넣을 때 map의 범위를 벗어나는 것을 넣어줬기 때문에 48/50이라고 생각...
			( 물론 이것은 Segmentation Fault는 아니지만!! )
		- 이중for문 돌 때, 인덱스를 바꿔 쓰거나, ++, --가 물린다면 무한루프 빠질 위험이 있어!!
			( 빨간 포인트 찍고, F5, 그리고 조사식에서 원하는 변수를 넣은 다음, F10으로 다음 다음!! 변화하는 것을 찍어보자! )
*/
#if 0
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
int visit[MAX][MAX];
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

	if (i > H) return; //
	wp = rp = 0;
	InQ(i, s, map[i][s] - 1);
	map[i][s] = 0;
	visit[i][s] = 1;
	while (wp > rp)
	{
		out = OutQ();
		sy = out->y;		sx = out->x;		sl = out->life;
		for (i = 0; i < 4; i++)
		{
			for (j = 1; j <= sl; j++)
			{
				ny = sy + dy[i] * j;	nx = sx + dx[i] * j;
				if (ny < 1 || ny > H || nx < 1 || nx > W || visit[ny][nx] ) continue;
				if (map[ny][nx])
				{
					visit[ny][nx] = 1;
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
			visit[i][j] = 0;
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
