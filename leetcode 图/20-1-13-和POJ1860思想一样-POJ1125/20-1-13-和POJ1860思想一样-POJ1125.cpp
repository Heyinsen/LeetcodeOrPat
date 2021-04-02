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
const int maxn = 35;

struct Edge {
	int u, v;
	double rate;
	Edge(int _u = 0, int _v = 0, double _rate = 0) :u(_u), v(_v), rate(_rate) {}
};

vector<Edge>e;
double dist[maxn];

map<string, int>mp;		// 名字和顶点序号的对应

bool bellmanFloyed(int n, int s, double v) {
	//初始化条件和bellmanFloyed算法不同
	for (int i = 1; i <= n; i++) {
		dist[i] = 0;
	}
	dist[s] = v;
	for (int i = 1; i < n; i++) {
		bool flag = 0;
		for (int j = 0; j < e.size(); j++) {
			int u = e[j].u;
			int v = e[j].v;
			double rate = e[j].rate;
			//松弛条件和BellmanFloyed算法不同
			if (dist[u] * rate > dist[v]) {
				dist[v] = dist[u] * rate;
				flag = true;
			}
		}
		//如果这一遍没有松弛, 说明没有正环回路, 直接返回
		if (!flag) {
			return false;
		}
	}
	for (int i = 0; i < e.size(); i++) {
		int u = e[i].u;
		int v = e[i].v;
		double rate = e[i].rate;
		if (dist[u] * rate > dist[v]) {
			dist[v] = dist[u] * rate;
			return true;		//发现正环回路
		}
	}
	return false;
}

int main() {
	int kase = 1;
	ios::sync_with_stdio(false); cin.tie(false);
	int n;
	while (scanf("%d", &n) && n) {
		string str;
		mp.clear();
		for (int i = 0; i < n; i++) {
			cin >> str;
			mp[str] = i + 1;
		}
		int m;
		cin >> m;
		string sour, dest;
		double rate;
		e.clear();
		for (int i = 1; i <= m; i++) {
			cin >> sour >> rate >> dest;
			int a = mp[sour];
			int b = mp[dest];
			//边
			e.push_back(Edge(a, b, rate));
		}
		int ans = false;
		ans = bellmanFloyed(n, 1, 100);
		if (ans) {
			cout << "Case " << kase++ << ": Yes" << "\n";
		}
		else {
			cout << "Case " << kase++ << ": No" << "\n";
		}
	}
}