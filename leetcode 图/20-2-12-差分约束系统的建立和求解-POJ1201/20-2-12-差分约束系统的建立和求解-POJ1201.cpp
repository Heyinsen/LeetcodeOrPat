#pragma warning(disable:4996)
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn = 50005;
int head[maxn];
bool vis[maxn];
int d[maxn];
struct Edge {
	int v, cost;
	int next;
	Edge(int v_ = 0, int cost_ = 0, int next_ = 0) {
		v = v_;
		cost = cost_;
		next = next_;
	}
	void setNext(int next_) {
		next = next_;
	}
};
Edge edge[maxn * 10];
int num_edge = 0;

void addEdge(int u, int v, int cost) {
	edge[num_edge] = Edge(v, cost, head[u]);
	head[u] = num_edge++;
}


int spfa(int minn, int maxx) {
	//[0,minn]的区间内的所有的数初始化为0
		//来考虑minn这个位置是否需要初始化为-1
		//题目所求为d[maxx+1]-d[minn], 故d[minn]=0
		//(minn,maxx]内的所有的数初始化为-1
	fill(d + minn + 1, d + maxx + 1, -1);
	vis[minn] = true;
	queue<int>q;
	q.push(minn);
	while (!q.empty()) {
		int top = q.front();
		q.pop();
		vis[top] = false;
		for (int i = head[top]; i != -1; i = edge[i].next) {
			int v = edge[i].v;
			if (d[v] < d[top] + edge[i].cost) {
				d[v] = d[top] + edge[i].cost;
				if (!vis[v]) {
					vis[v] = true;
					q.push(v);
				}
			}
		}
	}
	return d[maxx + 1];
}

//设d[i]代表从[0,i]的区间内至少选出d[i]个数
	//对于每一个[ai,bi],都有d[bi]-d[ai-1]>=ci
	//一个隐含的条件0<=d[i]-d[i-1]<=1
	//其中0<=ai<=bi<=50000
//ai==0时, 上述的d[ai-1]产生了d[-1], d[i-1]产生了d[-1]
	//为了解决这个问题, 将d[i+1]表示为[0,i]选出的d[i+1]个数
	//这样当i==0时, [0,0]选出的d[1]个数便可以表示了
	//此时建立约束图时, 边为(ai,bi+1)
int main() {
	int n;
	scanf("%d", &n);
	memset(head, 0xff, sizeof(head));
	int u, v, cost;
	int maxx = 0, minn = INF;
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &u, &v, &cost);
		addEdge(u, v + 1, cost);
		maxx = max(maxx, v);
		minn = min(minn, u);
	}
	for (int i = minn; i <= maxx; i++) {
		addEdge(i, i + 1, 0);//隐藏条件d[i]-d[i-1]>=0
		addEdge(i + 1, i, -1); //隐含条件d[i]-d[i-1]<=1
	}
	cout << spfa(minn, maxx) << "\n";
	return 0;
}

/*
5
3 7 3
8 10 3
6 8 1
1 3 1
10 11 1
*/
