#if 01 
#include <stdio.h> 

int Map[22][22]; 
int N; 
int min; 

void Input(void)
{
	int i, j; 

	scanf("%d", &N); 
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			scanf("%d", &Map[i][j]); 
		}
	}
	min = 0x7ffffff; 
}

void Calc_Min(void)
{
	int i, j; 
	int l, r; 
	int sol; 
	int M = N/2; 

	for (i = 1; i <= N; i++)
	{
		for (j = 2; j < N; j++)
		{
			for (l = 1; l <= M; l++)
			{
				if (i + l < 1 || j + l > N) break; 
				for (r = 1; r <= M; r++)
				{
					if (i + r > N || j + r > N) break; 
					sol = Make_SGG(i, j, l, r); 
					if (sol != -1 && sol < min) min = sol; 
				}
			}
		}
	}
}

int Make_SGG(int y, int x, int l, int r)
{
	int i, j; 
	int left, right; 
	int Chk[22][22] = {0};
	int sum[6] = {0};

	int ny = y + r + l; 
	int nx = x + r - l; 
	
	//printf("%d %d\n", y, x); 
	if (ny > N || nx > N || nx < 1) return -1; 

	left = x + 1, right = x -1; 
	for (i = y; i <= ny; i++)
	{
		if (i - y <= l) left--; 
		else left++; 
		if (i - y <= r) right++; 
		else right--; 
		for (j = left; j <= right; j++)
		{
			Chk[i][j] = 1; 
		}
	}


	right = x; 
	for (i = 1; i < y + l; i++)
	{
		if (i >= y) --right; 
		for (j = 1; j <= right; j++)
		{
			Chk[i][j] = 2; 
		}
	}

	left = x + 1; 
	for (i = 1; i <= y + r; i++)
	{
		if (i > y) ++left; 
		for (j = left; j <= N; j++)
		{
			Chk[i][j] = 3; 
		}
	}

	right = x - l - 2; 
	for (i = y + l; i <= N; i++)
	{
		if (i <= ny) right++; 
		else right = nx-1; 
		for (j = 1; j <= right; j++)
		{
			Chk[i][j] = 4; 
		}
	}

	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			sum[Chk[i][j]] += Map[i][j]; 
		}
	}

	int temp; 
	for (i = 0; i < 4; i++)
	{
		for (j = i + 1; j <= 4; j++)
		{
			if (sum[i] > sum[j])
			{
				temp = sum[i];
				sum[i] = sum[j];
				sum[j] = temp;
			}
		}
	}

	return sum[4] - sum[0]; 
}

int main(void)
{
	Input(); 
	Calc_Min(); 
	printf("%d\n", min); 
}

#endif 
