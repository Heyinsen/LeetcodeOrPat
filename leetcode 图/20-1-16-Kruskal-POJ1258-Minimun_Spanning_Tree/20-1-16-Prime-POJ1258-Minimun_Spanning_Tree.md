## POJ1258

* Agri-Net

    | **Time Limit:** 1000MS       |      | **Memory Limit:** 10000K |
    | ---------------------------- | ---- | ------------------------ |
    | **Total Submissions:** 77439 |      | **Accepted:** 31957      |
    
    Description
    
    Farmer John has been elected mayor of his town! One of his campaign promises was to bring internet connectivity to all farms in the area. He needs your help, of course.
    Farmer John ordered a high speed connection for his farm and is going to share his connectivity with the other farmers. To minimize cost, he wants to lay the minimum amount of optical fiber to connect his farm to all the other farms.
    Given a list of how much fiber it takes to connect each pair of farms, you must find the minimum amount of fiber needed to connect them all together. Each farm must connect to some other farm such that a packet can flow from any one farm to any other farm.
    The distance between any two farms will not exceed 100,000.
    
    Input
    
    The input includes several cases. For each case, the first line contains the number of farms, N (3 <= N <= 100). The following lines contain the N x N conectivity matrix, where each element shows the distance from on farm to another. Logically, they are N lines of N space-separated integers. Physically, they are limited in length to 80 characters, so some lines continue onto others. Of course, the diagonal will be 0, since the distance from farm i to itself is not interesting for this problem.
    
    Output
    
    For each case, output a single integer length that is the sum of the minimum length of fiber required to connect the entire set of farms.
    
    Sample Input
    
    ```
    4
    0 4 9 21
    4 0 8 17
    9 8 0 16
    21 17 16 0
    ```
    
    Sample Output
    
    ```
    28
    ```
    
    Source
    
    [USACO 102](http://poj.org/searchproblem?field=source&key=USACO+102)
    
    * kruskal水题
    
        ```c++
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
        const int MAXM = 9000000;//最大边数
        
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
        		if (cnt == n - 1)break;
        	}
        	if (cnt < n - 1)return -1;//不连通
        	else return ans;
        }
        
        
        int main() {
        
        	int n;
        	while (scanf("%d", &n) != EOF) {
        		//int u, v;
        		int cost;
        		tol = 0;
        		for (int i = 0; i < n; i++) {
        			for (int j = 0; j < i; j++) {
        				scanf("%d", &cost);
        				addEdge(i, j, cost);
        			}
        			scanf("%d", &cost);
        			for (int j = i + 1; j < n; j++) {
        				scanf("%d", &cost);
        			}
        		}
        		cout << kruskal(n) << "\n";
        	}
        }
        /*
        4
        0 4 9 21
        4 0 8 17
        9 8 0 16
        21 17 16 0
        */
        ```
    
        

