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
int small[100010] = {};
int ans[100010] = {};
struct node
{
    int L, R;
    int sum;
};
node tree[400100];
void build(int root, int l, int r)
{
    tree[root].L = l;
    tree[root].R = r;
    tree[root].sum = r - l + 1;
    if (l == r)
        return;
    build(2 * root + 1, l, (l + r)/2);
    build(2 * root + 2, (l + r)/2 + 1, r);
    return;
}
int query(int root, int k)
{
    tree[root].sum -= 1;
    if (tree[root].L == tree[root].R)
    {
        return tree[root].L;
    }
    if (k <= tree[root * 2 + 1].sum)
    {
        return query(root * 2 + 1, k);
    }
    else
    {
        return query(root * 2 + 2, k - tree[root * 2 + 1].sum);
    }
    return 0;
}
int main()
{
    int N, i = 0, t = 0;
    scanf("%d", &N);
    small[1] = 0;
    build(0, 1, N);
    
    for (i = 2; i <= N; i++)
    {
        scanf("%d", &small[i]);
    }
    // int t = 0;
    for (i -= 1; i >= 1; i--)
    {
        t = query(0, small[i] + 1);
        ans[i] = t;
        // update(0, t);
    }
    for (int i = 1; i <= N; i++)
        printf("%d\n", ans[i]);
    return 0;
}
