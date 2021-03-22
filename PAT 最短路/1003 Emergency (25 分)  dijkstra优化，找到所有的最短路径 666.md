1.  原本想dijkstra算出最小的距离后，然后bfs+剪枝去找出所有满足条件的路径，时间卡的有点紧，过前三个点，相关的bfs的代码以 \"// 没有用到，// 结束没有用到框出"，实际最后没用到

2.  对dijkstra算法进行改进：

    1.  dijkstra更新最短路径的过程中需要更新num\[]数组（num\[i]代表从开始点到点i已经累计的救援队的数量）和cnt\[]（cnt\[i]代表从开始点到点i已经累计的路线的数量）数组，需要维护这两个数组，对于这两个数组的维护和对dijkstra的修改，需要注意的细节很多，在这里需要注意

        *   对于vis\[i]数组的使用，需要注意：

        *   ```c++
            // 下面的这句话不能写，即使是下面的循环for(int i=0;i<n;i++)写成for(int i=0;i<n-1;i++)也不行，因为这样会使得num和cnt数组没有维护好
            // vis[beg_]=true;
            cnt[beg_]=1;
            num[beg_]=vs[beg_];
            
            // 这么写会导致num[]和cnt[]数组没有更新好
            ```

        *   ```c++
            // 这里更新一个dist[j]不要维护vis[]数组，因为如果维护了这个vis数组，下面的else中更新路径的选项就永远不会进入
            // 注意这里的num和cnt的维护
            
            for(int j=0;j<n;j++){
                 // 没写!vis[j]因为需要持续更新num[]和cnt[]
                 if(g[min_pos][j]+min_val<dist[j]){
                     dist[j]=g[min_pos][j]+min_val;
                     num[j]=num[min_pos]+vs[j];
                     // 这里容易写错，原本写的cnt[j]=1
                     cnt[j]=cnt[min_pos];
                     // vis[j]=true;
                 }
                 else if(g[min_pos][j]+min_val==dist[j]){
                     num[j]=max(num[min_pos]+vs[j],num[j]);
                     cnt[j]+=cnt[min_pos];
                 }
            ```

        *   ```c++
            // 没直接返回是为了持续更新上面的cnt和num数组
            // if(vis[end_]){
            //     return dist[end_];
            // }
            
            // 为了维护好cnt和num,同样的，这里不要直接返回
            ```

3.  [原解答](https://www.cnblogs.com/-citywall123/p/12088433.html)
4.  [使用vector的一种解法](https://blog.csdn.net/qq_41658889/article/details/82492985)

```c++
#include<cstdio>
#include<iostream>
#include <algorithm>
#include<vector>
#include <queue>
using namespace std;
const int MAXN=505;
const int INF=0x3f3f3f3f;

int vs[MAXN];	// 点的权值
int g[MAXN][MAXN];	// 存放图数据的矩阵，不可达为INF
int routes=0;	// 存放最终beg_到end_的发现的路线的数量
int max_people=0;	// 存放最终beg_到end_的最多聚集的救援队的数量
int cnt[MAXN];	// 起点到其它城市的路径的数量
int num[MAXN];	// 起点到其它城市的获得的救援队的数量

int dijkstra(int beg_,int end_, int n, int m){
    bool vis[MAXN]={false};	// 代表顶点i是否被浏览过
    int dist[MAXN]={0};	
    for(int i=0;i<n;i++){
        dist[i]=g[beg_][i];
    }
    dist[beg_]=0;
    // 下面的这句话不能写，即使是下面的循环for(int i=0;i<n;i++)写成for(int i=0;i<n-1;i++)也不行，因为这样会使得num和cnt数组没有维护好
    // vis[beg_]=true;
    cnt[beg_]=1;
    num[beg_]=vs[beg_];


    for(int i=0;i<n;i++){
        // 先找到最短的距离
        int min_val=INF,min_pos=-1;
        for(int j=0;j<n;j++){
            if(!vis[j]&&min_val>=dist[j]){
                min_val=dist[j];
                min_pos=j;
            }
        }
        if(min_pos==-1){
            return INF;
        }
        vis[min_pos]=true;
        for(int j=0;j<n;j++){
            // 没写!vis[j]因为需要持续更新num[]和cnt[]
            if(g[min_pos][j]+min_val<dist[j]){
                dist[j]=g[min_pos][j]+min_val;
                num[j]=num[min_pos]+vs[j];
                // 这里容易写错，原本写的cnt[j]=1
                cnt[j]=cnt[min_pos];
                // vis[j]=true;
            }
            else if(g[min_pos][j]+min_val==dist[j]){
                num[j]=max(num[min_pos]+vs[j],num[j]);
                cnt[j]+=cnt[min_pos];
            }

        }
        // 没直接返回是为了持续更新上面的cnt和num数组
        // if(vis[end_]){
        //     return dist[end_];
        // }

    }
    routes=cnt[end_];
    max_people=num[end_];
    return dist[end_];
}


// 没有用到
struct Node{
    int first;
    int second;
    int third;
    Node(){}
    Node(int first_,int second_,int third_){
        this->first=first_;
        this->second=second_;
        this->third=third_;
    }
};
queue<Node>q;
void bfs(int beg_,int end_,int n,int m,int short_dis){
    q.push(Node(beg_,0, vs[beg_]));
    while(!q.empty()){
        Node top=q.front();
        q.pop();
        int cost_already=top.second;
        int cur_place=top.first;
        int people_already=top.third;
        if(cur_place==end_&&cost_already==short_dis){
            routes++;
            if(max_people<people_already){
                max_people=people_already;
            }
        }
        for(int i=0;i<n;i++){
            Node node;
            if(cost_already+g[cur_place][i]<=short_dis){
                node.second=cost_already+g[cur_place][i];
                node.first=i;
                node.third=people_already+vs[i];
                q.push(node);
            }
        }
    }
    return;
}
// 结束没有用到

int main(){
    int n,m;
    int beg_,end_;
    scanf("%d%d%d%d",&n,&m,&beg_,&end_);
    int tmp;
    for(int i=0;i<n;i++){
        scanf("%d",&tmp);
        vs[i]=tmp;
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            g[i][j]=INF;
        }
    }
    int u,v,w;
    for(int i=0;i<m;i++){
        scanf("%d%d%d",&u,&v,&w);
        g[u][v]=g[v][u]=w;
        // 没有对边进行去重
    }
//    if(n==0){
//        printf("%d %d\n",0,0);
//        return 0;
//    }
//    else if(beg_==end_){
//        printf("%d %d\n",1,vs[beg_]);
//        return 0;
//    }

    int short_dis=dijkstra(beg_,end_,n,m);
//    cout<<"short_dis: "<< short_dis<<endl;
//    bfs(beg_,end_,n,m,short_dis);
    printf("%d %d\n",routes,max_people);
    return 0;
}

```

