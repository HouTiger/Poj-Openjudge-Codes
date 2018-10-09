//
//  main.cpp
//  project3
//
//  Created by tiger on 2018/9/22.
//  Copyright © 2018年 tiger. All rights reserved.
//
// http://bailian.openjudge.cn/practice/2757/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int N;
class pairs
{
public:
    int value;
    int pos;
};
bool cop(pairs p1, pairs p2)
{
    if (p1.value != p2.value)
        return p1.value < p2.value;
    else
        return p1.pos > p2.pos;
    
}
int lowbit(int x)
{
    return x & (-x);
}
pairs a[300005] = {};
int c[300005] = {};// end in a[i - lowbit(i) + 1] to a[i]'s LIS
int lis[300005] = {};// end in a[i]'s LIS

int query(int x)
{
    int len = c[x];
    while(x > 0)
    {
        if (c[x] > len)
            len = c[x];
        x -= lowbit(x);
        
    }
    
    
    return len;
}

void update(int x)// which means lis[x] is longer
{
    int t = x;
    while(x <= N)
    {
        if (lis[t] > c[x])
            c[x] = lis[t];
        x += lowbit(x);
    }
    return;
}
int main()
{
    
    cin >> N;
    for (int i1 = 1; i1 <= N; i1++)
    {
        scanf("%d", &a[i1].value);
        a[i1].pos = i1;
        
    }
    sort(a + 1, a + N + 1, cop);// in the order of value, same value, pos bigger in front
    for (int i2 = 1; i2 <= N; i2++)
    {
        lis[a[i2].pos] = query(a[i2].pos) + 1;
        update(a[i2].pos);
        
    }
    int r = c[1];
    for (int i = 1; i <= N; i++)
    {
        if (c[i] > r)
            r = c[i];
    }
    
    printf("%d\n", r);
    
    return 0;
}
