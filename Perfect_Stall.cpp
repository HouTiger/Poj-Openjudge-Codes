// http://dapractise.openjudge.cn/2018hw9/002/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define max 210
int g[max][max], v[max], connected[max];
int N, M;
int dfs(int floor)
{
    for (int i = 1; i <= M; ++i)
        if (!v[i] && g[floor][i])
        {
            v[i] = 1;
            if (connected[i] == -1 || dfs(connected[i]))
            {
                connected[i] = floor;
                return 1;
            }
        }
    return 0;
}

int main()
{
    int i, x;
    while (cin >> N >> M)
    {
        memset(g, 0, sizeof(g));
        for (i = 1; i <= N; ++i)
        {
            scanf("%d", &x);
            int p;
            while (x--)
            {
                scanf("%d", &p);
                g[i][p] = 1;
            }
        }
        int ans = 0;

        for (int i = 0; i < 210; i++)
        {

            connected[i] = ~0;
        }
        for (int i = 1; i <= N; ++i)
        {
            memset(v, 0, sizeof(v));
            if (dfs(i))
                ans += 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
