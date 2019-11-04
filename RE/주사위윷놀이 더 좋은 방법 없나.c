#if 0
#include <stdio.h>
#define R	(0)
#define B	(1)

typedef struct { int route, idx; }HORSE;
HORSE List[7];

void Input(void);
void DFS(int L, int horse_no, int score);
int Same_Place(int horse_no);

int dice_num[12];
int Map[4][28] = 
{
	{0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 0, 0, 0, 0, 0, },
	{0, 2, 4, 6, 8, 10, 13, 16, 19, 25, 30, 35, 40, },
	{0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 25, 30, 35, 40, },
	{0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 28, 27, 26, 25, 30, 35, 40, 0, 0, 0, 0, 0}
};
int max_score;

int main(void)
{
	freopen("in.txt", "r", stdin);
	Input();
	DFS(1, 1, 0);
	printf("%d\n", max_score);

	return 0;
}

void Input(void)
{
	int i;

	max_score = 0;
	for (i = 1; i <= 10; i++)
	{
		dice_num[i] = 0;
		scanf("%d", &dice_num[i]);
	}
	for (i = 1; i <= 4; i++) List[i].route = List[i].idx = 0;
}

void DFS(int L, int horse_no, int score)
{
	HORSE prev = (HORSE){ 0, 0 };
	int check;

	/*
	printf("===============================================================\n");
	getch();
	printf("[%d] 현재까지의 score = %d\n", L, score);
	printf("horse_no = %d\n", horse_no);
	printf("얘는 현재 route = %d, idx = %d ==> num = %d에 있음\n", List[horse_no].route, List[horse_no].idx, Map[List[horse_no].route][List[horse_no].idx]);
	printf("			▼\n");
	printf("dice_num[%d] = %d칸만큼 간다면!?\n", L, dice_num[L]);
	printf("			▼\n");
	*/
	

	if ( L > 10 )
	{
		if (max_score < score) max_score = score;
		return;
	}

	prev = List[horse_no];
	check = Map[prev.route][prev.idx + dice_num[L]];
	if (check != 0)
	{
		if (prev.route == 0 && check % 10 == 0 && check != 40) List[horse_no].route = check / 10;
		List[horse_no].idx += dice_num[L];
		if (Same_Place(horse_no) == 0)
		{
			DFS(L + 1, horse_no, score + check);
		}
		List[horse_no] = prev;
	}
	if (horse_no < 4) DFS(L, horse_no + 1, score);
}

int Same_Place(int horse_no)
{
	int i;

	for (i = 1; i <= 4; i++)
	{
		if (i == horse_no || List[i].idx == 0) continue;
		if (List[i].route == List[horse_no].route && List[i].idx == List[horse_no].idx) return 1;
	}
	return 0;
}
#endif
