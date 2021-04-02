#include <cstring>
/*
* SAP 算法（矩阵形式）
* 结点编号从0 开始
*/
const int MAXN = 1100;		//节点数目
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
						maze[u][v] = aug;
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