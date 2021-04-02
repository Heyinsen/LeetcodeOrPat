#pragma warning(disable:4996)
#include<cstdio>
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

/*
* 单源最短路SPFA
* 时间复杂度0(kE)
* 这个是队列实现，有时候改成栈实现会更加快，很容易修改
* 这个复杂度是不定的
*/
const int MAXN = 2005;
const int INF = 0x3f3f3f3f;

struct Edge {
	int v;
	double cost;
	Edge(int _v = 0, double _cost = 0) :v(_v), cost(_cost) {}
};

vector<Edge>E[MAXN];

void addEdge(int u, int v, double cost) {
	E[u].push_back(Edge(v, cost));
}
queue<int>q;
bool vis[MAXN];		//顶点i是否在队列中
int cnt[MAXN];		//顶点i进入队列的次数
double dist[MAXN];		//顶点start到顶点dist的最小的跳远距离
bool SPFA(int start, int n) {
	memset(vis, false, sizeof(vis));
	memset(cnt, 0, sizeof(cnt));
	for (int i = 1; i <= n; i++) {
		dist[i] = INF;
	}
	dist[start] = 0;
	q.push(start);
	vis[start] = true;
	cnt[start] = 1;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = false;
		for (int i = 0; i < E[u].size(); i++) {
			int v = E[u][i].v;
			if (dist[v] > max(E[u][i].cost, dist[u])) {
				dist[v] = max(E[u][i].cost, dist[u]);
				//cout << E[u][i].cost << " " << dist[u] << " " << E[u][i].cost << endl;
				if (!vis[v]) {
					vis[v] = true;
					q.push(v);
					if (++cnt[v] > n) {
						return false;
					}
				}
			}

		}
	}
	return true;
}

struct Point2 {
	int x, y;
	Point2(int _x = 0, int _y = 0) :x(_x), y(_y) {}
}point[MAXN];

inline double distance(const Point2& a, const Point2& b) {
	return sqrt(double((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

int main() {
	int n;
	int a, b;
	int time = 0;
	while (scanf("%d", &n) && n) {
		while (!q.empty()) {
			q.pop();
		}
		for (int i = 1; i <= n; i++) {
			E[i].clear();
		}
		for (int i = 1; i <= n; i++) {
			scanf("%d%d", &point[i].x, &point[i].y);
		}
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				double d = distance(point[i], point[j]);
				addEdge(i, j, d);
				addEdge(j, i, d);
			}
		}
		SPFA(1, n);
		cout << "Scenario #" << ++time << "\nFrog Distance = ";
		printf("%.3f\n", dist[2]);
	}
}