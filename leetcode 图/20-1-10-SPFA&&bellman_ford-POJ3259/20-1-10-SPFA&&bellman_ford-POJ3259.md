SPFA算法介绍](https://blog.csdn.net/strve/article/details/80957491)

## poj3259

Wormholes

| **Time Limit:** 2000MS       |      | **Memory Limit:** 65536K |
| ---------------------------- | ---- | ------------------------ |
| **Total Submissions:** 77551 |      | **Accepted:** 28814      |

Description

While exploring his many farms, Farmer John has discovered a number of amazing wormholes. A wormhole is very peculiar because it is a one-way path that delivers you to its destination at a time that is BEFORE you entered the wormhole! Each of FJ's farms comprises *N* (1 ≤ *N* ≤ 500) fields conveniently numbered 1..*N*, *M* (1 ≤ *M* ≤ 2500) paths, and *W* (1 ≤ *W* ≤ 200) wormholes.

As FJ is an avid time-traveling fan, he wants to do the following: start at some field, travel through some paths and wormholes, and return to the starting field a time before his initial departure. Perhaps he will be able to meet himself :) .

To help FJ find out whether this is possible or not, he will supply you with complete maps to *F* (1 ≤ *F* ≤ 5) of his farms. No paths will take longer than 10,000 seconds to travel and no wormhole can bring FJ back in time by more than 10,000 seconds.

Input

Line 1: A single integer, *F*. *F* farm descriptions follow.
Line 1 of each farm: Three space-separated integers respectively: *N*, *M*, and *W*
Lines 2..*M*+1 of each farm: Three space-separated numbers (*S*, *E*, *T*) that describe, respectively: a bidirectional path between *S* and *E* that requires *T* seconds to traverse. Two fields might be connected by more than one path.
Lines *M*+2..*M*+*W*+1 of each farm: Three space-separated numbers (*S*, *E*, *T*) that describe, respectively: A one way path from *S* to *E* that also moves the traveler back *T* seconds.

Output

Lines 1..*F*: For each farm, output "YES" if FJ can achieve his goal, otherwise output "NO" (do not include the quotes).

Sample Input

```
2
3 3 1
1 2 2
1 3 4
2 3 1
3 1 3
3 2 1
1 2 3
2 3 4
3 1 8
```

Sample Output

```
NO
YES
```

Hint

For farm 1, FJ cannot travel back in time.
For farm 2, FJ could travel back in time by the cycle 1->2->3->1, arriving back at his starting location 1 second before he leaves. He could start from anywhere on the cycle to accomplish this.

Source

[USACO 2006 December Gold](http://poj.org/searchproblem?field=source&key=USACO+2006+December+Gold)

> 只需判断是否存在负环回路即可, 使用SPFA算法判断. 
>
> 时光穿梭的设为负边

```c++
#pragma warning(disable:4996)
#include<cstdio>
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;

/*
* 单源最短路SPFA
* 时间复杂度0(kE)
* 这个是队列实现，有时候改成栈实现会更加快，很容易修改
* 这个复杂度是不定的
*/
const int MAXN = 1010;
const int INF = 0x3f3f3f3f;

struct Edge {
    int v;
    int cost;
    Edge(int _v = 0, int _cost = 0) :v(_v), cost(_cost) {}
};
//邻接表存储每一个顶点的临界点
vector<Edge>E[MAXN];

void addedge(int u, int v, int w) {
    E[u].push_back(Edge(v, w));
}

bool vis[MAXN];//在队列标志
int cnt[MAXN];//每个点的入队列次数
int dist[MAXN];
bool SPFA(int start, int n) {
    memset(vis, false, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    //初始化
    for (int i = 1; i <= n; i++)
        dist[i] = INF;
    vis[start] = true;
    dist[start] = 0;
    queue<int>que;
    while (!que.empty())
        que.pop();
    que.push(start);
    memset(cnt, 0, sizeof(cnt));
    cnt[start] = 1;

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        vis[u] = false;
        //扫描顶点u的所有临接点
        for (int i = 0; i < E[u].size(); i++) {
            int v = E[u][i].v;
            if (dist[v] > dist[u] + E[u][i].cost) {
                dist[v] = dist[u] + E[u][i].cost;
                //如果该顶点没有入队, 将其入队
                if (!vis[v]) {
                    vis[v] = true;
                    que.push(v);
                    if (++cnt[v] > n)
                        return false;
                    //因为存在负权边, 所以这个点会一直进行松弛
                    //cnt[i] 为入队列次数，用来判定是否存在负环回路
                }
            }
        }
    }
    return true;
}


int main() {
    int f, n, m, w;
    cin >> f;
    while (f--) {
        scanf("%d%d%d", &n, &m, &w);
        int u, v, ww;
        for (int i = 1; i <= n; i++) {
            E[i].clear();
        }
        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", &u, &v, &ww);
            addedge(u, v, ww);
            addedge(v, u, ww);
        }
        for (int i = 0; i < w; i++) {
            scanf("%d%d%d", &u, &v, &ww);
            addedge(u, v, -ww);
        }
        int flag = SPFA(1, n);

        if (flag) {
            cout << "NO" << "\n";
        }
        else {
            cout << "YES" << "\n";
        }
    }
}
```
