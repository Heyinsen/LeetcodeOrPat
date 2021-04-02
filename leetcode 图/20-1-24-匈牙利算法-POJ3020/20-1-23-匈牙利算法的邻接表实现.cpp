/*
* 匈牙利算法邻接表形式
* 使用前用init() 进行初始化，给uN 赋值
* 加边使用函数addedge(u,v)
* 时间复杂度:O(m*n)
*/
#include<cstring>
const int MAXN = 5010;//点数的最大值
const int MAXM = 50010;//边数的最大值

struct Edge {
	int to, next;
}edge[MAXM];
int head[MAXN], tot;

void addedge(int u, int v) {
	edge[tot].to = v; edge[tot].next = head[u];
	head[u] = tot++;
}

int linker[MAXN];
bool used[MAXN];
int uN;
bool dfs(int u) {
	for (int i = head[u]; i != -1; i = edge[i].next) {
		int v = edge[i].to;
		if (!used[v]) {
			used[v] = true;
			if (linker[v] == -1 || dfs(linker[v])) {
				linker[v] = u;
				return true;
			}
		}
	}
	return false;
}

int hungary() {
	int res = 0;
	memset(linker, -1, sizeof(linker));
	
	tot = 0;
	memset(head, -1, sizeof(head));
	
	//点的编号0∼uN-1
	for (int u = 0; u < uN; u++) {
		memset(used, false, sizeof(used));
		if (dfs(u))res++;
	}
	return res;
}