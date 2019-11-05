// 20191105
// [BOJ. 17829] 222-풀링
#if 01
#include <stdio.h>
#define MAX	(1100)

void Set_Data(void);
void Input(void);
void Operation(void);

int get_cnt[MAX];
int get_last[11] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };
int N, n;
int map[MAX][MAX];

int main(void)
{
	freopen("in.txt", "r", stdin);
	Set_Data();
	Input();
	Operation();
	printf("%d\n", map[1][1]);

	return 0;
}

void Set_Data(void)
{
	int i, cnt;
	for (cnt = 0, i = 1; i <= 1024; cnt++, i *= 2) get_cnt[i] = cnt;
}

void Input(void)
{
	int i, j;

	scanf("%d", &N);
	n = get_cnt[N];
	for (i = 1; i <= N; i++) for (j = 1; j <= N; j++) scanf("%d", &map[i][j]);
}

void Operation(void)
{
	int i, r, c, y, x, tmp;
	int last;
	int comp[6] = { 0 };

	for (i = n; i >= 0; i--)
	{
		last = get_last[i] - 1;
		for (r = 1; r <= last; r += 2)
		{
			for (c = 1; c <= last; c += 2)
			{
				comp[1] = map[r][c];
				comp[2] = map[r + 1][c];
				comp[3] = map[r][c + 1];
				comp[4] = map[r + 1][c + 1];
				for (y = 1; y < 4; y++)
				{
					for (x = y + 1; x <= 4; x++)
					{
						if (comp[y] < comp[x])
						{
							tmp = comp[x];
							comp[x] = comp[y];
							comp[y] = tmp;
						}
					}
				}
				map[(r + 1)/2][(c + 1)/2] = comp[2];
			}
		}
	}
}
#endif
