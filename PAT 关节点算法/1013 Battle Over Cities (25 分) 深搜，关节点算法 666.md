## 暴力算法

1. 每次深搜判断连通分量的个数$res$，然后结果就是$res-1$。
2. 每次的复杂度都是边的个数记为$e$，$O(e)$，那么$M$次查询总共的时间复杂度为$O(M*e)$。

```c++
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

vector<vector<int>>g;
vector<int>is;

int dfs(int u){
    is[u]=true;
    for(int j=0;j<g.size();j++){
        if(is[j]||!g[u][j])continue;
        dfs(j);
    }
}

int main(){
    int n,m,k;
    cin>>n>>m>>k;
    g.resize(n);
    for(int i=0;i<n;i++){
        g[i].resize(n);
        for(int j=0;j<n;j++){
             g[i][j]=0;
        }
    }
    int u,v;
    for(int i=0;i<m;i++){
        scanf("%d%d",&u,&v);
        g[u-1][v-1]=g[v-1][u-1]=1;
    }

    is.resize(n);
    int val;
    while(k--){
        scanf("%d",&val);
        fill(is.begin(),is.end(),false);
        is[val-1]=true;
        int cnt=0;
        for(int i=0;i<n;i++){
            if(!is[i]){
                dfs(i);
                cnt++;
            }
        }
        printf("%d\n",cnt-1);
    }
}
```

## 错了第三个点的代码

1. [关节点算法](https://www.cnblogs.com/yu-chao/archive/2011/12/17/2291403.html)
2. 采用上面的关节点算法的做法，时间复杂度$O(e)$，其中$e$为边的个数。

```c++
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

vector<vector<int>>g;
vector<int>is;
vector<int>pre,low;

int cnt=0;
int dfs(int u,int father){
    if(pre[u]==-1){
        pre[u]=low[u]=cnt++;
    }
    int k=0;
    for(int j=0;j<g.size();j++){
        if(!g[u][j]||j==u){
            continue;
        }
        if(pre[j]==-1){
            dfs(j,u);
            if(low[u]>low[j]){
                low[u]=low[j];
            }
            if(low[j]>=pre[u]){
                k++;
            }
        }
        else if(j!=father){
            if(low[u]>pre[j]){
                low[u]=pre[j];
            }
        }
    }
    if(k){
        is[u]=k;
    }
    return k;
}

int main(){
    int n,m,k;
    cin>>n>>m>>k;
    g.resize(n);
    for(int i=0;i<n;i++){
        g[i].resize(n);
        for(int j=0;j<n;j++){
             g[i][j]=0;
        }
    }
    int u,v;
    for(int i=0;i<m;i++){
        scanf("%d%d",&u,&v);
        g[u-1][v-1]=g[v-1][u-1]=1;
    }

    is.resize(n);
    pre.resize(n);
    low.resize(n);
    for(int i=0;i<n;i++){
        is[i]=false;
        pre[i]=-1;
        low[i]=-1;
    }
    for(int i=0;i<n;i++){
        if(pre[i]==-1){
            int k=dfs(i,-1);
            if(k<2){
                is[i]=false;
            }
            else{
                is[i]-=1;
            }
        }
    }
    int val;
    while(k--){
        scanf("%d",&val);
        printf("%d\n",is[val-1]);
    }
}
```

