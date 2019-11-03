#include <stdio.h>
#define R	(0)
#define B	(1)

typedef struct { int prev, now, RB; }HORSE;
HORSE List[7];

void Input(void);
void DFS(int L, int horse_no, int score);
HORSE getNum(int horse_no, int cnt);

int dice_num[12];
int AllR[26] = { 1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 0, 0, 0, 0, 0 };
int B_10[6] = { 0, 13, 16, 19, 25, 30 };
int B_13[6] = { 0, 16, 19, 25, 30, 35 };
int B_16[6] = { 0, 19, 25, 30, 35, 40 };
int B_19[6] = { 0, 25, 30, 35, 40, 0 };
int B_20[6] = { 0, 22, 24, 25, 30, 35 };
int B_22[6] = { 0, 24, 25, 30, 35, 40 };
int B_24[6] = { 0, 25, 30, 35, 40, 0 };
int B_25[6] = { 0, 30, 35, 40, 0, 0 };
int B_30[6] = { 0, 28, 27, 26, 25, 30 };
int B_28[6] = { 0, 27, 26, 25, 30, 35 };
int B_27[6] = { 0, 26, 25, 30, 35, 40 };
int B_26[6] = { 0, 25, 30, 35, 40, 0 };
int R_30[6] = { 0, 35, 40, 0, 0, 0 };
int R_35[6] = { 0, 40, 0, 0, 0, 0 };
int max_score;

int main(void)
{
	Input();
	DFS(1, 0, 0);
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
	for (i = 1; i <= 4; i++)
	{
		List[i].now = AllR[0];	// 1 : 시작점이라는 뜻, 0 : 도착점이라는 뜻
		List[i].RB = R;	// 시작점에서의 방향은 Red Arrow
	}
}

void DFS(int L, int horse_no, int score)
{
	int i;
	HORSE tmp = (HORSE){ 0, 0, 0 };
	
	/*
	printf("[L = %d] next_score = %d\n", L, score);
	printf("======================================================\n");	
	*/

	if (L > 10)
	{
		if (max_score < score) max_score = score;
		return;
	}

	/*
	printf("L = %d, horse_no = %d, prev = %d, RB = %d, now = %d, now_score = %d\n", L, horse_no,
		List[horse_no].prev, List[horse_no].RB, List[horse_no].now, score);
	printf("현재 말%d의 상태! : prev = %d, dir = %d, now = %d\n", horse_no, List[horse_no].prev,
		List[horse_no].RB, List[horse_no].now);
	printf("dice_num[%d] = %d이라서 %d칸 가야 함!\n", L, dice_num[L], dice_num[L]);
	printf("			▼\n");
	getch();
	*/

	for (i = 1; i <= 4; i++)
	{
		if (List[i].now != 0)	// "도착"해서 더 이상 가지 못하는 상태가 아니라면!
		{
			tmp = List[i];
			List[i] = getNum(i, dice_num[L]);// i번째 말이 L번째로 주어진 주사위 숫자 dice_num[L]만큼 갈 수 있나, 갈 수 있으면 그만큼 가게끔 하는 함수
			if (List[i].now != -1)			 // 그런데 이미 그 곳에 말이 있어서 가지 못하는 상태가 아니라면 가자!
			{
				DFS(L + 1, i, score + List[i].now);
			}
			List[i] = tmp;
		}
	}
}

HORSE getNum(int horse_no, int cnt)
{
	int i;
	HORSE result = (HORSE) { 0, 0, 0 };

	result.prev = List[horse_no].now;
	if (List[horse_no].RB == R)
	{
		if (result.prev == 30)
		{
			result.now = R_30[cnt];
			result.RB = List[horse_no].RB;
		}
		else if (result.prev == 35)
		{
			result.now = R_35[cnt];
			result.RB = List[horse_no].RB;
		}
		else
		{
			result.now = AllR[ (result.prev / 2) + cnt ];
			if ( result.now == 10 || result.now == 20 || result.now == 30 ) result.RB = B;
			else result.RB = List[horse_no].RB;
		}
	}
	else if(List[horse_no].RB == B)
	{
		switch ( result.prev )
		{
		case 10:
			result.now = B_10[cnt];
			if (result.now >= 30) result.RB = R;
			else result.RB = List[horse_no].RB;
			break;
		case 13:
			result.now = B_13[cnt];
			if (result.now >= 30) result.RB = R;
			else result.RB = List[horse_no].RB;
			break;
		case 16:
			result.now = B_16[cnt];
			if (result.now >= 30) result.RB = R;
			else result.RB = List[horse_no].RB;
			break;
		case 19:
			result.now = B_19[cnt];
			if (result.now >= 30) result.RB = R;
			else result.RB = List[horse_no].RB;
			break;
		case 20:
			result.now = B_20[cnt];
			if (result.now >= 30) result.RB = R;
			else result.RB = List[horse_no].RB;
			break;
		case 22:
			result.now = B_22[cnt];
			if (result.now >= 30) result.RB = R;
			else result.RB = List[horse_no].RB;
			break;
		case 24:
			result.now = B_24[cnt];
			if (result.now >= 30) result.RB = R;
			else result.RB = List[horse_no].RB;
			break;
		case 25:
			result.now = B_25[cnt];
			result.RB = R;
			break;
		case 30: // B랑 R 둘 다 있음..!
			result.now = B_30[cnt];
			if (result.now >= 30) result.RB = R;
			else result.RB = List[horse_no].RB;
			break;
		case 28:
			result.now = B_28[cnt];
			if (result.now >= 30) result.RB = R;
			else result.RB = List[horse_no].RB;
			break;
		case 27:
			result.now = B_27[cnt];
			if (result.now >= 30) result.RB = R;
			else result.RB = List[horse_no].RB;
			break;
		case 26:
			result.now = B_26[cnt];
			if (result.now >= 30) result.RB = R;
			else result.RB = List[horse_no].RB;
			break;
		default: // 필요한가?
			break;
		}
	}
	for (i = 1; i <= 4; i++)
	{
		if (i == horse_no) continue;
		if ( List[i].now == result.now && List[i].RB == result.RB )
		{
			if (result.now != 1 && result.now != 0) return (HORSE){ -1, -1, -1 };
		}
	}
	return result;
}
