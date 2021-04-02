/*
*Kosaraju算法, 时间复杂度O(n+m)
*这个算法比Tarjan算法的时间复杂度要高,应用的范围小
*存在着爆栈超内存的风险, 适用于有向图
*/
const int MAXN=20010;
const int MAXM=50010;
struct Edge{
    int to,next;
}edge1[MAXM],edge2[MAXM];
//edge1是原图G, edge2是逆图GT
int tot1,tot2;

int head1[MAXN],head2[MAXN];
//mark1和mark2代表head1和head2中的顶点是否被DFS遍历到
bool mark1[MAXN],mark2[MAXN];

int st[MAXN];
int cnt1;
//st[i]代表遍历到的第i个节点的序号是st[i]
    //对原图进行dfs,点结束的时间从小到大排序

int Belong[MAXN];//每一个点属于哪一个连通分量  
int cnt2;//cnt2记录强连通分量的个数 
int num;//中间变量,用来数某个连通分量中点的个数
int setNum[MAXN];//强连通分量中点的个数,编号0~cnt2-1
void addedge(int u, int v){
    edge1[tot1].to=v;
    edge1[tot1].next=head1[u];
    head1[u]=tot1++;

    edge2[tot2].to=u;
    edge2[tot2].next=head2[v];
    head2[v]=tot2++;
}

void DFS1(int u){
    mark1[u]=true;
    for(int i=head1[u];i!=-1;i=edge1[i].next){
        if(!mark1[edge1[i].to]){
            DFS1(edge1[i].to);
        }
    }
    st[cnt1++]=u;
}

//对转置图进行DFS遍历,一次DFS可以得到一个强连通分量,
    //遍历的时候记录Belong[]和cnt2
void DFS2(int u){
    mark2[u]=true;
    
    num++;//该强连通分量的个数加1
    Belong[u]=cnt2;

    for(int i=head2[u];i!=-1;i=edge2[i].next){
        if(!mark2[edge2[i].to]){
            DFS2(edge2[i].to);
        }
    }
}

//点的编号从1开始
void solve(int n){
    memset(mark1,false,sizeof(mark1));
    memset(mark2,false,sizeof(mark2));
    cnt1=cnt2=0;
    for(int i=1;i<=n;i++){
        if(!mark1[i]){
            DFS1(i);
        }
    }
    //从最后遍历的点向前进行DFS遍历
    for(int i = cnt1−1;i >= 0; i−−)
        if(!mark2[st[i]]){
            num = 0;
            DFS2(st[i]);
            setNum[cnt2++] = num;
        }
}
