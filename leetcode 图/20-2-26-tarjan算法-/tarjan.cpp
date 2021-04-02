/*
 *Tarjan算法
 *复杂度O(N+M)
 */
const int MAXN=20010;//点数
const int MAXM=50010;//边数
struct Edge{
	int to,next;
}edge[MAXM];
int head[MAXN];
int tot;

int Low[MAXN];//每一个顶点在DFS搜索树中(所在强连通分量构成的子树)的根节点的时间戳
	//该节点的Low值和根节点的时间戳的值相同代表该节点和所属强连通分量的根节点
	//属于同一个强连通分量

int DFN[MAXN];//DFS第一次搜索到这个节点的时间戳
int Belong[MAXN];//Belong数组的值是1-scc
	//记录每一个顶点所属的强连通分量的序号
int scc;//记录强连通分量的个数

int Stack[MAXN];
int Index,top;

bool Instack[MAXN];
int num[MAXN];//各个强连通分量包含的点的个数, 数组的编号为[1,scc]
	//num不一定需要,根据实际情况

void addEdge(int u, int v){
	edge[tot].to=v;
	edge[tot].next=head[u];
	head[u]=tot++;
}

//从Tarjan算法从顶点u开始搜索
void Tarjan(int u){
	int v;
	Low[u]=DFN[u]=++Index;//搜索的第一个节点打上时间戳1
	Stack[top++]=u;//第一个节点入栈
	Instack[u]=true;

	//遍历栈顶顶点的所有临接的顶点DFS
	for(int i=head[u];i!=-1;i=edge[i].next){
		v=edge[i].to;
		if(!DFN[v]){//如果该节点第一次搜索到,从该节点开始搜索
			Tarjan(v);
			//根据子节点的时间戳更新该节点的时间戳,这里的时间戳指的是Low[]中的时间戳
				//若果下面的操作可以更新成功, 说明子节点找到了一条通往自己或者自己父亲
				//节点的路径
				//因为子节点tarjan过程中, 可能会找到子节点的祖先节点
					//从而更新其Low[]值, 故u需要根据子节点的更新, 调整
					//自己的Low的值
			Low[u]=min(Low[v],Low[u]);
		}
		//如果v节点在栈中, 说明这次搜索发现v是u的某个祖先节点
			//这样的话, 需要更新Low[u]=DFN[v];
		else if(Instack[v]&&Low[u]>DFN[v]){
			Low[u]=DFN[v];
		}
		//DFN[v]!=0 && !Instack[v]的不予处理
	}
	//相等说明该节点是该颗强连通分量子树的根
		//这时需要将该节点u的所有的子树和自己全部退栈.
	if(Low[u]==DFN[u]){
		scc++;
		do{
			v=Stack[--top];
			Instack[v]=fasle;
			Belong[v]=scc;
			num[scc]++;
		}while(v!=u);
	}
}
void solve(int N){
	memset(DFN,0,sizeof(DFN));
	memset(Instack,false,sizeof(Instack));
	memset(num,0,sizeof(num));
	Index=scc=top=0;
	for(int i=1;i<=N;i++){
		if(!DFN[i]){
			Tarjan(i);
		}
	}
}
void init(){
	tot=0;
	memset(head,-1,sizeof(head));
}
