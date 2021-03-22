## 解体思路

1. 寻找到所有的叶子节点，进行dfs，记录深度，最后输出即可。、
2. 又犯了zz错误，自罚三杯。

## 代码

```c
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int n;
struct Node{
    int v;
    Node(int v_=0):v(v_){}
};
vector<vector<Node>>e;


int num_component=0;
vector<bool>vis;
int dfs(int u){
    if(vis[u]){
        return 1;
    }
    vis[u]=true;
    for(Node&node:e[u]){
        int &v=node.v;
        if(!vis[v]){
            dfs(v);
        }
    }
    return 0;
}

vector<int>depths;
vector<int>res;
int dfs1(int u){
    if(vis[u]){
        return 0;
    }
    vis[u]=true;
    int max_depth=1;
    for(Node&node:e[u]){
        int &v=node.v;
        if(!vis[v]){
            max_depth=max(max_depth,dfs1(v)+1);
        }
    }
    return max_depth;
}

int main(){
    cin>>n;
    e.resize(n+1);
    vis.resize(n+1);
    depths.resize(n+1,1);
    int u,v;
    Node node;
    for(int i=0;i<n-1;i++){
        scanf("%d%d",&u,&v);
        node.v=v;
        e[u].push_back(node);
        node.v=u;
        e[v].push_back(node);
    }
    if(n<=0){
        cout<<"Error: "<<0<<" components\n";
        return 0;
    }
    for(int i=1;i<=n;i++){
        if(dfs(i)==0){
            num_component++;
        }
    }
    if(num_component!=1){
        cout<<"Error: "<<num_component<<" components\n";
        return 0;
    }

    int max_depth=1;
    for(int i=1;i<=n;i++){
        fill(vis.begin(),vis.end(),false);
        // 这里写成e[v].size()了，智障错误
        if(e[i].size()==1){
            depths[i]=dfs1(i);
            max_depth=max(max_depth,depths[i]);
        }
    }
    for(int i=1;i<=n;i++){
        if(depths[i]==max_depth){
            res.push_back(i);
        }
    }
    sort(res.begin(),res.end());
    for(int i=0;i<res.size();i++){
        cout<<res[i]<<"\n";
    }
    return 0;
}
```

**上面的方法时间复杂度是不稳定的**，下面我们考虑进行优化。

首先我们找到任意的一个点比如就是$s$号节点，从这个点出发dfs求得一个最大的深度，可以知道这样求得的这个最大路径的终端节点集合记为集合$A$，元素$a_i\in A$，那么我们从$A$ 的任意一个节点$a_i$出发再进行一次$dfs$找到的最长路径的终端节点的集合记为集合$B$，那么集合$A$和$B$的并集就是我们的答案。

为什么？首先我们知道，假设我们知道这个图中的最长的路径，我们任意取一条最长的路径，端点记为$a$和$b$，那么我们从$a$或者$b$中的任意一个出发取dfs必定能找到最长的路径，并且能够找到以$a(假设从a出发去dfs)$开始的所有的最长路径。

直接看有点抽象，我们来看一张图：

![image-20210319004026587](1021 Deepest Root (25 分) dfs，求树的深度/image-20210319004026587.png)

图1看着有点抽象，我们来看图2，可以看到，我们要求从这个图的最长的路径，定义$d[s]$为$s$点离开始的不经过$s$点的最长路径的长度，随便找到的$s$点，那么经过$s$ 点的最长的路径，一定是和$s$ 点相连的所有的节点（变成以$s$点为根的树的话，那么$d[s]$定义为以$s$为根，$s$为开始节点的最长路径的长度）中选出最大的两个$d[s]$加上$s$节点产生的长度$1$，可以清晰的从上图看出，不管选出的点是$s$这样的关节点，还是叶子节点，这样一搜找到的集合$A$中的元素都最长路径的终端节点。

下面是证明：全局最优解一定是局部最优解。

全局的最深根也一定是局部的最深根，全局的最深根的端点记为集合$A$，$A$中两个元素$a_1和a_2$是最长路径的两个端点，从图中任意一点$S$出发，假设从其出发找到的最优解不在集合$A$中，记为节点$d$，那么$S-d$ 的距离比$S-A中任意一个元素的距离$大，如果$a_1-a_2$ 经过$S$，显然$a_1-S-d$ 的距离显然最长，这和最深的假设矛盾，如果$a_1-a_2$不经过$S$，由于$S$将整个图分成多个部分，并且$S$是所谓的关节点，那么$a_1和a_2$必定在$S$ 的一边，假如$d$和$a_1,a_2$ 不在一边，那么由于$d-S$和$d-a_1/a_2$的距离相等，而$a_1/a_2$ 到S，再从$S-d$ 的距离和比$a_1-a_2$ 的距离大，这和$a_1-a_2$是最长的距离矛盾，假如$d$和$a_1,a_2$在一边，那么$S-a1/a2$的距离和$S-d$的距离一定是相等的，这和$d \notin A$又是矛盾的，因此$d \in A$，得证。

其实我们可以把最长的路径看作干流，其它的不属于最长路径的看作支流，从支流上的点或者干流上的点找最长一定得通过干流把，否则干流不足以称之为干流，支流不足以称之为支流。

```c++
#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;

vector<bool>vis;
vector<vector<int>>vs;
bool dfs(int i) {
	if (vis[i]) {
		return false;
	}
	vis[i] = true;
	for (auto& v : vs[i]) {
		if (!vis[v]) {
			dfs(v);
		}
	}
	return true;
}

int maxDepth = 0;
vector<int>res;
vector<int>res1;
void dfs1(int u, int curDepth, vector<int>& res) {
	if (curDepth > maxDepth) {
		res.clear();
		res.push_back(u);
		maxDepth = curDepth;
	}
	else if (curDepth == maxDepth) {
		res.push_back(u);
	}
	vis[u] = true;
	for (auto& v : vs[u]) {
		if (!vis[v]) {
			dfs1(v, curDepth + 1, res);
		}
	}
}

int main() {
	int n;
	cin >> n;

	vs.resize(n + 1, vector<int>());
	int u, v;
	for (int i = 0; i < n - 1; i++) {
		cin >> u >> v;
		vs[u].push_back(v);
		vs[v].push_back(u);
	}

	int visCnt = 0;
	vis.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		if (dfs(i)) {
			visCnt++;
		}
	}
	if (visCnt > 1) {
		cout << "Error: " << visCnt << " components\n";
		return 0;
	}

	maxDepth = 0;
	fill(vis.begin(), vis.end(), false);
	dfs1(1, 1, res);

	res1.resize(n + 1);
	set<int>ans;// 去重
	for (int i = 0; i < res.size(); i++) {
		ans.insert(res[i]);
	}
	maxDepth = 0;
	fill(vis.begin(), vis.end(), false);
	dfs1(res[0], 1, res1);

	for (int j = 0; j < res1.size(); j++) {
		ans.insert(res1[j]);
	}
	for (auto& val : ans) {
		cout << val << "\n";
	}
	return 0;
}
```

