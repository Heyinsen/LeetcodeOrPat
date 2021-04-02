昂贵的聘礼

| **Time Limit:** 1000MS       |      | **Memory Limit:** 10000K |
| ---------------------------- | ---- | ------------------------ |
| **Total Submissions:** 62240 |      | **Accepted:** 18853      |

Description

年轻的探险家来到了一个印第安部落里。在那里他和酋长的女儿相爱了，于是便向酋长去求亲。酋长要他用10000个金币作为聘礼才答应把女儿嫁给他。探险家拿不出这么多金币，便请求酋长降低要求。酋长说："嗯，如果你能够替我弄到大祭司的皮袄，我可以只要8000金币。如果你能够弄来他的水晶球，那么只要5000金币就行了。"探险家就跑到大祭司那里，向他要求皮袄或水晶球，大祭司要他用金币来换，或者替他弄来其他的东西，他可以降低价格。探险家于是又跑到其他地方，其他人也提出了类似的要求，或者直接用金币换，或者找到其他东西就可以降低价格。不过探险家没必要用多样东西去换一样东西，因为不会得到更低的价格。探险家现在很需要你的帮忙，让他用最少的金币娶到自己的心上人。另外他要告诉你的是，在这个部落里，等级观念十分森严。地位差距超过一定限制的两个人之间不会进行任何形式的直接接触，包括交易。他是一个外来人，所以可以不受这些限制。但是如果他和某个地位较低的人进行了交易，地位较高的的人不会再和他交易，他们认为这样等于是间接接触，反过来也一样。因此你需要在考虑所有的情况以后给他提供一个最好的方案。
为了方便起见，我们把所有的物品从1开始进行编号，酋长的允诺也看作一个物品，并且编号总是1。每个物品都有对应的价格P，主人的地位等级L，以及一系列的替代品Ti和该替代品所对应的"优惠"Vi。如果两人地位等级差距超过了M，就不能"间接交易"。你必须根据这些数据来计算出探险家最少需要多少金币才能娶到酋长的女儿。

Input

输入第一行是两个整数M，N（1 <= N <= 100），依次表示地位等级差距限制和物品的总数。接下来按照编号从小到大依次给出了N个物品的描述。每个物品的描述开头是三个非负整数P、L、X（X < N），依次表示该物品的价格、主人的地位等级和替代品总数。接下来X行每行包括两个整数T和V，分别表示替代品的编号和"优惠价格"。

Output

输出最少需要的金币数。

Sample Input

```
1 4
10000 3 2
2 8000
3 5000
1000 2 1
4 200
3000 2 1
4 200
50 2 0
```

Sample Output

```
5250
```

Source

[浙江](http://poj.org/searchproblem?field=source&key=浙江)



**解题思路**

> dijkstra算法裸题
> 关键是建图: 
> 每一个物品作为节点, 节点之间的优惠关系作为边建立有向图, 边的方向为可替代的物品指向被替代的物品.
>  组长的节点编号为1, 设一个虚拟的0点,  0点到其他所有点的距离初始化为每件物品的价格. 
>
> 于是, 题意转化为求0点到1点的最短距离.
>
> 考虑等级的限制, 只需要枚举最小等级, 在符合要求的点中寻找满足要求的最短距离即可. 

对于样例的解释:

![20-1-8-Dijkstra-POJ1062](/20-1-8-Dijkstra-POJ1062.jpg)

```c++
#pragma warning(disable:4996)
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 105;

//地位等级差距和物品的总数
int m, n;

//物品的价格和物品主人的等级, 该节点是否被使用过
int val[maxn];
int rankk[maxn];
int vis[maxn];

//建立的有向图
int g[maxn][maxn];

//存储0节点到其他所有节点的最短路
int d[maxn];


//输入数据处理
void input() {
    //有向图的初始化
    memset(g, 0x3f, sizeof(g));

    scanf("%d%d", &m, &n);
    int p, l, x;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &p, &l, &x);
        val[i] = p;
        rankk[i] = l;
        //边的开始点, 优惠价格
        int stp, prior;

        for (int j = 1; j <= x; j++) {
            scanf("%d%d", &stp, &prior);
            g[stp][i] = prior;
        }
    }
}


//求出0点到1点的最短距离
int dijkstra() {
    memset(d, 0x3f, sizeof(d));
    //d[maxn]的初始化
    for (int i = 1; i <= n; i++) {
        d[i] = val[i];
    }

    for (int j = 1; j <= n; j++) {
        //寻找到0点的拥有最短距离的点
        int minpos = 0, mindis = INF;
        for (int i = 1; i <= n; i++) {
            if (mindis > d[i] && !vis[i]) {
                mindis = d[i];
                minpos = i;
            }
        }

        //如果已经找到到1点的最短距离, 返回
        if (minpos == 1) {
            return d[1];
        }

        vis[minpos] = true;
        //更新最短距离
        for (int i = 1; i <= n; i++) {
            if (!vis[i] && d[minpos] + g[minpos][i] < d[i]) {
                d[i] = d[minpos] + g[minpos][i];
            }
        }
    }

    //如果没找到最短距离
    return INF;
}


int main() {
    input();
    //答案
    int ans = INF;

    //将每一个点作为最小等级进行尝试
    for (int i = 1; i <= n; i++) {
        memset(vis, false, sizeof(vis));
        int min_rank = rankk[i];

        //寻找不满足条件的点
        for (int j = 1; j <= n; j++) {
            if (rankk[j]<min_rank || rankk[j] - min_rank > m) {
                vis[j] = true;
            }
        }
        int min_dis = dijkstra();
        ans = min(ans, min_dis);
    }
    cout << ans << endl;
}
```

