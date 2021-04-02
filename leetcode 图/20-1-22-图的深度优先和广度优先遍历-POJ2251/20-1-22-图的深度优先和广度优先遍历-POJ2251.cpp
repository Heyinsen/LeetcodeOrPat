#pragma warning(disable:4996)
#include <iostream>
#include <cstdio>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;
const int maxn = 105;

char g[35][35][35];
int sd, sx, sy, ed, ex, ey;
int depth, n, m;
int vis[35][35][35];

struct Node {
	int d, x, y;
	int step;
	Node(int d_ = 0, int x_ = 0, int y_ = 0) :d(d_), x(x_), y(y_) {}
};
queue<Node>q;

int dird[] = { 1, -1, 0, 0, 0, 0 };
int dirx[] = { 0, 0, -1, 1, 0, 0 };
int diry[] = { 0, 0, 0, 0, -1, 1 };

inline bool ok(int d, int x, int y) {
	return d >= 1 && d <= depth && x >= 1 && x <= n && y >= 0 && y <= m && vis[d][x][y] == -1 && g[d][x][y] == '.';
}

int bfs() {
	while (!q.empty()) {
		q.pop();
	}
	q.push(Node(sd, sx, sy));
	vis[sd][sx][sy] = 0;
	while (!q.empty()) {
		Node top = q.front();
		q.pop();
		if (top.d == ed && top.x == ex && top.y == ey) {
			return vis[ed][ex][ey];
		}
		for (int i = 0; i < 6; i++) {
			int td = dird[i] + top.d;
			int tx = dirx[i] + top.x;
			int ty = diry[i] + top.y;
			if (ok(td, tx, ty)) {
				q.push(Node(td, tx, ty));
				vis[td][tx][ty] = vis[top.d][top.x][top.y] + 1;
			}
		}
	}
	return -1;
}

int main() {
	while (scanf("%d%d%d", &depth, &n, &m) && (depth || n || m)) {
		getchar();
		memset(vis, 0xff, sizeof(vis));
		for (int i = 1; i <= depth; i++) {
			for (int j = 1; j <= n; j++) {
				for (int k = 1; k <= m; k++) {
					scanf("%c", &g[i][j][k]);
					if (g[i][j][k] == 'S') {
						g[i][j][k] = '.';
						sd = i;
						sx = j;
						sy = k;
					}
					else if (g[i][j][k] == 'E') {
						g[i][j][k] = '.';
						ed = i;
						ex = j;
						ey = k;
					}
				}
				getchar();
			}
			getchar();
		}
		/*for (int i = 1; i <= depth; i++) {
			for (int j = 1; j <= n; j++) {
				for (int k = 1; k <= m; k++) {
					cout << g[i][j][k] << " ";
				}
				cout << "\n";
			}
			cout << "\n";
		}*/
		int ans = bfs();
		if (ans != -1) {
			cout << "Escaped in " << ans << " minute(s).\n";
		}
		else {
			cout << "Trapped!\n";
		}
	}
	return 0;
}