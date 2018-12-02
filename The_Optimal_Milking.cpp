// http://dapractise.openjudge.cn/2018hw9/001/
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstdlib>
using namespace std;
#define inf 1 << 28
#define maxn 300

struct edge
{
    int u, v, next, f;
    edge(int u0 = 0, int v0 = 0, int f0 = 0, int next0 = 0)
    {
        u = u0, v = v0, f = f0, next = next0;
    }
} e[maxn * maxn];
int head[maxn * 2];
int visited[maxn * 2];
int path[maxn * 2];
int a[maxn][maxn];
int cnt, from, to, marked, K, C, M;

void adde(int u, int v, int f)
{
    e[cnt].u = u, e[cnt].v = v, e[cnt].f = f, e[cnt].next = head[u], head[u] = cnt++;
    e[cnt].u = v, e[cnt].v = u, e[cnt].f = 0, e[cnt].next = head[v], head[v] = cnt++;
}

void build(int x)
{
    cnt = 0;
    marked = 1;
    for (int i = 0; i <= to; i++)
    {
        head[i] = -1;
        visited[i] = 0;
    }
    for (int i = 1; i <= K; i++)
        adde(from, i, M);
    for (int i = K + 1; i <= K + C; i++)
        adde(i, to, 1);
    for (int i = 1; i <= K; i++)
    {
        for (int j = K + 1; j <= K + C; j++)
        {
            if (a[i][j] <= x)
                adde(i, j, 1);
        }
    }
}

bool bfs()
{
    int s = from, d;
    queue<int> q;
    q.push(s);
    marked++;
    visited[s] = marked;
    while (!q.empty())
    {
        s = q.front();
        q.pop();
        for (int i = head[s]; i != -1; i = e[i].next)
        {
            d = e[i].v;
            if (visited[d] != marked && e[i].f > 0)
            {
                visited[d] = marked;
                path[d] = i;
                q.push(d);
                if (d == to)
                    return true;
            }
        }
    }
    return false;
}

int maxf(int x)
{
    build(x);
    int maxflow = 0;
    while (bfs())
    {
        int offflow = inf;
        for (int i = to; i != from; i = e[path[i]].u)
        {
            offflow = min(e[path[i]].f, offflow);
        }
        for (int i = to; i != from; i = e[path[i]].u)
        {
            e[path[i]].f -= offflow;
            e[path[i] ^ 1].f += offflow;
        }
        maxflow += offflow;
    }
    return maxflow;
}

int main()
{
    while (cin >> K >> C >> M)
    {
        from = 0;
        to = K + C + 1;

        int c0, n = K + C;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                scanf("%d", &c0);
                if (c0 > 0)
                    a[i][j] = c0;
                else
                    a[i][j] = inf;
            }
        for (int k = 1; k <= n; k++)
        {
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    if (a[i][k] + a[k][j] < a[i][j])
                        a[i][j] = a[i][k] + a[k][j];
                }
            }
        }
        int l = 1, r = 200000;
        while (l < r)
        {
            int mid = (l + r) / 2;
            if (maxf(mid) >= C)
                r = mid;
            else
                l = mid + 1;
        }
        cout << r << endl;
    }
    return 0;
}