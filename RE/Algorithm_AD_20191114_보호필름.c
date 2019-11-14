// 20191114
// [SWEA. 2112] 보호 필름
#if 01
#include <stdio.h>
#define	A	(0)
#define	B	(1)

void Input(void);
void DFS(int L, int s_idx, int cnt);
void Copy_film(int L, int d);
void Set_film(int d, int flag);
int Test_film(void);
void Reverse_film(int L, int d);


void Print_film(void);

int T, D, W, K;
int film[15][25];
int cpy[15][25];
int min_cnt;
int end_flag;

int main(void)
{
	int i, j;

	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (i = 1; i <= T; i++)
	{
		Input();
		for (j = 0; j <= D; j++)
		{
			DFS(1, 1, j);
			if (end_flag) break;
		}
		printf("#%d %d\n", i, min_cnt);
	}

	return 0;
}

void Input(void)
{
	int i, j;

	end_flag = 0;
	min_cnt = 987654321;
	scanf("%d %d %d", &D, &W, &K);
	for (i = 1; i <= D; i++)
	{
		for (j = 1; j <= W; j++)
		{
			film[i][j] = 0;
			scanf("%d", &film[i][j]);
		}
	}
}

void DFS(int L, int s_idx, int cnt)
{
	int i;

	if (end_flag) return;
	if (L > cnt)
	{
		/*
		printf("[%d]\n", L);
		Print_film();
		*/
		
		if (Test_film())
		{
			min_cnt = cnt;
			end_flag = 1;
		}
		/*
		printf("min_cnt = %d\n", min_cnt);
		getch();
		*/

		return;
	}

	for (i = s_idx; i <= D; i++)
	{
		Copy_film(L, i);
		Set_film(i, A);
		DFS(L + 1, i + 1, cnt);
		Set_film(i, B);
		DFS(L + 1, i + 1, cnt);
		Reverse_film(L, i);
	}
}

void Copy_film(int L, int d)
{
	int i;
	for (i = 1; i <= W; i++) cpy[L][i] = film[d][i];
}

void Set_film(int d, int flag)
{
	int i;
	for (i = 1; i <= W; i++) film[d][i] = flag;
}

void Reverse_film(int L, int d)
{
	int i;
	for (i = 1; i <= W; i++) film[d][i] = cpy[L][i];
}

int Test_film(void)
{
	int i, j;
	int cnt = 0;
	int prev, flag = 0;
	
	for (j = 1; j <= W; j++)
	{
		flag = 0;
		prev = film[1][j];	cnt = 1;
		for (i = 2; i <= D; i++)
		{
			if (prev == film[i][j]) cnt++;
			else
			{
				prev = film[i][j];
				cnt = 1;
			}
			if (cnt >= K)
			{
				flag = 1;	break;
			}
		}
		if (!flag) return 0;
	}
	return 1;
}

void Print_film(void)
{
	int i, j;
	printf("Print_film\n");
	for (i = 1; i <= D; i++)
	{
		for (j = 1; j <= W; j++)
		{
			printf("%c ", (film[i][j] == 0) ? 'A' : 'B');
		}
		printf("\n");
	}
	printf("\n");
}
#endif
