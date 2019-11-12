// 20191112
// [BOJ. 17780] 새로운 게임
#if 01
#include <stdio.h>
#define MAX	(15)

enum COLOR{ W = 0, R = 1, B = 2 };

typedef struct { int num, y, x, dir, prev, next; }HORSE;
HORSE horse[12];

//typedef struct { int top, idx[10], sp; }CHK;
//CHK chk[MAX][MAX];

void Input(void);
int Operation(void);
void Init_Chk(void);

void Print_HORSE(void);
void Print_Chk(void);

int N, K;
int map[MAX][MAX];
int chk[MAX][MAX];
int dy[5] = { 0, 0, 0, -1, 1 };
int dx[5] = { 0, 1, -1, 0, 0 };
int dd[5] = { 0, 2, 1, 4, 3 };

int main(void)
{
	freopen("in.txt", "r", stdin);
	Input();
	//Print_HORSE();
	printf("%d\n", Operation());

	return 0;
}

void Input(void)
{
	int i, j;
	int yy, xx, dd;

	scanf("%d %d", &N, &K);
	for (i = 1; i <= N; i++) for (j = 1; j <= N; j++) scanf("%d", &map[i][j]);
	for (i = 1; i <= K; i++)
	{
		scanf("%d %d %d", &yy, &xx, &dd);
		horse[i] = (HORSE){i, yy, xx, dd, 0, 0};
	}
	for (i = 1; i <= N; i++) map[i][0] = map[N+1][0] = map[0][i] = map[0][N+1] = B;
}

int Operation(void)
{
	int i, j, k, t = 0;
	int d, sy, sx, ny, nx;
	HORSE * head;
	int tmp_idx[MAX];
	int down, up, end_flag = 0;
	
	while (++t <= 1000)
	{
		for (i = 1; i <= K; i++)
		{
			head = (HORSE *)0x0;
			if (horse[i].prev) continue;	// 다른 말 위에 있는 말은 움직이지 않는다. 밑에 있는 말 따라서 움직여짐.
			d = horse[i].dir;							// 가장 밑에 있는 말 i의 방향
			sy = horse[i].y;		sx = horse[i].x;	// 가장 밑에 있는 말 i의 좌표
			ny = sy + dy[d];		nx = sx + dx[d];	// 가장 밑에 있는 말 i의 이동
			if (map[ny][nx] == B)	// 그런데 그 곳이 파란색이라면
			{
				d = dd[d];			// 방향 반대로!
				ny = sy + dy[d];		nx = sx + dx[d];	// 그 반대 방향으로 이동
				if (map[ny][nx] == B)		// 그런데 그 곳도 파란색이라면?
				{
					ny = sy;		nx = sx;	// 움직이지 않고 처음 그 자리에 있게 됨.
				}
			}// 위까지의 경우에 해당되지 않는다면 가장 밑에 있는 말 i가 움직였는데 그 곳이 하얀색이거나 빨간색인 경우!!
			
			horse[i].dir = d;	// 일단 말 i가 이동한 방향을 다시 말 i에 넣어줌
			for (head = &horse[i], j = 1; head->next != 0; head = &horse[head->next], j++)// 말 i의 위에 있는 말들 모두 이동시켜줌!!
			{
				printf("head.num = %d\n", head->num);
				getch();
				horse[head->num].y = ny;		horse[head->num].x = nx;
				tmp_idx[j] = head->num;	// 그와 동시에 말 i를 포함하여 그 위에 있는 말들의 idx를 배열에 넣어줌
			}

			for (int z = 1; z < j; z++)
			{
				printf("%d ", tmp_idx[z]);
			}
			printf("\n");


			/*
			if (j >= 5)
			{
				end_flag = 1;
				break;
			}
			if (map[ny][nx] == R)	// 빨간 색이라면, 거꾸로 넣어주어야 함!
			{
				down = chk[ny][nx];
				for (k = j - 1; k >= 1; k--)
				{
					horse[tmp_idx[k]].prev = down;
					down = horse[tmp_idx[k]].prev;
				}
				down = 0;
				for (k = j - 1; k >= 1; k--)
				{
					horse[tmp_idx[k]].next = down;
					down = horse[tmp_idx[k]].next;
				}
				chk[ny][nx] = horse[tmp_idx[j - 1]].num;
			}
			else
			{
				horse[i].prev = chk[ny][nx];
				chk[ny][nx] = horse[tmp_idx[j - 1]].num;
			}
			*/

			/*
			Print_Chk();
			getch();
			*/

		}
		if (end_flag) break;
		//초기화 및 처리 코드 함수!!!
		Init_Chk();
	}

	if (t > 1000) t = -1;
	return t;
}

void Init_Chk(void)
{
	int i;

	for (i = 1; i <= K; i++) chk[horse[i].y][horse[i].x] = 0;
}

void Print_HORSE(void)
{
	int i;
	printf("Print_HORSE\n");
	for (i = 1; i <= K; i++)
	{
		printf("num = %d, y = %d, x = %d, dir = %d, prev = %d, next = %d\n",
			horse[i].num, horse[i].y, horse[i].x, horse[i].dir, horse[i].prev, horse[i].next);
	}
	printf("\n");
}

void Print_Chk(void)
{
	int i, j;
	printf("Print_Chk\n");
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			printf("%d ", chk[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
#endif
