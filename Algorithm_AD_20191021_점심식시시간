// 20191021
// [SWEA. 2383] [모의 SW 역량테스트] 점심 식사시간
#if 01
#include <stdio.h>
#define INF	(987654321)
#define ABS(a)	( ( (a) < 0 ) ? -(a) : (a) )
#define DIST(a, b, c, d)	( (ABS( (a) - (b) )) + (ABS( (c) - (d) )) )

typedef struct { int y, x; }PERSON;
PERSON P[11];

typedef struct { int y, x, len; }STEP;
STEP S[3];

void Input(void);
void DFS(int L, int cnt_A, int cnt_B, int s_idx);
int Get_Time_A(int cnt_A);
int Get_Time_B(int cnt_B);
 void Print_List(int cnt_A, int cnt_B);

int T, N;
int Class[12][12];
int p_cnt, s_cnt;
int min_min;
int ListA[12], ListB[12];

int main(void)
{
	int i;

	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (i = 1; i <= T; i++)
	{
		Input();
		DFS(1, 0, 0, 1);
		printf("#%d %d\n", i, min_min);
	}

	return 0;
}

void Input(void)
{
	int i, j;

	min_min = INF;
	p_cnt = s_cnt = 0;
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			scanf("%d", &Class[i][j]);
			// 1. Input을 받으며 사람과 계단의 위치를 각 구조체에 넣어줌
			if (Class[i][j] == 1) P[++p_cnt] = (PERSON){ i, j }; 
			else if (Class[i][j] > 1) S[++s_cnt] = (STEP){ i, j, Class[i][j] };
		}
	}
}

// 2. DFS함수를 통해 (스스로 나눈) 계단 A와 계단 B로 조합을 이용하여 두 그룹으로 나눠줌
void DFS(int L, int cnt_A, int cnt_B, int s_idx)
{
	int i, rA, rB, max;

	// 2 - 3. 모든 사람이 두 계단으로 나눠 들어간다고 결정이 됐다면? 
	if (L > p_cnt)
	{
		/*
		Print_List(cnt_A, cnt_B);
		getch();
		*/

		// 3. 각 사람들의 도착시간, 계단 내려가는 시간을 통해 마지막 사람이 내려올 때까지의 시간을 구함
		rA = Get_Time_A(cnt_A);
		rB = Get_Time_B(cnt_B);
		// 4. 가장 늦게 내려온 사람을 구해야 함
		max = (rA < rB) ? rB : rA;
		// 5. 그것들 중 가장 최솟값을 구하면 됨!
		if (min_min > max) min_min = max;
		return;
	}

	for (i = s_idx; i <= p_cnt; i++)
	{
		// 2 - 1. 일단 A에 넣어보고
		ListA[++cnt_A] = i;
		DFS(L + 1, cnt_A, cnt_B, i + 1);
		ListA[cnt_A--] = 0;

		// 2 - 2. B에도 넣어봄
		ListB[++cnt_B] = i;
		DFS(L + 1, cnt_A, cnt_B, i + 1);
		ListB[cnt_B--] = 0;
	}
}

/*
	* stepA[] 배열은 사람들이 계단에 도착해서 내려가기 시작할 때까지의 시간(거리 + 1)을 담아놓은 배열임(idx == 시간, 배열 값 == 사람 수)
	* down_stair[]배열은 계단을 나타냄 (idx == 시간, 배열 값 == 사람 수)
*/
int Get_Time_A(int cnt_A)
{
	int i, j, tmp;
	int stepA[22] = { 0 };		// 3 - 1. N의 최대값이 10이므로, 계단에서 가장 먼 거리는 20이 됨. 1분 후 내려갈 수 있으니 최대 21!
	int down_stair[85] = { 0 };// 3 - 2. 있을 수 없는 일이지만, 사람 10명이 모두 한 계단으로 조합되었고, 모두 21의 거리를 가진다고 가정했을 때 
	int go_down, time;

	for (i = 1; i <= cnt_A; i++)
	{
		tmp = DIST(P[ListA[i]].y, S[1].y, P[ListA[i]].x, S[1].x) + 1;	// 3 - 3. 계단까지 도착해서 내려가기까지의 시간
		stepA[tmp]++;	// 3 - 4. 각 시간의 사람 수
	}

	time = 0;
	for (i = 1; i <= 21; i++)
	{
		//if (stepA[i] <= 0) continue;
		while (stepA[i] > 0)	// 3 - 5. 사람이 도착했다면, 
		{
			stepA[i]--;			// 그 사람을 계단에 올려
			go_down = S[1].len;	// 그 사람이 가야 할 계단(1칸에 1분, K칸에 K분. K분 후 다 내려가게 됨)
			// i분부터 계단을 내려가기 시작함! (계단이 총 K칸이라고 한다면, ★그 사람은 i + K분 후에는 마지막 계단 위에 있게 된다)
			for (j = i; j <= 84; j++)
			{
				if (down_stair[j] >= 3) continue;	// 그 시간에 계단에 몇 명인지? 3명까지 이므로 그 이후에 온 사람은 들어올 수 없음
				down_stair[j]++;					// 그 시간(i)를 기준으로 K만큼 내려가게 됨
				if (--go_down == 0)
				{
					if (time < j + 1) time = j + 1;			// 그 사람
					break;
				}
			}
		}
	}

	return time;
}

int Get_Time_B(int cnt_B)
{
	int i, j, tmp;
	int stepB[22] = { 0 };
	int down_stair[85] = { 0 };
	int go_down, time;

	for (i = 1; i <= cnt_B; i++)
	{
		tmp = DIST(P[ListB[i]].y, S[2].y, P[ListB[i]].x, S[2].x) + 1;	// 계단까지 도착해서 내려가기까지의 시간
		stepB[tmp]++;	// 각 시간의 사람 수
	}

	time = 0;
	for (i = 1; i <= 21; i++)
	{
		//if (stepB[i] <= 0) continue;
		while (stepB[i] > 0)
		{
			stepB[i]--;
			go_down = S[2].len;
			for (j = i; j <= 84; j++)
			{
				if (down_stair[j] >= 3) continue;
				down_stair[j]++;
				if (--go_down == 0)
				{
					if (time < j + 1) time = j + 1;
					break;
				}
			}
		}
	}

	return time;
}

void Print_List(int cnt_A, int cnt_B)
{
	int i;
	printf("Print_List\n");
	for (i = 1; i <= cnt_A; i++) printf("%d ", ListA[i]);
	printf("\n");
	for (i = 1; i <= cnt_B; i++) printf("%d ", ListB[i]);
	printf("\n");
}

#endif
