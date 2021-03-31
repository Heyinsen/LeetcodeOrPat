// 实现的一个代码
/*9个顶点，11条边，输入顶点的编号1开始，代码中从0开始处理
9 11
1 2
1 3
1 4
2 5
3 5
4 6
5 7
5 8
6 8
7 9
8 9
*/
#include<cstdio>
#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std;
class Edge{
public:
    int v,w;
    Edge(int _v){
        v=_v;
    }
    Edge(int _v,int _w){
        v=_v;
        w=_w;
    }
};

class Topological{
public:
    int n;
    // 不用vector<>为存储结构的话可以考虑十字链表
    vector<vector<Edge>>e;
    vector<vector<Edge>>eRe;// 以u为弧头的边
    
    vector<int>indegree;
    
    stack<int>sstack;//求拓扑排序序列临时使用的栈
    stack<int>topo;// 存放拓扑排序后的顶点序列。
    stack<int>topoRe;// 存放拓扑排序后的顶点序列，用作求le[]用
    vector<int>ee,le;
    vector<int>e,l;
    
    // 存放关键路径的边
    // 找到关键路径上的所有的边之后，实际上我们可以再次对这些边进行一个拓扑排序，就可以找到所有的路径了
    Topological(int _n){
        this->n=_n;
        e.resize(n);
        indegree.resize(_n);//存放每一个顶点的入度
        ee.resize(n);
        le.resize(n);
        e.resize(n);
        l.resize(n);
    }
    void addEdge(int u,int v,int w){
        e[u].push_back(Edge(v,w));
        e[v].push_back(Edge(u,w));
    }
    void addEdge(int u,int v){
        e[u].push_back(Edge(v));
        e[v].push_back(Edge(u));
    }
    
    void topoSort(){
        // 首先计算每一个顶点的入度
        calIndegree();
        putZeroDegreeInStack();
        int num=0;
        while(!sstack.empty()){
            int u=sstack.top();
            sstack.pop();
            num++;
            
            topoRe.push(u);
            for(auto&edge:e[u]){
                int &v=edge.v,&w=edge.w;
                if(--indegree[v]==0){
                    sstack.push(v);
                    if(ee[v]<ee[u]+w){
                        ee[v]=ee[u]+w;
                    }
                }
            }
        }
        if(num<n){
            cout<<"存在环\n";
            return;
        }
        // 下面求le
        int lastVertical=topoRe.top();
        le[lastVertical]=ee[lastVertical];
        while(!topoRe.empty()){
            int u=topoRe.top();
            topoRe.pop();
            for(auto&edge:eRe[u]){
                int &v=edge.v,&w=edge.w;
               	if(le[v]>le[u]-w){
                    le[v]=le[u]-w;
                }
            }
        }
        // 下面我们需要找到所有的满足ee[i]==le[i]的顶点
        for(int i=0;i<n;i++){
            if(ee[i]==le[i]){
                cout<<i<<" ";
            }
        }
        cout<<endl;
    }
private:
    void calIndegree(){
        fill(indegree.begin(),indegree.end(),0);
        for(int i=0;i<n;i++){
            for(auto &edge:e[i]){
                int &v=e.v,&w=e.w;
                indegree[v]++;
            }
        }
    }
    void putZeroDegreeInStack(){
       	for(int i=0;i<n;i++){
            if(indegree[i]==0){
                sstack.push(i);
            }
        }
    }
};

int main(){
    int n,m;
    cin>>n>>m;
    Topological topo;
    int u,v,w;
    for(int i=0;i<m;i++){
        cin>>u>>v>>w;
        topo.addEdge(u,v,w);
    }
    topo.topoSort();
    return 0;
}