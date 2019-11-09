/*
    [오늘의 교훈!!]
    1. 2차원 구조체 배열 내의 멤버로 int sum, int idx[6], int sp; 를 선언해줬었는데,
      중요한 것은 이 2차원 구조체 배열의 범위를 2000*2000으로 잡았었음.
      추가적으로 이 구조체를 다루는 for문의 범위는 1 ~ 1000까지인 것이 두 갠가 세 개였음..
      ==> 대충 따져봐도 (4 + 24 + 4)*2000*2000*1000*1000이면 백 조가 넘는 바이트 수... 도랐슴미까!?!?!?!?
    
    2. 특히 이렇게 Map의 범위가 정해져 있지 않거나 매우 큰 경우,
      이 map에 대해서 계속 for문을 돌면 시간초과뿐만 아니라 메모리도 초과될 수 있는 가능성이 너무 높아짐!!
      ==> 그렇다면 당연히 전체 for문을 돌라는 이야기가 아닐 거야!!
          분명히 1차원 구조체 배열을 쓸 수 있는 게 나올텐데, 얘네들만을 가지고 for문을 돌아
          하고 싶은 일이 다 가능한지를 알아보는 것이 중요!
          ==> 여기에서는 "원자 구조체"를 가지고 할 수 있음!!
              chk[][]배열은 원자들이(1 ~ N) 한 번 이동할 때마다 원자가 그 위치에 몇 개나 있는지 확인해주기 위한 마킹!!
              그리고 한 번 이동 후, 겹쳤는지를 확인해주면서 chk[][] 값이 1이라면, 그냥 0으로 초기화해줘도 되지만,
                                        1보다 크다면 에너지를 방출하며 소멸되어야 하므로,
                                        다시 1 ~ N까지 for문을 돌며 좌표가 같은 애들을 찾아주고, 걔네들의 에너지를 토탈에 더한 후, 죽여주면 됨!!!

*/
#if 01
#include <stdio.h>
#define MAXM	(4200)
#define MAXW	(1100)

typedef struct { int y, x, d, e, boundary; }WONJA;
WONJA wonja[MAXW];

void Input(void);
void Operation(void);
void Renew_chk(void);
void Init(void);
void Print_chk(void);

int T, N;
int chk[MAXM][MAXM];
int dy[4] = { 1, -1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };
int b_cnt;
int total_energy;

int main(void)
{
	int i;

	scanf("%d", &T);
	for (i = 1; i <= T; i++)
	{
		Input();
		Operation();
		printf("#%d %d\n", i, total_energy);
		Init();
	}

	return 0;
}

void Input(void)
{
	int i;
	int yy, xx, dd, ee;

	total_energy = 0;	// 총 방출 에너지
	b_cnt = 0;
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		scanf("%d %d %d %d", &xx, &yy, &dd, &ee);
		xx += 1000;		yy += 1000;
		xx *= 2;		yy *= 2;
		wonja[i] = (WONJA) { yy, xx, dd, ee, 0 };
	}
}

void Operation(void)
{
	int t = 0, i;
	int ny, nx, d;

	// 모두 다 범위를 벗어날 정도의 최대 시간까지 도달하거나,
	// 에너지를 방출한 원자들이 원자의 수와 같다, 즉 모든 원자가 에너지를 방출했을 때 끝남!
	while ( (++t <= 4000) || (b_cnt < N) )
	{	// 원자들 다 확인해봄
		for (i = 1; i <= N; i++)
		{
			if (wonja[i].boundary) continue; // 다 확인해보지만, 걔네가 확인할 필요가 없는 상태면 바로 건너뜀
			d = wonja[i].d;
			ny = wonja[i].y + dy[d];	nx = wonja[i].x + dx[d];	// 원자의 새로운 이동 위치!
			// 만약 범위를 넘어섰다, 즉 만날 수 없는 영역에 들어섰다면 boundary 벗어났다는 플래그
			// (이는 죽는 플래그와 동일! ==> 앞으로 이동시키지 않을 것이기 때문!)
			if (ny < 0 || ny > 4000 || nx < 0 || nx > 4000)
			{
				wonja[i].boundary = 1;
				b_cnt++;
				continue;
			}
			wonja[i].y = ny;	wonja[i].x = nx;
			chk[ny][nx]++;
		}
		Renew_chk();
		//printf("b_cnt = %d\n", b_cnt);
		//printf("[%d] total_energy = %d\n", t, total_energy);
		//Print_chk();
		//getch();
	}
}

void Renew_chk(void)
{
	int i, k, yy, xx;

	for (i = 1; i <= N; i++)
	{
		if ( wonja[i].boundary ) continue;
		yy = wonja[i].y;	xx = wonja[i].x;
		if (chk[yy][xx] > 1)
		{
			for (k = 1; k <= N; k++)
			{
				if ( wonja[k].boundary ) continue;
				if ( (wonja[k].y == yy) && (wonja[k].x == xx) )
				{
					wonja[k].boundary = 1;
					b_cnt++;
					total_energy += wonja[k].e;
				}
			}
		}
		chk[yy][xx] = 0;
	}
}

void Init(void)
{
	int i;

	for (i = 0; i <= N + 1; i++)
	{
		wonja[i] = (WONJA){ 0, 0, 0, 0, 0 };
	}
}

void Print_chk(void)
{
	int i, j;
	//printf("Print_chk\n");
	for (i = 0; i <= 4000; i++)
	{
		for (j = 0; j <= 4000; j++)
		{
			if (chk[i][j]) printf("y = %d, x = %d\n", i, j);
		}
	}
}
#endif
