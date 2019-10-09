// 20191009
// [BOJ. 17472] 다리 만들기2
#if 01
#include <stdio.h>
#define MAX     (15)
#define INF     (987654321)

typedef struct
{
        int y, x;
}NODE;
NODE Q[MAX * MAX * 2];

void Input(void);
void Island_Numbering(void);
void InQ(int yy, int xx);
NODE * OutQ(void);
void BFS_Island(int sy, int sx, int num);
void Prepare_Bridge(void);
void BFS_Constructing(int num);
void Construct_Bridge(void);
//void DFS_Bridge_Sum(int L, int s, int sum);
void Print(void);
void Print_Island(void);
void Print_chk(void);
void Print_Bridge(void);

int N, M;
int Map[MAX][MAX];
int Island[MAX][MAX];
int island_cnt;
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};
int Bridge[7][7];
int Visit[7][7];
int chk[7];
int Bridge_sum;
int Wp, Rp;

int main(void)
{
        Input();
        Island_Numbering();
        Prepare_Bridge();
        Construct_Bridge();
        Print();

        return 0;
}

void Input(void)
{
        int i, j;

        scanf("%d %d", &N, &M);
        for(i = 1; i <= N; i++)
        {
                for(j = 1; j <= M; j++)
                {
                        scanf("%d", &Map[i][j]);
                }
        }
}

void Island_Numbering(void)
{
        int i, j;

        island_cnt = 1;
        for(i = 1; i <= N; i++)
        {
                for(j = 1; j <= M; j++)
                {
                        if( Map[i][j] && !Island[i][j] )
                        {
                                BFS_Island(i, j, island_cnt);
                                island_cnt++;
                        }
                }
        }
}

void InQ(int yy, int xx)
{
        Q[Wp].y = yy;
        Q[Wp++].x = xx;
}

NODE * OutQ(void)
{
        return &(Q[Rp++]);
}

void BFS_Island(int sy, int sx, int num)
{
        NODE * out = (NODE *)0x0;
        int i, ny, nx;

        Wp = Rp = 0;
        InQ(sy, sx);
        Island[sy][sx] = num;
        while( Wp > Rp )
        {
                out = OutQ();
                sy = out->y;    sx = out->x;
                for(i = 0; i < 4; i++)
                {
                        ny = sy + dy[i];        nx = sx + dx[i];
                        if( ny < 1 || ny > N || nx < 1 || nx > M ) continue;
                        if( Map[ny][nx] && !Island[ny][nx] )
                        {
                                Island[ny][nx] = num;
                                InQ(ny, nx);
                        }
                }
        }
}

void Prepare_Bridge(void)
{
        int i, j;

        for(i = 1; i < island_cnt; i++)
        {
                BFS_Constructing(i);
        }
}

void BFS_Constructing(int num)
{
        int i, j;
        NODE * out = (NODE *)0x0;
        int sy, sx, ny, nx, dist;
        int out_flag = 0;

        Wp = Rp = 0;    // Q 크기 괜찮나?
        for(i = 1; i <= N; i++)
        {
                for(j = 1; j <= M; j++)
                {
                        if( Island[i][j] == num ) InQ(i, j);
                }
        }

        while( Wp > Rp )
        {
                out = OutQ();
                sy = out->y;    sx = out->x;
                for(i = 0; i < 4; i++)
                {
                        out_flag = 0;
                        ny = sy + dy[i];        nx = sx + dx[i];
                        for(dist = 1; ; dist++)
                        {
                                if( ny < 1 || ny > N || nx < 1 || nx > M )
                                {
                                        out_flag = 1;
                                        break;
                                }
                                if( Island[ny][nx] ) break;
                                ny += dy[i];    nx += dx[i];
                        }
                        if( out_flag || Island[ny][nx] == num ) continue;
                        if( dist - 1 >= 2 )
                        {
                                Bridge[num][Island[ny][nx]] = Bridge[Island[ny][nx]][num] = dist - 1;
                        }
                }
        }
}

void Construct_Bridge(void)
{
        /*
        int i;

        Bridge_sum = INF;
        for(i = 1; i < island_cnt; i++)
        {

                chk[i] = 1;
                DFS_Bridge_Sum(1, i, 0);
                chk[i] = 0;

        }
        */
}

/*
void DFS_Bridge_Sum(int L, int s, int sum)
{
        int i;

        printf("Depth = %d, start = %d, sum = %d\n", L, s, sum);
        if(L >= island_cnt)
        {
                if(Bridge_sum > sum) Bridge_sum = sum;
                return;
        }

        for(i = 1; i < island_cnt; i++)
        {
                if( !Bridge[s][i] || chk[i] ) continue;
                chk[i] = 1;
                //Visit[s][i] = Visit[i][s] = 1;
                DFS_Bridge_Sum(L + 1, i, sum + Bridge[s][i]);
                //Visit[s][i] = Visit[i][s] = 0;
                chk[i] = 0;
        }
}
*/

void Print(void)
{
        Print_Bridge();
        Print_Island();
        printf("%d\n", ((Bridge_sum == INF) ? -1 : Bridge_sum));
}

void Print_Island(void)
{
        int i, j;

        printf("\n");
        for(i = 1; i <= N; i++)
        {
                for(j = 1; j <= M; j++)
                {
                        printf("%d ", Island[i][j]);
                }
                printf("\n");
        }
        printf("\n");
}

void Print_chk(void)
{
        int i;

        printf("[chk] ");
        for(i = 1; i < island_cnt; i++) printf("%d ", chk[i]);
        printf("\n");
}

void Print_Bridge(void)
{
        int i, j;

        printf("\n");
        for(i = 1; i < island_cnt; i++)
        {
                for(j = 1; j < island_cnt; j++)
                {
                        printf("%2d ", Bridge[i][j]);
                }
                printf("\n");
        }
        printf("\n");
}
#endif
