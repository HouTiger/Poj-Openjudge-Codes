//
//  main.cpp
//  project3
//
//  Created by tiger on 2018/9/22.
//  Copyright © 2018年 tiger. All rights reserved.
//

#include <iostream>
#include <cstdio>
using namespace std;
int S;
int a[1030][1030] = {};
int c[1030][1030] = {};
int lowbit(int x)
{
    return x & (-x);
}

void update(int x, int y, int carry)// start from a[1][1]
{
    for (int i = x; i <= S; i += (i & (-i)))
    {
        for (int j = y; j <= S; j += (j & (-j)))
        {
            c[i][j] += carry;
        }
    }
    return;
}

int cal_sum(int x, int y)// start from a[1][1]
{
    int re = 0;
    for (int i = x; i > 0; i -= (i & (-i)))
    {
        for (int j = y; j > 0; j -= (j & (-j)))
        {
            re += c[i][j];
        }
    }
    return re;
}

int main()
{
    cin >> S >> S;
    int p;// insturction code
    int a1, a2, a3, a4;
    while(true)
    {
        cin >> p;
        if (p == 3)
            break;
        if (p == 1)
        {
            scanf("%d%d%d", &a1, &a2, &a3);//
            a[a1 + 1][a2 + 1] += a3;
            update(a1 + 1, a2 + 1, a3);
            // cout << "c[a1 + 1][a2 + 1] = " << c[a1 + 1][a2 + 1] << endl;
        }
        else
        {
            scanf("%d%d%d%d", &a1, &a2, &a3, &a4);
            int t1 = cal_sum(a3 + 1, a4 + 1);
            int t2 = cal_sum(a1, a2);
            int t3 = cal_sum(a1, a4 + 1);
            int t4 = cal_sum(a3 + 1, a2);
            // cout << "ts = " << t1 << ' ' << t2 << ' ' << t3 << ' ' << t4 << endl;
            int result = t1 + t2 - t3 - t4;
            printf("%d\n", result);
            
        }
    }
    
    
    return 0;
}
