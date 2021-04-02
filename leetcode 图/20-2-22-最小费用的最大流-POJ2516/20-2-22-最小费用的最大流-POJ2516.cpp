#pragma warning(disable:4996)
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN = 110;
const int MAXM = 110 * 110;
const int maxn = 55;
const int INF = 0x3f3f3f3f;

int head[MAXN];
struct Edge {
	int u, v, cap, cost, next;
	Edge(int u_ = 0, int v_ = 0, int cap_ = 0, int cost_ = 0, int next_ = 0) {
		u = u_;
		v = v_;
		cap = cap_;
		cost = cost_;
		next = next_;
	}
}edge[MAXM];
int num_of_vertices;
int cur_edge_index;
int source, meet;//源点和汇点的序号

void addEdge(int u, int v, int cap, int cost) {
	//正向边
	edge[cur_edge_index].u = u; //
	edge[cur_edge_index].v = v;
	edge[cur_edge_index].cap = cap;
	edge[cur_edge_index].cost = cost;
	edge[cur_edge_index].next = head[u];
	head[u] = cur_edge_index++;

	//设置反向边
	edge[cur_edge_index].u = v; //
	edge[cur_edge_index].v = u;
	edge[cur_edge_index].cap = 0;
	edge[cur_edge_index].cost = -cost;
	edge[cur_edge_index].next = head[v];
	head[v] = cur_edge_index++;
}
//该顶点是在队列
bool vis[MAXN];
int d[MAXN];
int pre[MAXN];
bool spfa() {
	for (int i = 0; i < num_of_vertices; i++) {
		vis[i] = false;
		d[i] = INF;
	}
	vis[source] = true;
	d[source] = 0;

	queue<int> q;
	while (!q.empty()) {
		q.pop();
	}
	q.push(source);
	while (!q.empty()) {
		int u = q.front(); 
		q.pop();
		for (int i = head[u]; i != -1; i = edge[i].next) {
			int v = edge[i].v;
			//仍然存在曾广路并且优先每次找到最小费用的增广路
			if (edge[i].cap && d[v] > d[u] + edge[i].cost) {
				d[v] = d[u] + edge[i].cost;
				pre[v] = i;
				//这里的不会出现负权回路, 无需判环
				if (!vis[v]) {
					vis[v] = true;
					q.push(v);
				}
			}
		}
		vis[u] = false;
	}
	return d[meet] < INF;
}
int MCMF() {
	int res = 0;
	//找到一条增广路
	while (spfa()) {
		//路径回溯, 路径上的flow全部加上
		int flow = INF;
		int cost = 0;
		for (int u = meet; u != source; u = edge[pre[u]].u) {
			flow = min(flow, edge[pre[u]].cap);
		}
		for (int u = meet; u != source; u = edge[pre[u]].u) {
			edge[pre[u]].cap -= flow;
			edge[pre[u] ^ 1].cap += flow;
			cost += flow * edge[pre[u]].cost;
		}
		res += cost;
	}
	return res;
}

//(0,maxn)
int n, m, k;//n个shopkeeper, m个supplies place, 需要k types commodities
int g[maxn][maxn][maxn];

int to[maxn][maxn];//to[i][j]代表第i个商家需要的第j种商品的个数
int from[maxn][maxn];//from[i][j]代表第i个supper提供的第j种商品的个数

bool isEnough(int* needs, int* supplies) {
	for (int i = 0; i < k; i++) {
		if (needs[i] > supplies[i])
			return false;
	}
	return true;
}

int main() {
	int supplies[maxn];
	int needs[maxn];//needs[i]代表所有商家一共需要的第i种商品的个数
	while (~scanf("%d%d%d", &n, &m, &k) && (n || m || k)) {
		memset(supplies, 0, sizeof(supplies));
		memset(needs, 0, sizeof(needs));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < k; j++) {
				scanf("%d", &to[i][j]);
				needs[j] += to[i][j];
			}
		}
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < k; j++) {
				scanf("%d", &from[i][j]);
				supplies[j] += from[i][j];
			}
		}

		for (int i = 0; i < k; i++) {
			for (int x = 0; x < n; x++) {
				for (int y = 0; y < m; y++) {
					scanf("%d", &g[i][x][y]);
				}
			}
		}
		if (isEnough(needs, supplies) == false) {
			puts("-1");
			continue;
		}
		//源点和汇点的序号
		source = n + m;
		meet = n + m + 1;
		num_of_vertices = n + m + 2;

		int res = 0;
		//处理每一件商品
		for (int t = 0; t < k; ++t) {
			memset(head, -1, sizeof(head));
			cur_edge_index = 0;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					//这里是j到i
					addEdge(j, i + m, INF, g[t][i][j]);
				}
			}
			//源点和汇点加边, m个供应商, n个shopkeepers
			for (int i = 0; i < m; i++) {
				addEdge(source, i, from[i][t], 0);
			}
			for (int i = 0; i < n; i++) {
				addEdge(i + m, meet, to[i][t], 0);
			}
			res += MCMF();
		}
		printf("%d\n", res);
	}
	return 0;
}