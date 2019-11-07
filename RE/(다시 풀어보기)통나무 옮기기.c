// 20191105
// [BOJ. 1938] 통나무 옮기기
#if 0
#include <stdio.h>
#define MAX	(60)
#define INF	(987654321)
#define U	(0)
#define D	(1)
#define L	(2)
#define R	(3)
#define T	(4)

typedef struct { int y, x; }TREE;
TREE tree[5];
TREE end[5];

void Input(void);
void DFS(int level);
int Check_9(int cs);
void Rotate_Tree(int cs);
void Move_Tree(int n);
int Check_Arr(void);
void Print_Map(void);
void Print_Trees(void);

int N;
int map[MAX][MAX];
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };
int dd[4] = { 1, 0, 3, 2 };
int tree_cnt;
int end_cnt;
int min_move;
int visit[4][MAX][MAX];

int main(void)
{
	freopen("in.txt", "r", stdin);
	Input();
	DFS(0);
	printf("%d\n", min_move);

	//Print_Map();

	return 0;
}

void Input(void)
{
	int i, j;
	char tmp[MAX];

	min_move = INF;
	tree_cnt = end_cnt = 0;
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		scanf("%s", &tmp[1]);
		for (j = 1; j <= N; j++)
		{
			if (tmp[j] == 'B')
			{
				tree[++tree_cnt] = (TREE){ i, j };
				map[i][j] = 0xb;
				visit[tree_cnt][i][j] = 1;
			}
			else if (tmp[j] == 'E')
			{
				end[++end_cnt] = (TREE){ i, j };
				map[i][j] = 0xe;
			}
			else if (tmp[j] == '1') map[i][j] = 1;
		}
	}
	for (i = 1; i <= N; i++) map[0][i] = map[i][0] = map[N + 1][i] = map[i][N + 1] = 1;
}

void DFS(int level)
{
	int i, t, rot, cs;
	int cont_flag = 0;

	Print_Trees();
	getch();

	if (Check_Arr())
	{
		if (min_move > level) min_move = level;
		return;
	}

	if (tree[1].x + 1 == tree[2].x)
	{
		cs = 0;
		rot = Check_9(cs);
	}
	else
	{
		cs = 1;
		rot = Check_9(cs);
	}
	if (rot)	// 회전
	{
		Rotate_Tree(cs);
		
		DFS(level + 1);
		
		Rotate_Tree(!cs);
	}

	for (i = 0; i < 4; i++)	// 사방
	{
		cont_flag = 0;
		switch (i)
		{
			case U:
				for (t = 1; t <= tree_cnt; t++)
				{
					if (map[tree[t].y - 1][tree[t].x] == 1)
					{
						cont_flag = 1;
						break;
					}
				}
				break;
			case D:
				for (t = 1; t <= tree_cnt; t++)
				{
					if (map[tree[t].y + 1][tree[t].x] == 1)
					{
						cont_flag = 1;
						break;
					}
				}
				break;
			case L:
				for (t = 1; t <= tree_cnt; t++)
				{
					if (map[tree[t].y][tree[t].x - 1] == 1)
					{
						cont_flag = 1;
						break;
					}
				}
				break;
			default:
				for (t = 1; t <= tree_cnt; t++)
				{
					if (map[tree[t].y][tree[t].x + 1] == 1)
					{
						cont_flag = 1;
						break;
					}
				}
				break;
		}
		if (cont_flag) continue;
		Move_Tree(i);

		DFS(level + 1);

		Move_Tree(dd[i]);
	}
}

void Move_Tree(int n)
{
	int i;

	switch (n)
	{
	case U:
		for (i = 1; i <= 3; i++) tree[i].y -= 1;
		break;
	case D:
		for (i = 1; i <= 3; i++) tree[i].y += 1;
		break;
	case L:
		for (i = 1; i <= 3; i++) tree[i].x -= 1;
		break;
	default:
		for (i = 1; i <= 3; i++) tree[i].x += 1;
		break;
	}
}

int Check_9(int cs)
{
	int i, j;

	if (cs == 1)// 가로로
	{
		for (i = tree[1].y - 1; i <= tree[1].y + 1; i += 2)
		{
			for (j = tree[1].x; j <= tree[1].x + 2; j++)
			{
				if (map[i][j] == 1) return 0;
			}
		}
	}
	else//세로로
	{
		for (i = tree[1].y; i <= tree[1].y + 2; i++)
		{
			for (j = tree[1].x - 1; j <= tree[1].x + 1; j += 2)
			{
				if (map[i][j] == 1) return 0;
			}
		}
	}
	return 1;
}

void Rotate_Tree(int cs)
{
	if (cs == 1)	// 가로로 있다는 뜻
	{
		tree[1].x++;	tree[1].y--;
		tree[3].x--;		tree[3].y++;
	}
	else
	{
		tree[1].x--;		tree[1].y++;
		tree[3].x++;	tree[3].y--;
	}
}

int Check_Arr(void)
{
	int i;

	for (i = 1; i <= 3; i++)
	{
		if (tree[i].y != end[i].y || tree[i].x != end[i].x) return 0;
	}
	return 1;
}

void Print_Map(void)
{
	int i, j;
	printf("Print_Map\n");
	for (i = 0; i <= N + 1; i++)
	{
		for (j = 0; j <= N + 1; j++)
		{
			printf("%2d ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void Print_Trees(void)
{
	int i;
	printf("Print_Trees\n");
	for (i = 1; i <= tree_cnt; i++)
	{
		printf("(y = %d, x = %d), ", tree[i].y, tree[i].x);
	}
	printf("\n");
	for (i = 1; i <= end_cnt; i++)
	{
		printf("(y = %d, x = %d), ", end[i].y, end[i].x);
	}
	printf("\n");
	printf("======================================\n");
}
#endif
