#pragma warning(disable:4996)
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<map>
using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 505;

int dist[maxn];
bool vis[maxn];
int g[maxn][maxn];
int prime(int n) {
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		dist[i] = g[1][i];
	}
	vis[1] = true;
	for (int i = 1; i < n; i++) {
		int minn = INF, minn_pos = 0;
		for (int j = 1; j <= n; j++) {
			if(!vis[j] && minn >= dist[j]){
				minn = dist[j];
				minn_pos = j;
			}
		}
		if (minn_pos == 0) {
			return -1;
		}
		ans = max(minn, ans);
		vis[minn_pos] = true;
		for (int i = 1; i <= n; i++) {
			if (!vis[i] && dist[i] > g[minn_pos][i]) {
				dist[i] = g[minn_pos][i];
			}
		}
	}
	return ans;
}

int main() {
	int t;
	cin >> t;
	int n;
	while (t--) {
		memset(g, 0x3f, sizeof(g));
		memset(vis, false, sizeof(vis));
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				scanf("%d", &g[i][j]);
				g[j][i] = g[i][j];
			}
		}
		printf("%d\n", prime(n));
	}
	return 0;
}
/*
1

3
0 990 692
990 0 179
692 179 0
*/