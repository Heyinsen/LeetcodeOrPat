#pragma warning(disable:4996)
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include<iostream>
using namespace std;
const int maxn = 105;

char g[maxn][maxn];
int vis[maxn][maxn];
int n, m;
int sx, sy, ex, ey;

int kase = 0, cnt;

int dirx[] = { -1,1,0,0 };
int diry[] = { 0,0,1,-1 };

bool ok(int xx, int yy) {
	if (xx <= n + 1 && yy <= m + 1 && xx >= 0 && yy >= 0 && g[xx][yy] != 'X' && !vis[xx][yy])return 1;
	return 0;
}

struct Node {
	int x, y, cost;
	Node(int x_ = 0, int y_ = 0, int cost_ = 0) :x(x_), y(y_), cost(cost_) {}
};

queue<Node>q;

int bfs(){
	while (!q.empty()) {
		q.pop();
	}
	q.push(Node(sx, sy, 0));
	vis[sx][sy] = true;
	while (!q.empty()){
		Node top = q.front();
		q.pop();

		if (top.x == ex && top.y == ey){
			return top.cost;
		}

		for (int i = 0; i < 4; i++){
			int qa = top.x, qb = top.y;
			while (ok(qa + dirx[i], qb + diry[i]))
			{
				qa += dirx[i]; qb += diry[i];
				q.push(Node(qa, qb, top.cost + 1));
				vis[qa][qb] = true;
				//vis[qa][qb] = vis[tempa][tempb] + 1;
				//aa.push(qa); bb.push(qb);
			}
		}
	}
	return -1;
}
int main()
{
	while (scanf("%d%d", &m, &n) && (n || m)) {
		memset(g, 0, sizeof(g));

		cnt = 0;

		printf("Board #%d:\n", ++kase);
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= m; j++) {
				scanf("%c", &g[i][j]);
			}
		}
		while (scanf("%d%d%d%d", &sy, &sx, &ey, &ex) && (sx || sy || ex || ey)) {
			memset(vis, 0, sizeof(vis));
			g[ex][ey] = ' ';
			int ans = bfs();
			if (ans != -1)
				printf("Pair %d: %d segments.\n", ++cnt, ans);
			else
				printf("Pair %d: impossible.\n", ++cnt);
			g[ex][ey] = 'X';
		}
		printf("\n");
	}
}