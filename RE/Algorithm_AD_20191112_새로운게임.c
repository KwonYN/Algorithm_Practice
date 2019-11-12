// 20191112
// [BOJ. 17780] 새로운 게임
#if 01
#include <stdio.h>
#define MAX	(15)

enum COLOR{ W = 0, R = 1, B = 2 };

struct _st { int y, x, dir, floor; }HORSE;
struct _st horse[12];

typedef struct { int idx[10], sp; }CHK;
CHK chk[MAX][MAX];


void Input(void);
int Operation(void);

void Print_HORSE(void);
void Print_Chk(void);
void Print_map(void);

int N, K;
int map[MAX][MAX];
int dy[5] = { 0, 0, 0, -1, 1 };
int dx[5] = { 0, 1, -1, 0, 0 };
int dd[5] = { 0, 2, 1, 4, 3 };

int main(void)
{
	//freopen("in.txt", "r", stdin);
	Input();
	//Print_map();
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
		horse[i] = (struct _st){ yy, xx, dd, 0 };
		chk[yy][xx].idx[++chk[yy][xx].sp] = i;
	}
	for (i = 1; i <= N; i++) map[i][0] = map[i][N+1] = map[0][i] = map[N+1][i] = B;
}

int Operation(void)
{
	int i, j, k, t = 0;
	int d, sy, sx, ny, nx, sp_tmp;
	int tmp_idx[MAX];
	int end_flag = 0;

	while (++t <= 1000)
	{
		for (i = 1; i <= K; i++)
		{
			if (horse[i].floor) continue;	// 다른 말 위에 있는 말은 움직이지 않는다. 밑에 있는 말 따라서 움직여짐.
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
                                        continue;
				}
			}// 위까지의 경우에 해당되지 않는다면 가장 밑에 있는 말 i가 움직였는데 그 곳이 하얀색이거나 빨간색인 경우!!

			horse[i].dir = d;	// 일단 말 i가 이동한 방향을 다시 말 i에 넣어줌
			sp_tmp = chk[sy][sx].sp;
			for(j = 1; j <= sp_tmp; j++)    // 말 i를 포함하여 그 위에 있는 말들의 좌표 바꿈
                        {
                                tmp_idx[j] = chk[sy][sx].idx[j];
                                horse[tmp_idx[j]].y = ny;
                                horse[tmp_idx[j]].x = nx;
                        }
                        chk[sy][sx].sp = 0;
                        if(map[ny][nx] == R)
                        {
                                for(j = sp_tmp; j >= 1; j--)
                                {
                                        chk[ny][nx].idx[++chk[ny][nx].sp] = tmp_idx[j];
                                        horse[tmp_idx[j]].floor = 1;
                                }
                                horse[chk[ny][nx].idx[1]].floor = 0;
                        }
                        else
                        {
                                for(j = 1; j <= sp_tmp; j++)
                                {
                                        chk[ny][nx].idx[++chk[ny][nx].sp] = tmp_idx[j];
                                        horse[tmp_idx[j]].floor = 1;
                                }
                                horse[chk[ny][nx].idx[1]].floor = 0;
                        }
                        if(chk[ny][nx].sp >= 4)
                        {
                                end_flag = 1;
                                break;
                        }
                        /*
                        Print_HORSE();
                        Print_Chk();
                        getch();
                        */
		}
		if (end_flag) break;
	}

	if (t > 1000) t = -1;
	return t;
}

void Print_HORSE(void)
{
	int i;
	printf("Print_HORSE\n");
	for (i = 1; i <= K; i++)
	{
		printf("[%d] y = %d, x = %d, dir = %d, floor = %d\n",
			i, horse[i].y, horse[i].x, horse[i].dir, horse[i].floor);
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
			printf("%d ", chk[i][j].sp);
		}
		printf("\n");
	}
	printf("\n");
}

void Print_map(void)
{
	int i, j;
	printf("Print_map\n");
	for (i = 0; i <= N+1; i++)
	{
		for (j = 0; j <= N+1; j++)
		{
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
#endif
