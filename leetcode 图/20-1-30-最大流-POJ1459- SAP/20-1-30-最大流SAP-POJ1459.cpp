#include<iostream>
#include<algorithm>
#include<queue>
//EK算法,Dinic算法,SAP算法
//SAP算法的邻接表形式
#include<cstring>
using namespace std;
const int MAXN = 100010;//点数的最大值
const int MAXM = 400010;//边数的最大值
const int INF = 0x3f3f3f3f;

//临接表的方式建立图
struct Edge {
	int to, v, /*载荷*/cap, /*流量*/flow;
}edge[MAXM];//注意是MAXM
int tol;//边的总数
int head[MAXN];

int gap[MAXN];//距离标号为i的点有多少个
int dep[MAXN];
int pre[MAXN];//记录路径, 一个顶点的前一个顶点的编号, 第一个设置为-1
int cur[MAXN];//head的临时顶点 

//边的初始化
void init() {
	tol = 0;
	memset(head, -1, sizeof(head));
}

//加边，单向图三个参数，双向图四个参数
void addedge(int u, int v, int w/*承载能力*/, int rw = 0/*反向边的承载能力*/) {
	edge[tol].to = v; edge[tol].cap = w; edge[tol].v = head[u];
	edge[tol].flow = 0/*当前流量设置为0*/; head[u] = tol++;
	edge[tol].to = u; edge[tol].cap = rw; edge[tol].v = head[v];
	edge[tol].flow = 0; head[v] = tol++;
}

//SAP算法:求最大流有一种经典的算法，就是每次找增广路时用BFS找，
	//保证找到的增广路是弧数最少的，也就是所谓的Edmonds-Karp算法。
	//O(V*E^2)
//输入参数：起点、终点、点的总数
	//点的编号没有影响，只要输入点的总数
int sap(int start/*起点的编号*/, int end/*终点的编号*/, int N/*顶点的总数*/) {
	memset(gap, 0, sizeof(gap));
	memset(dep, 0, sizeof(dep));

	memcpy(cur, head, sizeof(head));

	int u = start;
	pre[u] = -1;
	gap[0] = N;//距离标号为0的点有n个
	int ans = 0;
	//dep[start]初始化为0
	while (dep[start] < N) {
		//找到增光路
		if (u == end) {
			//寻找路径上残量网络中最小的流量
			int Min = INF;
			for (int i = pre[u]; i != -1; i = pre[edge[i ^ 1].to]/**/)
				if (Min > edge[i].cap - edge[i].flow)
					Min = edge[i].cap - edge[i].flow;
			for (int i = pre[u]; i != -1; i = pre[edge[i ^ 1].to]) {
				edge[i].flow += Min;
				edge[i ^ 1].flow -= Min;

			}
			u = start;
			ans += Min;
			continue;
		}
		//u<end
		bool flag = false;
		int v;

		//遍历顶点u的所有的边v
		for (int i = cur[u]; i != -1; i = edge[i].v) {
			v = edge[i].to;//
			if (edge[i].cap - edge[i].flow && dep[v] + 1 == dep[u]/*寻找允许路*/)
			{
				flag = true;
				cur[u] = pre[v] = i;
				break;
			}
		}
		//找到了允许路
		if (flag) {
			u = v;
			continue;
		}
		int Min = N;
		for (int i = head[u]; i != -1; i = edge[i].v)
			if (edge[i].cap - edge[i].flow && dep[edge[i].to] < Min)
			{
				Min = dep[edge[i].to];
				cur[u] = i;
			}
		gap[dep[u]]--;
		if (!gap[dep[u]])return ans;
		dep[u] = Min + 1;
		gap[dep[u]]++;
		if (u != start) u = edge[pre[u] ^ 1].to;
	}
	return ans;
}
int n, np, nc, m;
int main(){
    char parenthesis;
    int u, v;
    int value;
    while (cin >> n >> np >> nc >> m){
        init();
        int start = n;
        int end = n + 1;
        for (int i = 0; i < m; i++){
            cin >> parenthesis;
            cin >> u;//开始点
            cin >> parenthesis;
            cin >> v;//结束点
            cin >> parenthesis;
            cin >> value;
			if (u == v) {
				continue;
			}
			addedge(u, v, value);
        }
        for (int i = 0; i < np; i++){
            cin >> parenthesis;
            cin >> u;//顶点的序号
            cin >> parenthesis;
            cin >> value;
			addedge(n, u, value);
        }
        for (int i = 0; i < nc; i++){
            cin >> parenthesis;
            cin >> u;
            cin >> parenthesis;
            cin >> value;
			addedge(u, end, value);
        }
        cout << sap(start, end, n + 2) << endl;
    }
    return 0;
}