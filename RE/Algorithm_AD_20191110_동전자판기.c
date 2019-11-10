// 20191110
// [문제 B8: [TST]동전 자판기(下)]
#if 01
#include <stdio.h>

void Input(void);
void DFS(int L, int cnt, int sum);
void Print(void);

int W;
int coin_cnt[8];
int coin[7] = { 0, 500, 100, 50, 10, 5, 1 };
int list[7];
int result_list[7];
int used_max_coin;

int main(void)
{
	freopen("in.txt", "r", stdin);
	Input();
	DFS(1, 0, 0);
	Print();

	return 0;
}

void Input(void)
{
	int i;

	used_max_coin = 0;
	scanf("%d", &W);
	for (i = 1; i <= 6; i++) scanf("%d", &coin_cnt[i]);
}

void DFS(int L, int cnt, int sum)
{
	int i, j;

	if (L > 6)
	{
		if (sum == W)
		{
			if (used_max_coin < cnt)
			{
				used_max_coin = cnt;
				for (j = 1; j <= 6; j++) result_list[j] = list[j];
			}
		}
		return;
	}

	for (i = 0; i <= coin_cnt[L]; i++)
	{
		if (sum + coin[L] * i > W) return;
		list[L] = i;
		DFS(L + 1, cnt + i, sum + coin[L] * i);
		list[L] = 0;
	}
}

void Print(void)
{
	int i;

	printf("%d\n", used_max_coin);
	for (i = 1; i <= 6; i++) printf("%d ", result_list[i]);
	printf("\n");
}
#endif


#if 0
#include <stdio.h>

void Input(void);
void DFS(int L, int cnt, int sum);
void Print(void);

int W, W_tmp;
int coin_cnt[8];
int coin[7] = { 0, 500, 100, 50, 10, 5, 1 };
int list[7];
int result_list[7];
int total_coin;
int keep_min_coin;

int main(void)
{
	freopen("in.txt", "r", stdin);
	Input();
	DFS(1, 0, W_tmp);
	Print();

	return 0;
}

void Input(void)
{
	int i, tmp;

	W_tmp = 0;
	total_coin = 0;
	keep_min_coin = 987654321;
	scanf("%d", &W);
	for (i = 1; i <= 6; i++)
	{
		scanf("%d", &tmp);
		total_coin += tmp;
		coin_cnt[i] = tmp;
		W_tmp += (coin[i] * tmp);
	}
	W_tmp -= W;
}


void DFS(int L, int cnt, int sum)
{
	int j, i, L_cnt;

	if (L > 6)
	{
		//for (j = 1; j <= 6; j++) printf("%d ", list[j]);
		//printf("\n");
		//getch();
		if (0 == sum)
		{
			if (keep_min_coin > cnt)
			{
				keep_min_coin = cnt;
				for (i = 1; i <= 6; i++) result_list[i] = list[i];
			}
		}
		return;
	}
	
	L_cnt = sum / coin[L];
	if (L_cnt > coin_cnt[L]) L_cnt = coin_cnt[L];
	list[L] = L_cnt;
	DFS(L + 1, cnt + L_cnt, sum - (L_cnt * coin[L]));
	list[L] = 0;
}


void Print(void)
{
	int i;

	printf("%d\n", total_coin - keep_min_coin);
	for (i = 1; i <= 6; i++) printf("%d ", coin_cnt[i] - result_list[i]);
	printf("\n");
}
#endif



#if 0
#include <stdio.h>

void Input(void);
void Operation(void);
void Print(void);

int W, W_tmp;
int coin_cnt[8];
int coin[7] = { 0, 500, 100, 50, 10, 5, 1 };
int total_coin;

int main(void)
{
	freopen("in.txt", "r", stdin);
	Input();
	Operation();
	Print();

	return 0;
}

void Input(void)
{
	int i, tmp;

	W_tmp = 0;
	total_coin = 0;
	scanf("%d", &W);
	for (i = 1; i <= 6; i++)
	{
		scanf("%d", &tmp);
		total_coin += tmp;
		coin_cnt[i] = tmp;
		W_tmp += (coin[i] * tmp);
	}
	W_tmp -= W;
}

void Operation(void)
{
	int i, i_cnt, total = 0;

	for (i = 1; i <= 6; i++)
	{
		i_cnt = W_tmp / coin[i];
		if (i_cnt > coin_cnt[i]) i_cnt = coin_cnt[i];
		W_tmp -= (i_cnt * coin[i]);
		coin_cnt[i] -= i_cnt;
		total_coin -= i_cnt;
	}
}

void Print(void)
{
	int i;

	printf("%d\n", total_coin);
	for (i = 1; i <= 6; i++) printf("%d ", coin_cnt[i]);
	printf("\n");
}
#endif
