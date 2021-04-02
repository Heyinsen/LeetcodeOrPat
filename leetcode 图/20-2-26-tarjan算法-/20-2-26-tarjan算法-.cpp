#pragma warning(disable:4996)
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN = 110;
const int MAXM = 110 * 110;
const int maxn = 55;
const int INF = 0x3f3f3f3f;
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<queue>
#include<cstdio>
#include<string>
#include<math.h>
#include<algorithm>
#include<map>
#include<set>
#include<stack>
#define mod 998244353
#define INF 0x3f3f3f3f
#define eps 1e-6
using namespace std;
typedef long long ll;
#define MAXN 1003
#define MAXM 40004
//最小费用最大流
struct Edge{
    int to,next;
    int flow,cost,cap;
}edge[MAXM];
int tol,head[MAXN];
void init()
{
    tol=0;
    memset(head,-1,sizeof head);
}
void addEdge(int u,int v,int cap,int cost){
    edge[tol].to=v;
    edge[tol].cap=cap;
    edge[tol].cost=cost;
    edge[tol].flow=0;
    edge[tol].next=head[u];
    head[u]=tol++;
 
    edge[tol].to=u;
    edge[tol].cap=0;
    edge[tol].cost=-cost;
    edge[tol].flow=0;
    edge[tol].next=head[v];
    head[v]=tol++;
}
 
bool inq[MAXN];//标记是否点是否在队列
int dis[MAXN];//最短距离
int pre[MAXN];//记录路径
int q[MAXN*10];//队列
//单位费用可能是负值，所以用SPFA
bool spfa(int st,int en)
{
    memset(inq,0,sizeof inq);
    memset(dis,INF,sizeof dis);
    memset(pre,-1,sizeof pre);
 
    int rear=0,front=0;
    dis[st]=0;
    inq[st]=true;
    q[front++]=st;
    while(rear<front){
        int u=q[rear++];
        inq[u]=false;
 
        for(int e=head[u];e!=-1;e=edge[e].next){
            int v=edge[e].to;
            if(edge[e].cap>edge[e].flow&&dis[v]>dis[u]+edge[e].cost){
                dis[v]=dis[u]+edge[e].cost;
                pre[v]=e;//表示边e-->v,e就是v的前驱
                if(!inq[v])
                    inq[v]=true,q[front++]=v;
            }
        }
    }
    return pre[en]!=-1;
}
int minCostMaxFlow(int st,int en,int &cost,int &flow)
{
    //如果能找到从源点到汇点的最短路，说明还没有达到最小费用最大流
    while(spfa(st,en)){
        int Min=INF;//最小残余流量
        //沿着当前路径返回
        for(int i=pre[en];i!=-1;i=pre[edge[i^1].to]){
            int rem=edge[i].cap-edge[i].flow;
            Min=Min>rem?rem:Min;
        }
        for(int i=pre[en];i!=-1;i=pre[edge[i^1].to]){
            edge[i].flow+=Min;//正向边添加残余流量
            edge[i^1].flow-=Min;//反向边减少残余流量
            cost+=Min*edge[i].cost;
        }
        flow+=Min;
    }
}
//以上为最小费用最大流模板
 
int n,m;
struct point{
    int x,y;
}house[MAXN],men[MAXN];
char str[110];
int main()
{
    while(scanf("%d%d",&n,&m)&&n&&m){
        init();
        int houseNum=1,menNum=1;
        for(int i=0;i<n;i++){
            scanf("%s",str);
            for(int j=0;j<m;j++){
                if(str[j]=='H')
                house[houseNum].x=i,house[houseNum].y=j,houseNum++;
 
                if(str[j]=='m')
                men[menNum].x=i,men[menNum].y=j,menNum++;
            }
        }
        int st=0;
        int en=houseNum+menNum-1;
 
        for(int i=1;i<menNum;i++){
            for(int j=1;j<houseNum;j++){
                int w=abs(men[i].x-house[j].x)+abs(men[i].y-house[j].y);
                addEdge(i,menNum+j-1,1,w);
            }
        }
 
        for(int i=1;i<menNum;i++){
            addEdge(0,i,1,0);
            addEdge(menNum+i-1,en,1,0);
        }
 
        int cost=0,flow=0;
        minCostMaxFlow(st,en,cost,flow);
        printf("%d\n",cost);
    }
}
int head[MAXN];
struct Edge {
	int u, v, cap, cost, next;
	Edge(int u_ = 0, int v_ = 0, int cap_ = 0, int cost_ = 0, int next_ = 0) {
		u = u_;
		v = v_;
		cap = cap_;
		cost = cost_;
		next = next_;
	}
}edge[MAXM];
int num_of_vertices;
int cur_edge_index;
int source, meet;//源点和汇点的序号

void addEdge(int u, int v, int cap, int cost) {
	//正向边
	edge[cur_edge_index].u = u; //
	edge[cur_edge_index].v = v;
	edge[cur_edge_index].cap = cap;
	edge[cur_edge_index].cost = cost;
	edge[cur_edge_index].next = head[u];
	head[u] = cur_edge_index++;

	//设置反向边
	edge[cur_edge_index].u = v; //
	edge[cur_edge_index].v = u;
	edge[cur_edge_index].cap = 0;
	edge[cur_edge_index].cost = -cost;
	edge[cur_edge_index].next = head[v];
	head[v] = cur_edge_index++;
}
//该顶点是在队列
bool vis[MAXN];
int d[MAXN];
int pre[MAXN];
bool spfa() {
	for (int i = 0; i < num_of_vertices; i++) {
		vis[i] = false;
		d[i] = INF;
	}
	vis[source] = true;
	d[source] = 0;

	queue<int> q;
	while (!q.empty()) {
		q.pop();
	}
	q.push(source);
	while (!q.empty()) {
		int u = q.front(); 
		q.pop();
		for (int i = head[u]; i != -1; i = edge[i].next) {
			int v = edge[i].v;
			//仍然存在曾广路并且优先每次找到最小费用的增广路
			if (edge[i].cap && d[v] > d[u] + edge[i].cost) {
				d[v] = d[u] + edge[i].cost;
				pre[v] = i;
				//这里的不会出现负权回路, 无需判环
				if (!vis[v]) {
					vis[v] = true;
					q.push(v);
				}
			}
		}
		vis[u] = false;
	}
	return d[meet] < INF;
}
int MCMF() {
	int res = 0;
	//找到一条增广路
	while (spfa()) {
		//路径回溯, 路径上的flow全部加上
		int flow = INF;
		int cost = 0;
		for (int u = meet; u != source; u = edge[pre[u]].u) {
			flow = min(flow, edge[pre[u]].cap);
		}
		for (int u = meet; u != source; u = edge[pre[u]].u) {
			edge[pre[u]].cap -= flow;
			edge[pre[u] ^ 1].cap += flow;
			cost += flow * edge[pre[u]].cost;
		}
		res += cost;
	}
	return res;
}

//(0,maxn)
int n, m, k;//n个shopkeeper, m个supplies place, 需要k types commodities
int g[maxn][maxn][maxn];

int to[maxn][maxn];//to[i][j]代表第i个商家需要的第j种商品的个数
int from[maxn][maxn];//from[i][j]代表第i个supper提供的第j种商品的个数

bool isEnough(int* needs, int* supplies) {
	for (int i = 0; i < k; i++) {
		if (needs[i] > supplies[i])
			return false;
	}
	return true;
}

int main() {
	int supplies[maxn];
	int needs[maxn];//needs[i]代表所有商家一共需要的第i种商品的个数
	while (~scanf("%d%d%d", &n, &m, &k) && (n || m || k)) {
		memset(supplies, 0, sizeof(supplies));
		memset(needs, 0, sizeof(needs));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < k; j++) {
				scanf("%d", &to[i][j]);
				needs[j] += to[i][j];
			}
		}
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < k; j++) {
				scanf("%d", &from[i][j]);
				supplies[j] += from[i][j];
			}
		}

		for (int i = 0; i < k; i++) {
			for (int x = 0; x < n; x++) {
				for (int y = 0; y < m; y++) {
					scanf("%d", &g[i][x][y]);
				}
			}
		}
		if (isEnough(needs, supplies) == false) {
			puts("-1");
			continue;
		}
		//源点和汇点的序号
		source = n + m;
		meet = n + m + 1;
		num_of_vertices = n + m + 2;

		int res = 0;
		//处理每一件商品
		for (int t = 0; t < k; ++t) {
			memset(head, -1, sizeof(head));
			cur_edge_index = 0;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					//这里是j到i
					addEdge(j, i + m, INF, g[t][i][j]);
				}
			}
			//源点和汇点加边, m个供应商, n个shopkeepers
			for (int i = 0; i < m; i++) {
				addEdge(source, i, from[i][t], 0);
			}
			for (int i = 0; i < n; i++) {
				addEdge(i + m, meet, to[i][t], 0);
			}
			res += MCMF();
		}
		printf("%d\n", res);
	}
	return 0;
}