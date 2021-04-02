#pragma warning(disable:4996)
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 105;

struct Edge {
	int u, v;
	double ruv, cuv;
	Edge(int _u = 0, int _v = 0, double _ruv = 0, double _cuv=0) :u(_u), v(_v), ruv(_ruv), cuv(_cuv) {}
};

vector<Edge>e;
double dist[maxn];

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
			double ruv = e[j].ruv;
			double cuv = e[j].cuv;
			//松弛条件和BellmanFloyed算法不同
			if ((dist[u] - cuv) * ruv > dist[v]) {
				dist[v] = (dist[u] - cuv) * ruv;
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
		double ruv = e[i].ruv;
		double cuv = e[i].cuv;
		if ((dist[u] - cuv) * ruv > dist[v]) {
			dist[v] = (dist[u] - cuv) * ruv;
			return true;		//发现正环回路
		}
	}
	return false;
}

int main() {
	int n, m, s;
	double v;
	scanf("%d%d%d%lf", &n, &m, &s, &v);
	int a, b;
	double rab, cab, rba, cba;
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &a, &b);
		scanf("%lf%lf%lf%lf", &rab, &cab, &rba, &cba);
		//边
		e.push_back(Edge(a, b, rab, cab));
		e.push_back(Edge(b, a, rba, cba));
	}
	bool ans = bellmanFloyed(n, s, v);
	if (ans) {
		cout << "YES" << endl;
	}
	else {
		cout << "NO" << endl;
	}
}