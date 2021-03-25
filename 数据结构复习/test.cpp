// 没跑过
#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;

const int maxn=1005;
struct Node{
    int v;
    Node(){}
};
vector<vector<Node>>head;// 邻接表的头节点
int scc;//强连通分量的个数

vector<int>dfn;// 顶点访问的顺序
int cnt=0;// 当前时间戳
vector<int>low;// 子节点最早能访问的非父亲节点的节点的dfn的值

// 有向图中使用
vector<int>instack; // 当前节点是否在栈中,求割点与桥的时候不需要这个变量
vector<int>sstack;// 栈，求割点与桥不需要这个变量

// 无向连通图G中，一个顶点是割点
// 1、根结点u为割顶当且仅当它有两个或者多个子结点；
// 2、非根结点u为割顶当且仅当u存在结点v，使得v极其所有后代都没有反向边可以连回u的祖先（u不算）
// 第二个条件的代码中就是low[u]<=low[v]
// 一条边为桥
// 当且仅当该边的孩子节点没有反向边可以连向父亲或者是祖先节点
// 放在代码中就是low[u]<low[v]，少了一个=
void tarjan(int u){
    dfn[u]=low[u]=++cnt;// 0代表没有访问过
    int son=0;//记录根节点有多少孩子节点，根节点满足u==fat
    instack[u]=true;
    sstack.push_back(u);
    for(int i=0;i<head[u].size();i++){
        Node &node=head[u][i];
        int& v=node.v;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(instack[v]&&low[u]>dfn[v]){// 上面已经处理过重边，这边不需要处理
           low[u]=dfn[v];
        }
    }
    if(low[u]==dfn[u]){
        scc++;
        do{
            v=sstack[sstack.size()-1];
            sstack.pop_back();
            instack[v]=false;
            // belong[v]=scc;
            
        }
        while(v!=u)
    }
    // 根节点
    if(u==fat&&son>1){
        cut[u]=true;
    }
}


int main(){
    int n;
    int m;
    cin>>n>>m;
    head.resize(n); cut.resize(n);
    dfn.resize(n);
    low.resize(n);
    instack.resize(n);
    cnt=0;
    
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        head[u].push_back(v); 
        head[v].push_back(u); 
    }

    for(int i=0;i<n;i++){
        if(!dfn[i]){
            tarjan(i,i);
        }
    }
}