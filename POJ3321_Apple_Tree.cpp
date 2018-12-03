//
//  main.cpp
//  project3
//
//  Created by tiger on 2018/9/22.
//  Copyright © 2018年 tiger. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

vector<vector<int>> v(100005);// the vector of forks
bool a[100005] = {};
int c[100005] = {};
int start[100005] = {};
int tend[100005] = {};
int N;
void dfs(int x, int& cnt)
{
    start[x] = cnt;
    for (int i = 0; i < v[x].size(); i++)
    {
        cnt += 1;
        dfs(v[x][i], cnt);
    }
    tend[x] = cnt;
    return;
}
int LowBit(int n)
{
    return n & (-n);
}
int Cal_C(int n)// return c[n]
{
    int t1 = LowBit(n);
    int sum = 0;
    for (int i = n - t1 + 1; i <= n; i++)
    {
        sum += a[i];
    }
    return sum;
}
int Cal_Sum(int k)// calculate sum(k)
{
    
    int sum = 0;
    while(k > 0)
    {
        sum += c[k];
        k -= LowBit(k);
    }
    return sum;
}
void update(int n)
{
    // cout << "update n = " << n << endl;
    int carry = 0;
    if (a[n] == false)
        carry = 1;
    else
        carry = -1;
    a[n] = !a[n];
    // cout << "n = " << n << endl;
    while(true)
    {
        // cout << "n = " << n << endl;
        c[n] += carry;
        n = n + LowBit(n);
        if (n > N)
            break;
    }
    return;
}
int main()
{
    memset(a, 1, sizeof(a));
    
    cin >> N;
    int a, b;
    for (int i1 = 1; i1 <= N - 1; i1++)
    {
        scanf("%d%d", &a, &b);
        v[a].push_back(b);
    }
    int cnt = 1;
    dfs(1, cnt);
    
    for (int i2 = 1; i2 <= N; i2++)
    {
        c[i2] = Cal_C(i2);
    }
    // cout << "t1" << endl;
    int P;
    cin >> P;
    char ch;
    int t1;
    for (int i3 = 1; i3 <= P; i3++)
    {
        cin >> ch;
        if (ch == 'Q')
        {
            scanf("%d", &t1);
            printf("%d\n", Cal_Sum(tend[t1]) - Cal_Sum(start[t1] - 1));
        }
        else
        {
            scanf("%d", &t1);
            update(start[t1]);
        }
    }
    
    return 0;
}
