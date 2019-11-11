// 20191111
// [BOJ. 17471] 게리맨더링 (RE)

/*
    [ 교훈!! ]
    1. 단계를 나누어서 접근해야 함!!
    2. 비효율적이라도 한 번에 다 해야지!! 하는 마음은 접어야 함!!
    3. 다 풀고 50개의 테케가 통과한 다음에야 시간을 줄이든, 코드를 줄이든 할 수 있는 것!!
    4. DFS 사용할 때, 무조건 for문을 써야 한다는 강박에서 벗어나야 함!!
      - ↓ 방향은 정점의 개수
      - → 방향은 각 Level, Depth에서 도전해야 할 것의 개수 == TREE 구조 생각해보았을 때, Yes/No인지, 여러 가지 경우의 수가 있는지 꼭 생각!
      - 특히 팀을 나눌 때는, 각 Level에서 팀의 개수만큼 DFS호출해주면 됨!
        == A팀에 넣어보고, B팀에 넣어보고, C팀에 넣어보고!!
          ( 단, 주의해야 할 것이 내가 임의로 A, B, C조라는 이름을 붙여서 나눈 것이지,
            문제 내에서 세 팀으로 나누기만 하면 됐지, 조의 이름이 상관이 없다면,
            그냥 끝까지 보내는 것은 같은 경우를 여러 번 체크하는 경우도 생기기 때문에 항상 주의!!!!!
            ex. 두 팀으로 나눈다고 가정했을 때,
                "1 / 2 3 4 5 6" 이나 "2 3 4 5 6 / 1"이나 완전히 똑같은 경우게찌!?!?!?!? )
*/

#if 01
#include <stdio.h>
#define MAX	(15)
#define INF	(987654321)
#define ABS(a)	( ( (a) < 0 ) ? -(a) : (a) )

void Input(void);
void DFS(int L, int cnt_A, int cnt_B);
int BFS_A(int s, int cnt_A);
int BFS_B(int s, int cnt_B);
void Init_visit(void);
void Print(void);
void Init(void);

void Print_injub(void);
void Print_list(int cnt_A, int cnt_B);
void Print_visit(void);

int T, N;
int pop[MAX];
int injub[MAX][MAX];
int visit_A[MAX], visit_B[MAX];
int list_A[MAX], list_B[MAX];
int queue[MAX];
int wp, rp;
int min_diff;

int main(void)
{
	int i;

	freopen("in.txt", "r", stdin);
	//scanf("%d", &T);
	T = 1;
	for (i = 1; i <= T; i++)
	{
		Input();
		DFS(1, 0, 0);
		Print();
		//Print_injub();
		Init();
	}

	return 0;
}

void Input(void)
{
	int i, j, cnt, tmp;

	min_diff = INF;
	scanf("%d", &N);
	for (i = 1; i <= N; i++) scanf("%d", &pop[i]);
	for (i = 1; i <= N; i++)
	{
		scanf("%d", &cnt);
		for (j = 1; j <= cnt; j++)
		{
			scanf("%d", &tmp);
			injub[i][tmp] = 1;
		}
	}
}

void DFS(int L, int cnt_A, int cnt_B)
{
	int rA, rB, rr = 0;

	if (min_diff == 0) return;
	if (cnt_B > N / 2) return;	// 이 조건이 없다면, "1 / 2 3 4 5 6"과 "2 3 4 5 6 / 1"은 다른 경우가 되어 버린다!!
						// 사실 내가 임의적으로 A, B조로 나눈 것이지, 실제로는 그냥 "두 그룹"으로 나누는 것이기 때문!!
	if (L > N)
	{
		if (cnt_A == 0 || cnt_B == 0) return;
		//Print_list(cnt_A, cnt_B);
		//getch();

		Init_visit();
		rA = BFS_A(list_A[1], cnt_A);
		rB = BFS_B(list_B[1], cnt_B);
		if (rA && rB)
		{
			rr = ABS(rA - rB);
			if (min_diff > rr) min_diff = rr;
			//Print_visit();
		}
		//printf("min_diff = %d, rr = %d\n", min_diff, rr);
		//getch();
		return;
	}

	list_A[++cnt_A] = L;
	DFS(L + 1, cnt_A, cnt_B);
	list_A[cnt_A--] = 0;

	list_B[++cnt_B] = L;
	DFS(L + 1, cnt_A, cnt_B);
	list_B[cnt_B--] = 0;
}

int BFS_A(int s, int cnt_A)
{
	int i, out, sum = 0;

	for (i = 1; i <= cnt_A; i++)
	{
		visit_A[list_A[i]] = -1;
	}

	wp = rp = 0;
	queue[wp++] = s;
	visit_A[s] = 0;
	sum = pop[s];
	while (wp > rp)
	{
		out = queue[rp++];
		for (i = 1; i <= N; i++)
		{
			if (injub[out][i] && visit_A[i] == -1)
			{
				queue[wp++] = i;
				visit_A[i] = 0;
				sum += pop[i];
			}
		}
	}

	for (i = 1; i <= N; i++)
	{
		if (visit_A[i] != 0) return 0;
	}

	return sum;
}

int BFS_B(int s, int cnt_B)
{
	int i, out, sum = 0;

	for (i = 1; i <= cnt_B; i++)
	{
		visit_B[list_B[i]] = -1;
	}

	wp = rp = 0;
	queue[wp++] = s;
	visit_B[s] = 0;
	sum = pop[s];
	while (wp > rp)
	{
		out = queue[rp++];
		for (i = 1; i <= N; i++)
		{
			if (injub[out][i] && visit_B[i] == -1)
			{
				queue[wp++] = i;
				visit_B[i] = 0;
				sum += pop[i];
			}
		}
	}

	for (i = 1; i <= N; i++)
	{
		if (visit_B[i] != 0) return 0;
	}

	return sum;
}

void Print(void)
{
	if (min_diff == INF) min_diff = -1;
	printf("%d\n", min_diff);
}

void Init_visit(void)
{
	int i;
	for (i = 1; i <= N; i++) visit_A[i] = visit_B[i] = 0;
}

void Init(void)
{
	int i, j;

	for (i = 0; i <= N + 1; i++) pop[i] = 0;
	for (i = 0; i <= N + 1; i++) for (j = 0; j <= N + 1; j++) injub[i][j] = 0;
}

void Print_injub(void)
{
	int i, j;
	printf("Print_injub\n");
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			printf("%d ", injub[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void Print_list(int cnt_A, int cnt_B)
{
	int i;
	printf("Print_list\n");
	printf("[list_A]");
	for (i = 1; i <= cnt_A; i++) printf("%d ", list_A[i]);
	printf("\n");
	printf("[list_B]");
	for (i = 1; i <= cnt_B; i++) printf("%d ", list_B[i]);
	printf("\n");
}

void Print_visit(void)
{
	int i;
	printf("Print_visit\n");
	printf("[visit_A]");
	for (i = 1; i <= N; i++) printf("%d ", visit_A[i]);
	printf("\n");
	printf("[visit_B]");
	for (i = 1; i <= N; i++) printf("%d ", visit_B[i]);
	printf("\n");
}
#endif
