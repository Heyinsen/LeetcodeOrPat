#pragma warning(disable:4996)
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

char g[45][15];
int nums[45][15];

struct Edge {
	int to, next;
} edge[1000000];
int head[1100], tot;
void addEdge(int u, int v) {
	edge[tot].next = head[u];
	edge[tot].to = v;
	head[u] = tot++;
}

int linker[1100];
bool used[1100];
bool dfs(int u) {
	for (int i = head[u]; i != -1; i = edge[i].next){
		int to = edge[i].to;
		if (!used[to]){
			used[to] = true;
			if (linker[to] == -1 || dfs(linker[to]))
			{
				linker[to] = u;
				return true;
			}
		}

	}
	return false;
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int m, n;
		scanf("%d %d", &m, &n);
		for (int i = 0; i < m; i++)
			scanf("%s", g[i]);

		int cnt = 0;//给找到的"*"编号
		memset(head, -1, sizeof(head));
		tot = 0;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (g[i][j] == '*') {
					cnt++;
					nums[i][j] = cnt;
					if (i >= 1 && g[i - 1][j] == '*') {
						addEdge(nums[i - 1][j], nums[i][j]);
						addEdge(nums[i][j], nums[i - 1][j]);
					}
					if (j >= 1 && g[i][j - 1] == '*') {
						addEdge(nums[i][j], nums[i][j - 1]);
						addEdge(nums[i][j - 1], nums[i][j]);
					}
				}
			}
		}
		memset(linker, -1, sizeof(linker));
		int ans = 0;
		for (int i = 1; i <= cnt; i++) {
			memset(used, false, sizeof(used));
			if (dfs(i))ans++;
		}
		printf("%d\n", cnt - ans / 2);
	}
	return 0;
}