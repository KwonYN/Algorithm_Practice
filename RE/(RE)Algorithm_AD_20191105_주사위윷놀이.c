
#if 01
#include <stdio.h>

void Input(void);
void Operation(void);
int Get_Score(int c);
void Init_Visit(void);

int dice_num[12];
int score_set[33] = { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40,
					13, 16, 19, 22, 24, 28, 27, 26, 25, 30, 35, 0 };	// 그 위치에서 얻을 수 있는 점수
int visit[33];
int horse[4];
int map_step[33][6] = 
{
	{ 0, 1, 2, 3, 4, 5 },
	{ 1, 2, 3, 4, 5, 6 },
	{ 2, 3, 4, 5, 6, 7 },
	{ 3, 4, 5, 6, 7, 8 },
	{ 4, 5, 6, 7, 8, 9 },
	{ 5, 21, 22, 23, 29, 30 },
	{ 6, 7, 8, 9, 10, 11 },
	{ 7, 8, 9, 10, 11, 12 },
	{ 8, 9, 10, 11, 12, 13 },
	{ 9, 10, 11, 12, 13, 14 },
	{ 10, 24, 25, 29, 30, 31 },
	{ 11, 12, 13, 14, 15, 16 },
	{ 12, 13, 14, 15, 16, 17 },
	{ 13, 14, 15, 16, 17, 18 },
	{ 14, 15, 16, 17, 18, 19 },
	{ 15, 26, 27, 28, 29, 30 },
	{ 16, 17, 18, 19, 20, 32 },
	{ 17, 18, 19, 20, 32, 32 },
	{ 18, 19, 20, 32, 32, 32 },
	{ 19, 20, 32, 32, 32, 32 },
	{ 20, 32, 32, 32, 32, 32 },
	{ 21, 22, 23, 29, 30, 31 },
	{ 22, 23, 29, 30, 31, 20 },
	{ 23, 29, 30, 31, 20, 32 },
	{ 24, 25, 29, 30, 31, 20 },
	{ 25, 29, 30, 31, 20, 32 },
	{ 26, 27, 28, 29, 30, 31 },
	{ 27, 28, 29, 30, 31, 20 },
	{ 28, 29, 30, 31, 20, 32 },
	{ 29, 30, 31, 20, 32, 32 },
	{ 30, 31, 20, 32, 32, 32 },
	{ 31, 20, 32, 32, 32, 32 },
	{ 32, 32, 32, 32, 32, 32 },
};
int max_score;

int main(void)
{
	freopen("in.txt", "r", stdin);
	Input();
	Operation();
	printf("%d\n", max_score);

	return 0;
}

void Input(void)
{
	int i;

	for (i = 0; i < 10; i++)
	{
		dice_num[i] = 0;
		scanf("%d", &dice_num[i]);
	}
}

void Operation(void)
{
	int i, r;

	max_score = 0;
	for (i = 0; i < (1 << 20); i++)
	{
		Init_Visit();
		horse[0] = horse[1] = horse[2] = horse[3] = 0;
		r = Get_Score(i);
		if (max_score < r) max_score = r;
	}
}

int Get_Score(int c)
{
	int i, horse_no, score, step, s, e;

	score = step = 0;
	for (i = 0; i < 10; i++)
	{
		horse_no = (c >> (i * 2)) & 0x3;
		s = horse[horse_no];	// 위치
		step = dice_num[i];
		e = map_step[horse[horse_no]][step];	// 위치
		if ( visit[e] && score_set[e] != 0 ) return;
		horse[horse_no] = e;
		visit[s]--;
		visit[e]++;
		score += score_set[e];
	}

	return score;
}

void Init_Visit(void)
{
	int i;
	visit[0] = 4;
	for (i = 1; i <= 32; i++) visit[i] = 0;
}
#endif
