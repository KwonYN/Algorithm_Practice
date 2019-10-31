// 20191030
// [BOJ. 9466] 텀 프로젝트

/*
    예를 들어.
    1 -> 5 -> 2 -> 54 -> 24 -> 4 -> 7 -> 54일 때(즉, 7이 54를 가리켜서 DFS로 한 깊이 더 들어갔는데 걔가 이미 방문이 되어있다면?)
    그 때, List[1]에서부터 List[L]까지 기록해준 List 배열을 1 ~ L - 1까지 마지막 수였던, 그리고 이미 방문했던 "54"인지 찾는다.
    만날 때까지 cnt = 0;에서 ++로 증가시켜준다.
    여기에서는 54를 만날 때까지 cnt는 3이므로, 이 세 명은 팀을 구할 수 없게 된다.
    이 cnt를 리턴해주고, 이는 최종 결과값(초기 : 0)에 계속 더해준다!
    이 때, DFS에서는 Visit은 0으로 초기화시켜주지 않는다!
*/

#if 01
#include <stdio.h>
#define MAX	(100050)

void Input(void);
void DFS(int L, int s);
int getCnt(int L, int e);
void Init_Visit(void);

int T, N;
int want[MAX];
int Visit[MAX];
int List[MAX];
int wangdda;

int main(void)
{
	int i, j;

	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (i = 1; i <= T; i++)
	{
		Input();
		for (j = 1; j <= N; j++)
		{
			if (Visit[j]) continue;
			DFS(1, j);
		}
		printf("%d\n", wangdda);
		Init_Visit();
	}

	return 0;
}

void Input(void)
{
	int i;

	wangdda = 0;
	scanf("%d", &N);
	for (i = 1; i <= N; i++) scanf("%d", &want[i]);
}

void DFS(int L, int s)
{
	int r;

	if (Visit[s])
	{
		r = getCnt(L, s);
		wangdda += r;
		return;
	}
	Visit[s] = 1;		List[L] = s;
	DFS( L + 1, want[s] );
	List[L] = 0;
}

int getCnt(int L, int e)
{
	int i, cnt = 0;

	for (i = 1; i < L; i++)
	{
		if (List[i] == e) break;
		cnt++;
	}

	return cnt;
}

void Init_Visit(void)
{
	int i;

	for (i = 1; i <= N; i++) Visit[i] = 0;
}
#endif
