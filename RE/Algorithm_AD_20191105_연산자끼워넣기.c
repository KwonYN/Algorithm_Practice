// 20191105
// [BOJ.14888] 연산자 끼워넣기
#if 01
#include <stdio.h>
#define INF  (0x7fffffff)
#define INF2 (0x80000000)

void Input(void);
void DFS(int L);
void Calc_Result(void);

void Print_List(int L);

int N;
int num[15], op[5], List[15];
int max, min;

int main(void)
{
	freopen("in.txt", "r", stdin);
	Input();
	DFS(1);
	printf("%d\n%d\n", max, min);

	return 0;
}

void Input(void)
{
	int i;

	max = INF2;		min = INF;
	scanf("%d", &N);
	for (i = 0; i < N; i++) scanf("%d", &num[i]);
	for (i = 1; i <= 4; i++) scanf("%d", &op[i]);
}

void DFS(int L)
{
	int i;

	if (L > N - 1)
	{
		//Print_List(L);
		Calc_Result();
		//getch();
		return;
	}

	for (i = 1; i <= 4; i++)
	{
		if (op[i] == 0) continue;
		op[i]--;
		List[L] = i;
		DFS(L + 1);
		List[L] = 0;
		op[i]++;
	}
}

void Print_List(int L)
{
	int i;
	printf("Print_List\n");
	for (i = 1; i < L; i++)
	{
		printf("%d ", List[i]);
	}
	printf("\n");
}

void Calc_Result(void)
{
	int i, result = 0;
	int rmax = 0, rmin = INF;

	result = num[0];
	for (i = 1; i <= N - 1; i++)
	{
		switch (List[i])
		{
			case 1: result += num[i];
				break;
			case 2:result -= num[i];
				break;
			case 3:result *= num[i];
				break;
			default:result /= num[i];
				break;
		}
	}

	if (max < result) max = result;
	if (min > result) min = result;
}
#endif
