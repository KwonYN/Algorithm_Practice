#if 01
#include <stdio.h>
#define MAX	(20)
#define WHITE	(0)
#define RED		(1)
#define BLUE	(2)

struct _st { int no, y, x, dir; struct _st * down, *up; };
struct _st horse[15];

void Input(void);
void Operation(void);
int Reverse(int idx);
int Move_Up(int idx);
void Print_Board(void);
void Print_Link(void);
void Print_Structure(void);
void Print_Chk(void);

int dy[5] = { 0, 0, 0, -1, 1 };
int dx[5] = { 0, 1, -1, 0, 0 };
int dd[5] = { 0, 2, 1, 4, 3 };
int N, K;
int Board[MAX][MAX];
int chk[MAX][MAX];
int cnt[MAX][MAX];

int main(void)
{
	freopen("in.txt", "r", stdin);
	Input();
	Operation();
	Print_Board();

	return 0;
}

void Input(void)
{
	int i, j;
	int yy, xx, dd;

	scanf("%d %d", &N, &K);
	for (i = 1; i <= N; i++) for (j = 1; j <= N; j++) scanf("%d", &Board[i][j]);
	for (i = 1; i <= K; i++)
	{
		scanf("%d %d %d", &yy, &xx, &dd);
		horse[i] = (struct _st){ i, yy, xx, dd, 0x0, 0x0 };
		chk[yy][xx] = i;
	}
	for (i = 1; i <= N; i++)
	{
		Board[0][i] = Board[i][0] = Board[N + 1][i] = Board[i][N + 1] = BLUE;
	}
}

void Operation(void)
{
	int time, h, r, new_down;
	int ny, nx, nd;
	struct _st * tmp = (struct _st *)0x0;

	for (time = 1; time <= 1000; time++)
	{

		//Print_Link();
		//Print_Structure();
		//getch();

		for (h = 1; h <= K; h++)
		{
			if (horse[h].down != 0x0) continue;	// 다른 말 위에 올라타 있으면 움직이지 않아!
			chk[horse[h].y][horse[h].x] = 0;
			nd = horse[h].dir;
			ny = horse[h].y + dy[nd];			nx = horse[h].x + dx[nd];	// 현재 말이 가지고 있는 방향에서 일단 한 칸!
			if (Board[ny][nx] == BLUE)	// 일단 방향이 꺾이는 상황부터 처리
			{
				nd = dd[nd];
				ny = horse[h].y + dy[nd];			nx = horse[h].x + dx[nd];
				if (Board[ny][nx] == BLUE)
				{
					ny = horse[h].y;		nx = horse[h].x;
				}
			}
			// 다음 칸이 파란색이 아닌 흰색과 빨간색인 경우, 그래도 일단 움직이는 것은 동일!!
			horse[h].y = ny;		horse[h].x = nx;		horse[h].dir = nd;
			r = Move_Up(h);	// 가장 위에 있는 말의 번호가 리턴됨
			if (Board[ny][nx] == RED)
			{
				r = h;	// 뒤집힐 것이므로 현재 가장 밑에 있는 h번 말이 가장 위에 있는 말이 됨!
				new_down = Reverse(h);
			}
			else new_down = h;
			if (chk[ny][nx])
			{
				horse[chk[ny][nx]].up = &horse[new_down];
				horse[new_down].down = &horse[chk[ny][nx]];
			}
			chk[ny][nx] = r;
			/*
			Print_Link();
			Print_Chk();
			getch();
			*/
		}
	}
	if (time > 1000) time = -1;
	printf("%d\n", time);
}

int Move_Up(int idx) // 위에 있는 말들은 방향이 바뀌지 않음! 그냥 좌표만 바뀌는 것!
{
	struct _st * head = (struct _st *)0x0;

	for (head = &horse[idx]; head->up; head = head->up)
	{
		head->up->y = head->y;
		head->up->x = head->x;
	}
	return head->no;
}

int Reverse(int idx)
{
	struct _st * tmp = (struct _st *)0x0;
	struct _st * head = (struct _st *)0x0;

	for ( head = &horse[idx]; head->up; head = head->up )
	{
		tmp = head->up;
		head->up = head->down;
		head->down = tmp;
	}

	return head->no;	// 결국 뒤집혀서 가장 위에 있던 애가 가장 밑이 됨!!
}

void Print_Board(void)
{
	int i, j;
	printf("Print_Board\n");
	for (i = 0; i <= N + 1; i++)
	{
		for (j = 0; j <= N + 1; j++)
		{
			printf("%d ", Board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void Print_Link(void)
{
	int i;
	struct _st * head = (struct _st *)0x0;
	printf("Print_Link\n");
	for (i = 1; i <= K; i++)
	{
		if (horse[i].down != (struct _st *)0x0) continue;
		for (head = &horse[i]; head->up; head = head->up)
		{
			printf("[%d] y = %d, x = %d, dir = %d -> ", head->no, head->y, head->x);
		}
		printf("\n");
	}
}

void Print_Structure(void)
{
	int i;
	printf("Print_Structure\n");
	for (i = 1; i <= K; i++)
	{
		printf("[%d==%d?] y = %d, x = %d, dir = %d, down = %x, up = %x\n", i, horse[i].no, 
			horse[i].y, horse[i].x, horse[i].dir, horse[i].down, horse[i].up);
	}
	printf("=========================================================\n");
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
