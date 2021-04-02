#pragma warning(disable:4996)
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<map>
using namespace std;

/*
* Kruskal 算法求MST
*/
const int MAXN = 2005;//最大点数
const int MAXM = 2100000;//最大边数

int F[MAXN];//并查集使用

struct Edge {
	int u, v, w;
}edge[MAXM];//存储边的信息，包括起点/终点/权值

int tol;//边数，加边前赋值为0

void addEdge(int u, int v, int w) {
	edge[tol].u = u;
	edge[tol].v = v;
	edge[tol++].w = w;
}

//排序函数，讲边按照权值从小到大排序
bool cmp(Edge a, Edge b) {
	return a.w < b.w;
}

int find(int x) {
	if (F[x] == -1)
		return x;
	else
		return F[x] = find(F[x]);
}

//传入点数，返回最小生成树的权值，如果不连通返回-1
int kruskal(int n) {
	memset(F, -1, sizeof(F));
	sort(edge, edge + tol, cmp);

	int cnt = 0;//计算加入的边数
	int ans = 0;

	for (int i = 0; i < tol; i++) {
		int u = edge[i].u;
		int v = edge[i].v;
		int w = edge[i].w;
		int t1 = find(u);
		int t2 = find(v);
		if (t1 != t2) {
			ans += w;
			F[t1] = t2;
			cnt++;
		}
		if (cnt == n-1)break;
	}
	if (cnt < n-1)return -1;//不连通
	else return ans;
}

char vec[MAXN][8];
//vector<string>vec;
int main() {
    //ios::sync_with_stdio(false);
    //cin.tie(0);
    int n;
    while (cin >> n && n) {
        //string str;
		tol = 0;
        //vec.clear();
        //vec.reserve(2100000);
        for (int i = 0; i < n; i++) {
            //cin >> str;
            //vec.push_back(str);
			scanf("%s", vec[i]);
        }
        for (int i = 0; i < n/*vec.size()*/; i++) {
            for (int j = i + 1; j < n; j++) {
                int cnt = 0;
                for (int k = 0; k < 7; k++) {
                    if (vec[i][k] != vec[j][k]) {
                        cnt++;
                    }
                }
                addEdge(i, j, cnt);
            }
        }
        int ans = kruskal(n);
        cout << "The highest possible quality is " << "1/" << ans << ".\n";
    }
    return 0;
}

/*
4
aaaaaaa
baaaaaa
abaaaaa
aabaaaa
0
*/