## dijkstra+BFS

爆搜所有的路径直接找即可，边的数目为$M$，那么时间复杂度为$O(M)$

```cpp
// 过了四个点
#pragma warning(disable:4996)
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<string>

using namespace std;
const int INF = 0x3f3f3f3f;

int C, N, S, M;
vector<int>vs;
struct Node {
	int v, w;
	Node() {}
	Node(int v_, int w_) {
		v = v_;
		w = w_;
	}
};
vector<vector<Node>>e;

vector<int>path;// 记录到达终点的最短路径
vector<int>cur_path;//记录当前搜索的路径
vector<bool>vis;//记录到达当前节点最短路径上需要带的
int bike_in = INF, bike_out = INF, tmp_bike_in = 0, tmp_bike_out = 0;
int dist = INF, tmp_dist = 0;

void dfs(int cur) {
	if (cur == S) {
		if (dist > tmp_dist || dist == tmp_dist && bike_in > tmp_bike_in || dist == tmp_dist && bike_in == tmp_bike_in && bike_out > tmp_bike_out) {
			dist = tmp_dist;
			for (int i = 0; i < cur_path.size(); i++) {
				path[i] = cur_path[i];
			}
			bike_in = tmp_bike_in;
			bike_out = tmp_bike_out;
		}
		return;
	}
	
	for (auto& edge : e[cur]) {
		int& v = edge.v, &w = edge.w;
		if (vis[v]) {
			continue;
		}
		if (tmp_dist + w > dist) {
			continue;
		}
		tmp_dist += w;
		int prev_cur_path = cur_path[cur];
		cur_path[cur] = v;
		vis[cur] = true;
		if (vs[v] < C / 2) { // 当前位置需要补车
			if (tmp_bike_out - (C / 2 - vs[v]) >= 0) {// 需要带回的车多于当前位置需要补的车，不需要多带车
				tmp_bike_out -= (C / 2 - vs[v]);
				dfs(v);
				tmp_bike_out += (C / 2 - vs[v]);
			}
			else {
				int prev_bike_out = tmp_bike_out;
				int remain = (C / 2 - vs[v]) - tmp_bike_out;
				tmp_bike_out = 0;
				tmp_bike_in += remain;// 需要多带remain这么多的车
				dfs(v);
				tmp_bike_out = prev_bike_out;// 恢复
				tmp_bike_in -= remain;
			}
		}
		else {
			tmp_bike_out += vs[v] - (C / 2);
			dfs(v);
			tmp_bike_out -= (vs[v] - (C / 2));
		}
		tmp_dist -= w;
		cur_path[cur] = prev_cur_path; 
		vis[cur] = false;// 注意这个vis的状态也要恢复
	}
}

int main() {
	cin >> C >> N >> S >> M;
	vs.resize(N + 1);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &vs[i]);
	}
	e.resize(N + 1);
	int u, v, w;
	for (int i = 1; i <= M; i++) {
		scanf("%d%d%d", &u, &v, &w);
		e[u].push_back(Node(v, w));
		e[v].push_back(Node(u, w));
	}

	vis.resize(N + 1);
	path.resize(N + 1);
	cur_path.resize(N + 1);
	dfs(0);

	cout << bike_in << " ";
	int pos = 0;
	while (pos != S) {
		cout << pos << "->";
		pos = path[pos];
	}
	cout << S << " " << bike_out << endl;
}
```



## dijkstra+贪心

[思路来自这里](https://blog.csdn.net/weixin_43116322/article/details/103840390)

摘抄:

用Dijkstra和贪心算法。
用状态转移方程描述发出的车数：

sendNum = max(send[u], (passByNum[u] + 1) * (capacity / 2) - (bikeSum[u] + bikeNum[v]));	//当到达v站时，需要发出的车数 = 到达u站需要发出的车数、到达v站需要发出的车数中的较大者

当最短路更新时直接更新send[v] = sendNum
当一条路和最短路长度相等时send[v] = min(sendNum, send[v])
以上仅根据子问题最优解逐步确定整体的最优解的方法是错误的，举个例子：

如果运用贪心算法，当计算的站点到达两条路交汇点，当前最优路径必然为下面的那条路，因为它当前只需要发出2辆车，且只收回的车数也更少。但是当计算继续向右进行，发现后面的站点车数很少，由于下面那条路的总车数比上面那条路的总车数少，最后计算得到的发车数send反而比走上面的那条路的更多，显然贪心算法不能解决这个问题。
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<string>
#include<list>

using namespace std;
const int INF=0x3f3f3f3f

int C,N,S,M;
vector<int>vs;		// 存放顶点的权值
struct Node{
    int v,w;		// 下一个顶点的序号和边的权值
    Node(){}
    Node(int v_,int w_){
        v=v_;
        w=w_;
    }
};
vector<vector<Node>>e;	// 存放所有的边，临接表的存储结构
vector<int>dist;    	// 顶点0到其它节点的距离
vector<int>num;     	// 到达当前节点认为最优的一条路发现的车辆的总数目
vector<int>station_num;	// 到达当前节点认为最优的一条路发现的车站的总数目
vector<int>send;		// 到当前所在站点为止，可能发送的最大的车站的数量
vector<int>path;		// 到达当前节点认为最优的一条路的路径

vector<int>cnt;     		// 起点到其它城市的路径的数量,用不到
vector<vector<int>>prevs; 	// 记录所有的路径,可以根据这个路径打印出所有的路径，没用到
//struct Node1{
//    int index=0;
//    int sum_num=0;
//    int node_num=0;
//    vector<Node1*>next;
//    Node1(){}
//    Node1(int index_,int sum_num_){
//        index=index_;
//        sum_num=sum_num_;
//    }
//};
//vector<Node1>tree;
//vector<int>path_min,path_max,path_cur;//记录路径
//int min_val=INF,max_val=0;
//int res1=INF,res2=INF;//带回，带去

//void getPaths(int cur_v,Node1*prev){
//    if(cur_v==0){
//        if(prev->sum_num>=C*prev->node_num/2&&min_val>prev->sum_num){
//            path_max.clear();
//            for(int i=0;i<path_cur.size();i++){
//                path_min.push_back(path_cur[i]);
//            }
//            res1=min(prev->sum_num-C*prev->node_num/2,res1);   //带回
//        }
//        if(prev->sum_num<C*prev->node_num/2&&max_val<prev->sum_num){
//            max_val=prev->sum_num;
//            path_max.clear();
//            for(int i=0;i<path_cur.size();i++){
//                path_max.push_back(path_cur[i]);
//            }
//            res2=min(res2,C*prev->node_num/2-prev->sum_num);//带去
//        }
//        return;
//    }
//    for(int i=0;i<prevs[cur_v].size();i++){
//        Node1* node_tmp=new Node1(cur_v,prev->sum_num+vs[cur_v]);
//        node_tmp->node_num=prev->node_num+1;
//        vector<Node1*>&next=prev->next;
//        next.push_back(node_tmp);
//        path_cur.push_back(cur_v);
//        getPaths(prevs[cur_v][i],node_tmp);
//        path_cur.pop_back();
//    }
//}

void dijkstra(int n,int target){
    dist.resize(n,INF);
    num.resize(n,0);
    station_num.resize(n,0);
    send.resize(n,INF);
    path.resize(n,0);

    cnt.resize(n,0);
    prevs.resize(n);//到达顶点i的最短路径的上一个节点的序号);
    vector<bool>vis(n,false);
    dist[0]=0;
    num[0]=0;
    station_num[0]=0;
    send[0]=0;
    cnt[0]=1;
//    for(Node&node:e[0]){
//        int &v=node.v;
//        int &w=node.w;
//        dist[v]=w;
//        station_num[v]=1;
//        num[v]=vs[v];
//    }

    for(int i=0;i<n;i++){
        int pos=-1,val=INF;
        for(int j=0;j<n;j++){
            if(!vis[j]&&val>dist[j]){
                val=dist[j];
                pos=j;
            }
        }
        if(pos==-1){
            return;
        }
        vis[pos]=true;
        for(Node&node:e[pos]){
            int &v=node.v;
            int &w=node.w;
            if(vis[v]){continue;}
            int send_num=max(send[pos],(station_num[pos]+1)*C/2-(num[pos]+vs[v]));// 第二项是当前还需要多少车,这样更新可能出现的问题就是前面已有的车很多，弥补了后面的车，导致实际上需要发车但是没有发车，所以这是一种近似最优的解法
            if(dist[v]>dist[pos]+w){
                dist[v]=dist[pos]+w;
                station_num[v]=station_num[pos]+1;
                num[v]=num[pos]+vs[v];
                send[v]=send_num;
                path[v]=pos;

                cnt[v]=cnt[pos];
                prevs[v].clear();   // 一个点可能被更新多次，这个需要保留
                prevs[v].push_back(pos);
            }
            else if(dist[v]==dist[pos]+w&&(send_num<send[v]||send_num==send[v]&&send[v]+num[v]-station_num[v]*C/2>send_num+num[pos]+vs[v]-station_num[v]*C/2)){
                station_num[v]=station_num[pos]+1;
                num[v]=num[pos]+vs[v];
                send[v]=send_num;
                path[v]=pos;

                cnt[v]+=cnt[pos];
                prevs[v].push_back(pos);
            }
        }
    }
}

int main(){
    cin>>C>>N>>S>>M;
    vs.resize(N+1,0);
    for(int i=1;i<=N;i++){
        scanf("%d",&vs[i]);
    }
    e.resize(N+1);
    int u,v,w;
    for(int i=1;i<=M;i++){
        scanf("%d%d%d",&u,&v,&w);
        e[u].push_back(Node(v,w));
        e[v].push_back(Node(u,w));
    }
    dijkstra(N+1,S);
//    Node1 root;
//    root.index=prevs.size()-1;//根节点
//    root.sum_num=0;
//    root.node_num=0;
//    getPaths(prevs.size()-1,&root);
//    if(res1!=INF){
//        cout<<0<<" 0";
//        for(int i=path_min.size()-1;i>=0;i--){
//            cout<<"->"<<path_min[i];
//        }
//        cout<<" "<<res1<<endl;
//        return 0;
//    }
//
//    if(res2!=INF){
//        cout<<res2<<" 0";
//        for(int i=path_max.size()-1;i>=0;i--){
//            cout<<"->"<<path_max[i];
//        }
//        cout<<" "<<0<<endl;
//        return 0;
//    }
//    for(int i=0;i<path.size();i++){
//        cout<<path[i]<<" ";
//    }
//    cout<<endl;
    list<int>res;
    int cur=S;
    while(cur){
        res.push_front(cur);
        cur=path[cur];
    }
    res.push_front(0);

    cout<<send[S]<<" ";
    for(list<int>::iterator it=res.begin();it!=res.end();it++){
        if(it!=res.begin()){
            cout<<"->";
        }
        cout<<*it;
    }
    int back_=(send[S]+num[S])-(station_num[S]*C)/2;
    if(back_<0){
        back_=0;
    }
    cout<<" "<<back_<<"\n";
    return 0;
}


```

## 记录所有的路径，然后找到花费最短的路径的方法，过四个点

1. 首先在dijkstra的过程中记录所有的最短路径，并记录路径上的所有的自行车的数量num和路径经过的顶点的个数num_v。
2. 如果带去自行车，那么$num<num\_v*C/2$，取最靠近$num\_v*C$的那一条路径。记录为1
3. 如果带回自行车，那么$num>num\_v*C/2$，取最靠近$num\_v*C$的那一条路径。记录为2
4. 我们首先希望尽量少的带去自行车，其次希望尽量少的带回自行车，那么自然的，记录1的优先级大于记录2的优先级。
5. 似乎忘了考虑在路径上如果遇见不够的，需要从老家带东西过去补的情况了、
6. 重写、

```cpp
// 过了四个点
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<string>

using namespace std;
const int INF=0x3f3f3f3f;

int C,N,S,M;
vector<int>vs;
struct Node{
    int v,w;
    Node(){}
    Node(int v_,int w_){
        v=v_;
        w=w_;
    }
};
vector<vector<Node>>e;
vector<int>dist;    // 距离
vector<int>cnt;     // 起点到其它城市的路径的数量

vector<vector<int>>prevs; // 记录所有的路径,可以根据这个路径打印出所有的路径吗？
struct Node1{
    int index=0;
    int sum_num=0;
    int node_num=0;
    vector<Node1*>next;
    Node1(){}
    Node1(int index_,int sum_num_){
        index=index_;
        sum_num=sum_num_;
    }
};
vector<Node1>tree;
vector<int>path_min,path_max,path_cur;//记录路径
int min_val=INF,max_val=0;
int res1=INF,res2=INF;//带回，带去

void getPaths(int cur_v,Node1*prev){
    if(cur_v==0){
//        cout<<"sum: "<<prev->sum_num<<" "<<prev->node_num<<endl;
        if(prev->sum_num>=C*prev->node_num/2&&min_val>prev->sum_num){
            path_max.clear();
            for(int i=0;i<path_cur.size();i++){
                path_min.push_back(path_cur[i]);
            }
            res1=min(prev->sum_num-C*prev->node_num/2,res1);   //带回
        }
        if(prev->sum_num<C*prev->node_num/2&&max_val<prev->sum_num){
            max_val=prev->sum_num;
            path_max.clear();
            for(int i=0;i<path_cur.size();i++){
                path_max.push_back(path_cur[i]);
            }
            res2=min(res2,C*prev->node_num/2-prev->sum_num);//带去
        }
        return;
    }
    for(int i=0;i<prevs[cur_v].size();i++){
        Node1* node_tmp=new Node1(cur_v,prev->sum_num+vs[cur_v]);
        node_tmp->node_num=prev->node_num+1;
        vector<Node1*>&next=prev->next;
        next.push_back(node_tmp);
        path_cur.push_back(cur_v);
        getPaths(prevs[cur_v][i],node_tmp);
        path_cur.pop_back();
    }
}

void dijkstra(int n,int target){
    dist.resize(n,INF);
    cnt.resize(n,0);
    prevs.resize(n);//到达顶点i的最短路径的上一个节点的序号);
    vector<bool>vis(n,false);
    dist[0]=0;
    cnt[0]=1;
    for(Node&node:e[0]){
        int &v=node.v;
        int &w=node.w;
        dist[v]=w;
    }

    for(int i=0;i<n;i++){
        int pos=-1,val=INF;
        for(int j=0;j<n;j++){
            if(!vis[j]&&val>dist[j]){
                val=dist[j];
                pos=j;
            }
        }
        if(pos==-1){
            return;
        }
        vis[pos]=true;
        for(Node&node:e[pos]){
            int &v=node.v;
            int &w=node.w;
            if(dist[v]>dist[pos]+w){
                dist[v]=dist[pos]+w;
                cnt[v]=cnt[pos];
                prevs[v].clear();   // 一个点可能被更新多次，这个需要保留
                prevs[v].push_back(pos);
            }
            else if(dist[v]==dist[pos]+w){
                cnt[v]+=cnt[pos];
                prevs[v].push_back(pos);
            }
        }
    }
}

int main(){
    cin>>C>>N>>S>>M;
    vs.resize(N+1,0);
    for(int i=1;i<=N;i++){
        scanf("%d",&vs[i]);
    }
    e.resize(N+1);
    int u,v,w;
    for(int i=1;i<=M;i++){
        scanf("%d%d%d",&u,&v,&w);
        e[u].push_back(Node(v,w));
        e[v].push_back(Node(u,w));
    }
    dijkstra(N+1,S);
    Node1 root;
    root.index=prevs.size()-1;//根节点
    root.sum_num=0;
    root.node_num=0;
    getPaths(prevs.size()-1,&root);
    if(res1!=INF){
        cout<<0<<" 0";
        for(int i=path_min.size()-1;i>=0;i--){
            cout<<"->"<<path_min[i];
        }
        cout<<" "<<res1<<endl;
        return 0;
    }
    // 找到所有的路径
//    cout<<"size: "<<prevs.size()<<endl;
//    for(int i=0;i<prevs.size();i++){
//        for(int val:prevs[i]){
//            cout<<val<<" ";
//        }
//        cout<<endl;
//    }
    if(res2!=INF){
        cout<<res2<<" 0";
        for(int i=path_max.size()-1;i>=0;i--){
            cout<<"->"<<path_max[i];
        }
        cout<<" "<<0<<endl;
        return 0;
    }
    return 0;
}


```

