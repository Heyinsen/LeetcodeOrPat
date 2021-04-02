[bellman_floyed算法介绍](https://blog.csdn.net/strve/article/details/80957491)

## poj1860

Currency Exchange

| **Time Limit:** 1000MS       |      | **Memory Limit:** 30000K |
| ---------------------------- | ---- | ------------------------ |
| **Total Submissions:** 44057 |      | **Accepted:** 16975      |

Description

Several currency exchange points are working in our city. Let us suppose that each point specializes in two particular currencies and performs exchange operations only with these currencies. There can be several points specializing in the same pair of currencies. Each point has its own exchange rates, exchange rate of A to B is the quantity of B you get for 1A. Also each exchange point has some commission, the sum you have to pay for your exchange operation. Commission is always collected in source currency.
For example, if you want to exchange 100 US Dollars into Russian Rubles at the exchange point, where the exchange rate is 29.75, and the commission is 0.39 you will get (100 - 0.39) * 29.75 = 2963.3975RUR.
You surely know that there are N different currencies you can deal with in our city. Let us assign unique integer number from 1 to N to each currency. Then each exchange point can be described with 6 numbers: integer A and B - numbers of currencies it exchanges, and real RAB, CAB, RBA and CBA - exchange rates and commissions when exchanging A to B and B to A respectively.
Nick has some money in currency S and wonders if he can somehow, after some exchange operations, increase his capital. Of course, he wants to have his money in currency S in the end. Help him to answer this difficult question. Nick must always have non-negative sum of money while making his operations.

Input

The first line of the input contains four numbers: N - the number of currencies, M - the number of exchange points, S - the number of currency Nick has and V - the quantity of currency units he has. The following M lines contain 6 numbers each - the description of the corresponding exchange point - in specified above order. Numbers are separated by one or more spaces. 1<=S<=N<=100, 1<=M<=100, V is real number, 0<=V<=103.
For each point exchange rates and commissions are real, given with at most two digits after the decimal point, 10-2<=rate<=102, 0<=commission<=102.
Let us call some sequence of the exchange operations simple if no exchange point is used more than once in this sequence. You may assume that ratio of the numeric values of the sums at the end and at the beginning of any simple sequence of the exchange operations will be less than 104.

Output

If Nick can increase his wealth, output YES, in other case output NO to the output file.

Sample Input

```
3 2 1 20.0
1 2 1.00 1.00 1.00 1.00
2 3 1.10 1.00 1.10 1.00
```

Sample Output

```
YES
```

Source

[Northeastern Europe 2001](http://poj.org/searchproblem?field=source&key=Northeastern+Europe+2001), Northern Subregion

```c++
//BellmanFloyed算法板子
//单源最短路径的bellman_ford算法, 复杂度O(VE)
//可以处理负权边图
//可以判断是否存在负环回路, 返回truem, 当且仅当图中不包含从源点可达的负权回路
//vector<Edge>E; 先E.clear() 初始化，然后加入所有边
//点的编号从1 开始(从0 开始简单修改就可以了)

const int INF=0x3f3f3f3f;
//顶点的数量
const int MAXN=550;
//顶点start到其他所有顶点的最短路径
int dist[MAXN];

struct Edge{
    int u,v;
    int cost;
    Edge(int _u=0,int _v=0,int _cost=0):u(_u),v(_v),cost(_cost){}
};
vector<Edge>E;
//点的编号从1开始
//顶点start到其他所有顶点的最短路径, 顶点的数量为n
bool bellman_ford(int start,int n){
    //dist初始化
    for(int i=1;i<=n;i++)
        dist[i]=INF;
    dist[start]=0;
    //最多做n-1次
    for(int i=1;i<n;i++){
        bool flag=false;
        //遍历所有的边进行松弛计算
        for(int j=0;j<E.size();j++){
            int u=E[j].u;
            int v=E[j].v;
            int cost=E[j].cost;
            if(dist[v]>dist[u]+cost){
                dist[v]=dist[u]+cost;
                flag=true;
            }
        }
        //这一遍松弛没有任何更新, 说明start点为源点的最短路求解完毕
        if(!flag)
            return true;//没有负环回路
    }
    //如果经过n-1次松弛后，还能继续松弛，说明有负权回路存在，
    //如果n-1次松弛后，如果有边（u，v）满足d[v]>d[u]+w[u][v]，
    //      说明还能继续松弛，存在负权回路。
    for(int j=0;j<E.size();j++)
        if(dist[E[j].v]>dist[E[j].u]+E[j].cost)
            return false;//有负环回路
    return true;//没有负环回路
}
```



[翻译](https://blog.csdn.net/yslcl12345/article/details/50574213)

> 本题采用BellmanFloyed算法的思想, 所不同之处是本题求的是是否具有正环回路(原生的BellmanFloyed算法求的是是否具有负环回路), BellmanFloyed算法给每一个顶点赋了一个权值, 即算法中的dist[i]代表顶点i的权值, 通过每次根据对边的信息对顶点的权值进行更新, 这就是我们所说的松弛操作, 于是本题中我们可以将图进行抽象, 即以每一种货币为一个顶点, 一共有n个顶点, 边的权值看成是一种信息,  通过这个信息更新顶点的权值. 由于要求正权回路, 需要和bellmanFloyed算法反向行之---(n-1次扫描, 每次遍历所有边进行松弛操作)每次进行的松弛操作和dist[]数组的初始化需做修改. 
>
> 只要找到正环回路, 我们便可以认为必定可以赚钱. 

```c++
#pragma warning(disable:4996)
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 105;

struct Edge {
	int u, v;
	double ruv, cuv;
	Edge(int _u = 0, int _v = 0, double _ruv = 0, double _cuv=0) :u(_u), v(_v), ruv(_ruv), cuv(_cuv) {}
};

vector<Edge>e;
double dist[maxn];

bool bellmanFloyed(int n, int s, double v) {
	//初始化条件和bellmanFloyed算法不同
	for (int i = 1; i <= n; i++) {
		dist[i] = 0;
	}
	dist[s] = v;
	for (int i = 1; i < n; i++) {
		bool flag = 0;
		for (int j = 0; j < e.size(); j++) {
			int u = e[j].u;
			int v = e[j].v;
			double ruv = e[j].ruv;
			double cuv = e[j].cuv;
			//松弛条件和BellmanFloyed算法不同
			if ((dist[u] - cuv) * ruv > dist[v]) {
				dist[v] = (dist[u] - cuv) * ruv;
				flag = true;
			}
		}
		//如果这一遍没有松弛, 说明没有正环回路, 直接返回
		if (!flag) {
			return false;
		}
	}
	for (int i = 0; i < e.size(); i++) {
		int u = e[i].u;
		int v = e[i].v;
		double ruv = e[i].ruv;
		double cuv = e[i].cuv;
		if ((dist[u] - cuv) * ruv > dist[v]) {
			dist[v] = (dist[u] - cuv) * ruv;
			return true;		//发现正环回路
		}
	}
	return false;
}

int main() {
	int n, m, s;
	double v;
	scanf("%d%d%d%lf", &n, &m, &s, &v);
	int a, b;
	double rab, cab, rba, cba;
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &a, &b);
		scanf("%lf%lf%lf%lf", &rab, &cab, &rba, &cba);
		//边
		e.push_back(Edge(a, b, rab, cab));
		e.push_back(Edge(b, a, rba, cba));
	}
	bool ans = bellmanFloyed(n, s, v);
	if (ans) {
		cout << "YES" << endl;
	}
	else {
		cout << "NO" << endl;
	}
}
```

