#pragma warning(disable:4996)
#include <cstring>
#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
const int maxn = 55;
const int maxp =	15;
const int INF = 0x3f3f3f3f;
/*
* SAP 算法（矩阵形式）
* 结点编号从0 开始
*/
const int MAXN = 55;		//节点数目

int maze[MAXN][MAXN];		//图
int gap[MAXN], dis[MAXN], pre[MAXN], cur[MAXN];
int sap(int start, int end, int nodenum/*节点的数量*/) {
	memset(cur, 0, sizeof(cur));
	memset(dis, 0, sizeof(dis));
	memset(gap, 0, sizeof(gap));
	int u = pre[start] = start;
	int maxflow = 0;		//最大流的结果
	int aug = -1;
	gap[0] = nodenum;
	while (dis[start] < nodenum) {
	loop:
		for (int v = cur[u]; v < nodenum; v++)
			if (maze[u][v] && dis[u] == dis[v] + 1) {
				if (aug == -1 || aug > maze[u][v])aug = maze[u][v];
				pre[v] = u;
				u = cur[u] = v;
				if (v == end) {
					maxflow += aug;
					for (u = pre[u]; v != start; v = u, u = pre[u]) {
						maze[u][v] -= aug;
						maze[v][u] += aug;
					}
					aug = -1;
				}
				goto loop;
			}
		int mindis = nodenum - 1;
		for (int v = 0; v < nodenum; v++)
			if (maze[u][v] && mindis > dis[v]) {
				cur[u] = v;
				mindis = dis[v];
			}
		if ((--gap[dis[u]]) == 0)break;
		gap[dis[u] = mindis + 1]++;
		u = pre[u];
	}
	return maxflow;
}

int cost[maxn];
int g[maxn * 2][maxn * 2];
int G[maxn * 2][maxn * 2];

struct Node {
	int x, y, cost;
};

int main() {
	int p, n;
	while (cin >> p >> n && (p || n)) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &cost[i]);		//机器i每小时生产的零件的数量
			for (int j = 0; j < p; j++) {
				scanf("%d", &g[i][j]);
			}
			for (int j = 0; j < p; j++) {
				scanf("%d", &g[i + n][j]);
			}
		}
		memset(G, 0, sizeof(G));
		//将每一台机器拆分为两个顶点, 顶点i和顶点i+n
			//由顶点i指向顶点i+n构造一条边
			//边的权值为cost[i]
		for (int i = 0; i < n; i++) {
			G[i][i + n] = cost[i];
		}
		//源点的标号设置为2*n和2*n+1.
			//源点和所有的对部件要求为0的顶点或者
			//存在2的顶点之间连上边
		for (int i = 0; i < n; i++) {
			 bool flag = true;
			for (int j = 0; j < p; j++) {
				if (!(g[i][j] == 0 || g[i][j] == 2)) {
					flag = false;
					break;
				}
			}
			if (flag) {
				G[2 * n][i] = INF;
			}
		}
		//汇点和所有的对部件要求为1的顶点连上边
			//边的权值为INF
		for (int i = n; i < 2 * n; i++) {
			int flag = true;
			for (int j = 0; j < p; j++) {
				if (g[i][j] != 1) {
					flag = false;
					break;
				}
			}
			if (flag) {
				G[i][2 * n + 1] = INF;
			}
		}
		//如果一个机器的产出和另一个机器的产入相接,
			//那么将这两个机器相连,权值为0, 否则为INF
		for (int i = n; i < 2 * n; i++) {//产出
			for (int j = 0; j < n; j++) {
				bool flag = true;
				for (int k = 0; k < p; k++) {
					if (!(g[i][k] == g[j][k] || g[j][k] == 2)) {
						flag = false;
						break;
					}
				}
				if (flag) {
					G[i][j] = INF;
				}	
			}
		}
		for (int i = 0; i < 2 * n + 2; i++) {
			for (int j = 0; j < 2 * n + 2; j++) {
				maze[i][j] = G[i][j];
			}
		}
		/*for (int i = 0; i < 2 * n + 2; i++) {
			for (int j = 0; j < 2 * n + 2; j++) {
				if(maze[i][j]!=INF)
				cout << maze[i][j] << "\t";
				else {
					cout << "INF" << "\t";
				}
			}
			cout << "\n";
		}*/
		//调用SAP算法模板求最大流
		int res = sap(2 * n, 2 * n + 1, 2 * n + 2);
		cout << res << " ";
		int cnt = 0;
		vector<Node>q;
		for (int i = n; i < 2 * n; i++) {//出点
			for (int j = 0; j < n; j++) {//入点
				if (i - n != j && G[i][j] != maze[i][j]) {
					cnt++;
					Node tmp;
					tmp.x = i - n + 1;
					tmp.y = j + 1;
					tmp.cost = G[i][j] - maze[i][j];
					q.push_back(tmp);
				}
			}
		}
		cout << cnt << "\n";
		for (int i = 0; i < q.size(); i++) {
			cout << q[i].x << " " << q[i].y << " " << q[i].cost << "\n";
		}
	}
	return 0;
}
/*
3 4
15  0 0 0  0 1 0
10  0 0 0  0 1 1
30  0 1 2  1 1 1
3   0 2 1  1 1 1
*/