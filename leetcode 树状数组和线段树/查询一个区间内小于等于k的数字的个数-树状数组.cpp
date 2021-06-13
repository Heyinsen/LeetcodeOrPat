// 本代码为查询区间内为小于h的数字的个数
// 改成等于h的数字的个数很简单
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAXM = 1e5 + 5;

struct Node
{
    int num, id;
    bool operator<(const Node nodes)
    { //按数值大小排序
        return num < nodes.num;
    }
} nodes[MAXM];

struct Query
{
    int l, r, h, id;
    bool operator<(const Query nodes)
    { //按h排序
        return h < nodes.h;
    }
} query[MAXM];

int c[MAXM];   //BIT
int res[MAXM]; //存答案
int n, m;
int cas = 1;

int lowbit(int i)
{
    return i & -i;
}

void add(int i, int x)
{
    while (i <= n)
    {
        c[i] += x;
        i += lowbit(i);
    }
}

int ask(int i)
{
    int ans = 0;
    while (i)
    {
        ans += c[i];
        i -= lowbit(i);
    }
    return ans;
}

void solve()
{
    printf("Case %d:\n", cas++);
    int last = 1;
    for (int i = 1; i <= m; i++)
    {
        while (query[i].h >= nodes[last].num && last <= n)
        {                       //把数值比h小的插入
            add(nodes[last].id, 1); //插入的是编号
            last++;
        }
        res[query[i].id] = ask(query[i].r) - ask(query[i].l - 1);
    }
    for (int i = 1; i <= m; i++)
    {
        printf("%d\n", res[i]);
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(c, 0, sizeof(c));
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &nodes[i].num);
            nodes[i].id = i;
        }
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d%d", &query[i].l, &query[i].r, &query[i].h);
            query[i].l++, query[i].r++; //题目区间从0开始，加1变为从1开始
            query[i].id = i;
        }
        sort(nodes + 1, nodes + 1 + n);
        sort(query + 1, query + 1 + m);
        solve();
    }
    return 0;
}