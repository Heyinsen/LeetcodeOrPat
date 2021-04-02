#pragma warning(disable:4996)
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

const int maxn = 505;//顶点的个数
const int maxm = 10005;

int n, m;
int g[maxn][maxn];
int linker[maxn];
bool used[maxn];


bool dfs(int u) {
	for (int v = 0; v < n; v++) {
		if (g[u][v] && !used[v]) {
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
	memset(linker, 0xff, sizeof(linker));
	for (int u = 0; u < n; u++) {
		memset(used, false, sizeof(used));
		if (dfs(u)) {
			res++;
		}
	}
	return res;
}

int main() {
	cin >> n >> m;
	int u, v;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &u, &v);
		g[u - 1][v - 1] = 1;
	}
	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << g[i][j] << " ";
		}
		cout << "\n";
	}*/
	cout << hungary() << "\n";
	return 0;
}
