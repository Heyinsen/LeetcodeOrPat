## 图的定义和表示

### 顶点，弧，有向图和无向图

<v,w>表示弧，v表示弧尾，w表示弧头。

### 稀疏图和稠密图

1. 边的数目e<nlogn
2. e>=nlogn

### 简单路径，回路或者环，有根图

1. 简单路径：顶点不重复出现的路径
2. 回路：第一个和最后一个顶点相同的路径
3. 简单回路：除了第一个和最后一个顶点，其余的顶点都不重复的路径
4. 有根图：存在一个顶点u，顶点u可以到达其它所有的顶点，顶点u称为根。

## 存储结构

1. **邻接表**和十字链表

    * 求得出度的时候需要遍历整个邻接表，可以用**带入度的邻接表进行优化**。

        * 也即是Orthogonal List

        * > ​    可以看成是有向图的邻接表和逆邻接表结合起来形成的一种链表。
            >
            > ​    在邻接表的弧(或边)结点中增加一个指针指向弧头相同的下一条弧，再增加一个该弧依附的弧尾顶点，即可以方便地求某个顶点的入度。
            >
            > ```cpp
            > typedef struct _ArcNode
            > {
            >   int tailVex, headVex; /* 弧的头尾顶点的位置*/
            >   struct _ArcNode *hLink; /* 弧头相同的弧的链域*/
            >   struct _ArcNode *tLink; /* 弧尾相同的弧的链域*/
            >   AdjType weight;
            > } ArcNode;
            > // 对于邻接表的顶点结点，需要增加一个指针指向第一条以该顶点为弧头的弧的指针。
            > typedef struct _VexNode
            > {
            >     VexType  vertex;
            >     ArcNode  *firstIn;		/* 指向该顶点的第一条入弧*/
            >     ArcNode  *firstOut;		/* 指向该顶点的第一条出弧*/
            > } VexNode;
            > typedef struct
            > {
            >     VexNode  xList[Max_Vert_Num];		/* 表头向量*/
            >     int  vexNum, arcNum;
            > } OLGraph;
            > ```
            >
            > ![image-20210324142356383](Chapter07Graph/image-20210324142356383.png)
            >
            > * 理解：
            > * 我们看到上图，就拿V1来说，V1有两个产生出度的边(v1,v2),(v1,v3)，这个就是一般的邻接表的存储结构，很好实现。
            > * V1有两个产生入度的边，分别是(V3,V1),(V4,V1)，我们知道，不管是(V3,V1)还是(V4,V1)我们都可以在V3和V4的邻接表的边节点中找到这两条边，也就是产生入度的边和邻接表中的边节点是一一对应的，于是我们可以利用这些一一对应的边节点，在V1的头部设置一个指针，指向产生该节点1入度的第一个边节点u，例子中也就是V3节点，这个边节点u中也设立一个next指针，指向产生该节点1入读的第二个边节点v，例子中也就是V4节点，于是我们得到了交叉的十字链表的结构。

        * 理解了这个就可以轻松的写出十字链表的代码：

        * ```cpp
            输入: n个顶点和e条弧的信息
            Status CreateDG (OLGraph *g) {
                AdjType weight;		/* 非0则输入弧的其他信息*/
                VexType v1,v2;
                int i, j, k;
                ArcNode *p;
                scanf("%d %d %d", &g->vexNum, &g->arcNum);
                /* 构造表头向量，即输入顶点 */
                for (i=0; i<g->vexNum; i++) { 
                    /* 输入所有顶点并初始化指针成员 */
                    scanf (“%d”, &g->xlist[i].vertex);	/* 输入顶点值 */
                    g->xlist[i].firstIn = NULL;		/* 初始化指针*/
                    g->xlist[i].firstOut = NULL;	/* 初始化指针*/
                }
                /* 输入各弧并构造十字链表 */
                for (k=0; k<g->arcNum; k++) {
                    scanf(“%d %d”, &v1, &v2);	/* 输入每条弧的始点和终点 */
                    i = LocateVex(*g, v1);	   	/* 确定v1和v2在图中的位置 */
                    j = LocateVex(*g, v2);
                    p = (ArcNode *)malloc(sizeof(ArcNode));	/* 创建弧结点*/
                    assert(p);
                    p->tailVex = i;			/* 弧的始点是弧的弧尾*/
                    p->headVex = j;			/* 弧的终点是弧的弧头*/
                    /* 当前结点插入到十字链表第一个的位置*/
                    p->hLink = g->xlist[j].firstIn;	/* 作为第j个顶点的第一条入弧 */
                    p->tLink = g->xlist[i].firstOut;	/* 作为第i个顶点的第一条出弧 */
                    /* 重新设置第一条入弧和出弧*/
                    g->xlist[j].firstIn = g->xlist[i].firstOut = p;	
                }
                return OK;
            }	/* End of CreateDG() */
            ```

        * 十字链表的优缺点

            * 优点，容易求有向图的入度和出度
            * 缺点：操作复杂

2. **邻接矩阵**

    * 入度和出度。

3. 邻接多重表(**无向图**的以边为核心的操作)

    1. 例如遍历郭一条边，删除一条边等主要针对边的操作，用邻接表为存储结构的话，一条无向图的边需要对该边的两个顶点节点分别进行操作，较为麻烦。

    2.  和邻接表相似的构造，同一条边，在邻接表中使用两个节点表示，在邻接多重表中使用一条边来表示，如何实现？

    3. 定义边的存储结构：

        > ```cpp
        > // 邻接多重表是无向图另一种链式存储结构，它的结构与十字链表类似。
        > // 在邻接多重表中，每一条边用一个结点表示，有6个属性。
        > typedef struct _EdgeNode
        > {
        >     VisitIf  mark;		/*访问标记*/
        >     int  iVex, jVex;		/*该边依附的两个顶点的位置*/
        >     struct _EdgeNode  *iLink, *jLink;  
        > 			/*分别指向依附这两个顶点的下一条边*/
        >     AdjType  weight;		/*边的权 */
        > } EdgeNode;
        > typedef struct _VexNode
        > {
        >     VexType  vertex;
        >     EdgeNode  *firstedge;	/*指向第一条依附该顶点的边*/
        > } VexNode;
        > typedef struct
        > {
        >     VexNode  adjMultiList[Max_Vert_Num];	/* 表头向量*/
        >     int  vexNum, edgeNum;
        > } AMLGraph;
        > ```
        >
        > ![image-20210324144928896](Chapter07Graph/image-20210324144928896.png)
        >
        > * 主要要理解上面的边的存储结构和顶点的那个指向边的指针的含义。
        > * 边节点中的两个指针iLink和rLink分别指向iVex和jVex这两个顶点的下一条边，顶点节点中的firstedge指针指向该顶点的第一个边的节点，这样就可以理解上面的图示的结构了。

## 图的遍历和最短路径

### 图的深度优先遍历。

1. 类似于树的先序遍历，是树的先序遍历的推广。
2. ![image-20210324145613118](Chapter07Graph/image-20210324145613118.png)
3. 很简单，代码就不写了。
4. 时间复杂度，邻接矩阵为存储结构，时间复杂度为$O(n^2)$，邻接表为存储结构，时间复杂度为$O(n+e)$。

### 图的广度优先遍历

1. 类似于图的层次遍历。
2. ![image-20210324145835959](Chapter07Graph/image-20210324145835959.png)
3. 时间复杂度，和深度优先遍历相同。

### 图的深度优先生成树和广度优先生成树

1. ![image-20210324150022361](Chapter07Graph/image-20210324150022361.png)

2. 每一个连通分量通过遍历都可以得到一棵生成树，这些连通分量的生成树就构成了非连通图的生成森林，使用**孩子兄弟表示法**可以生成森林。

    ```cpp
    typedef  struct CSNode
    {
        DataType  info;
        struct CSNode  *lchild;
        struct CSNode  *rsibling;
    }CSTree, *PCSTree;
    
    // 邻接表作为存储结构，构建深度优先生成森林
    // MGraph g代表图，CSTree*T代表生成森林的根节点
    // CSTree是一个结构体, T是传入的一个地址,*T代表更改这个位置的值
    void DFSForest(MGraph g,PCSTree*T){
    	// p代表在遍历的过程中新生成的节点,q代表当前节点的所有邻接节点中的第一个节点作为树的孩子节点
        PCSTree p,q;
        int v;// 当前节点的邻接节点
        *T=NULL;//树根清空
        // 初始化visited数组
        for(v=0;v<g.vexNum;v++){
            visited[v]=FALSE;
        }
        for(v=0;v<g.vexNum;v++){
            if(visited[v])continue;
            p=(CSNode*)malloc(sizeof(CSNode));
            assert(p);
            p->data=GetVex(g,v);//获得当前邻接节点的data
            p->firstChild=NULL;//当前的第一个临接节点暂时没孩子
            p->nextSibling=NULL;// 当前的第一个邻接节点暂时没兄弟，等会就有兄弟了
            if(*T==NULl){
                *T=p;// 初始化森林的根节点
            }
            else{// 否则的话设置其右边的兄弟
                q->nextSibling=p;
            }
            q=p;
            DFSTree(g,v,&p);//从邻接节点继续深搜，中间要设置好父亲节点也就是p节点的左孩子节点
        }
    }
    
    void DFSTree(MGraph g,int v,PCSTree*T){
        PCSTree p,q; int w;
        BOOL first;
        visited[v]=TRUE;first=TRUE;
        q=*T;
        for (w = FirstAdjVex (g, v); w!=-1; w = NextAdjVex (g, v, w)) {
            if(visited[w])continue;
            p = (CSTree) malloc(sizeof(CSNode));
            p->data = GetVex (g, w);
            p->firstChild = NULL;
            p->nextSibling = NULL;
            if (first) {
                (*T)->firstChild = p;  first = FALSE; // 设置父亲节点的孩子
            }
            else  q->nextSibling = p;// 设置兄弟
            q = p;
            DFSTree (g, w, &q);
        }  /* for */
    }
    ```

### 有向图中的强连通分量和生成森林

1. Kosaraju算法[算法详解](https://www.jianshu.com/p/0264cb308069)

    > 第一步：计算出有向图 (G) 的反向图 (G反) 的**逆后序排列**（代码中有介绍）
    >  第二步：在有向图 (G) 中进行标准的深度优先搜索，按照刚才计算出的逆后序排列顺序**而非**标准顺序，每次搜索访问的所有点即在同一强连通分量中

    > ```cpp
    > class Kosaraju {
    >     private Digraph G;
    >     private Digraph reverseG; //反向图
    >     private Stack<Integer> reversePost; //逆后续排列保存在这
    >     private boolean[] marked;
    >     private int[] id; //第v个点在几个强连通分量中
    >     private int count; //强连通分量的数量
    >     public Kosaraju(Digraph G) {
    >         int temp;
    >         this.G = G;
    >         reverseG = G.reverse();
    >         marked      = new boolean[G.V()];
    >         id          = new int[G.V()];
    >         reversePost = new Stack<Integer>();
    >         
    >         makeReverPost(); //算出逆后续排列
    >         
    >         for (int i = 0; i < marked.length; i++) { //重置标记
    >             marked[i] = false;
    >         }
    >         
    >         for (int i = 0; i < G.V(); i++) { //算出强连通分量
    >             temp = reversePost.pop();
    >             if (!marked[temp]) {
    >                 count++;
    >                 dfs(temp);
    >             }
    >         }
    >     }
    >     /*
    >      * 下面两个函数是为了算出 逆后序排列
    >      */
    >     private void makeReverPost() {
    >         for (int i = 0; i < G.V(); i++) { //V()返回的是图G的节点数
    >             if (!marked[i])
    >                 redfs(i);
    >         }
    >     }
    >     
    >     private void redfs(int v) {
    >         marked[v] = true;
    >         for (Integer w: reverseG.adj(v)) { //adj(v)返回的是v指向的结点的集合
    >             if (!marked[w])
    >                 redfs(w);
    >         }
    >         reversePost.push(v); //在这里把v加入栈,完了到时候再弹出来,弹出来的就是逆后续排列
    >     }
    >     /*
    >      * 标准的深度优先搜索
    >      */
    >     private void dfs(int v) {
    >         marked[v] = true;
    >         id[v] = count;
    >         for (Integer w: G.adj(v)) {
    >             if (!marked[w])
    >                 dfs(w);
    >         }
    >     }
    >     
    >     public int count() { return count;}
    > }
    > ```
    >
    > 

    > 作者：zhangqi张琦
    > 链接：https://www.jianshu.com/p/0264cb308069
    > 来源：简书
    > 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

2. 原理解释：[为什么使用逆后序遍历](https://www.zhihu.com/question/58926821)

    > 作者：简致
    > 链接：https://www.zhihu.com/question/58926821/answer/583402591
    > 来源：知乎
    > 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
    >
    > 
    >
    > 以《算法》第四版中的实现为例，它旨在让每次递归探索中的所有顶点属于同一强连通分量。所以可以这么理解，当递归进入一个强连通分量中时，把它锁死在这个强连通分量中。
    >
    > ***\*核心在于封死连通分量往外走的路\****
    >
    > 而如何封死呢？该算法采用的是深度优先搜索，如果遇到了已经访问过的顶点则不再访问，那么如果能让一个分量内往外走的顶点已经被访问过了，是不是就能够锁死了呢？所以下图中，为了让5中的顶点正确关联上强连通分量编号，我们需要事先锁死H和C这两个顶点。
    >
    > ![img](Chapter07Graph/v2-d0d3da7fe69b44a2cf68ce1caa5aa230_hd.jpg)![img](Chapter07Graph/v2-d0d3da7fe69b44a2cf68ce1caa5aa230_720w.jpg)
    >
    > 
    > 上图为一个有向图，每个绿色方框为一个强连通分量，我们想要做的就是为这几个绿色方框内的顶点关联上对应的分量编号(绿框的编号)。  
    >
    > 
    > 我们将以深度优先搜索去穿越这幅图，但是我们希望每次探索都控制在一个绿色方框内，如1，进去了肯定到不了其他分量，而5通过顶点E和C、通过G和H连接起来了，它能够到达其他分量，所以我们希望当在分量5中探索时，如果到了E点，希望能够得到一个信息:不应该继续探索C顶点(H点同理)。  
    >
    >
    > 如何做到呢？考虑到深度优先搜索的特性：如果一个顶点已经探索过了，将不会再探索。那么我们只要保证在分量5内的顶点被探索时，C顶点与H顶点已经被探索过就能实现我们的目标。分量2、3、4之间的先后顺序同理。一般情况下我们使用DFS时都是从索引为0的顶点开始探索(或者其他的顶点，可视为从随机顶点开始)，无法保证分量1(还有分量3)在分量5之前探索完毕。在这个图中，无论是采用前序、后序还是逆后序，都无法达到我们的要求。
    >
    > 
    > 根据逆后序的性质，我们知道先探索完的顶点将会被放在栈的底部，其顺序是比较靠后的，所以我们可以利用这一点让分量5中的顶点顺序靠后，如何做到呢？  
    > 我们观察一下图并联想一下食物链，发现分量5实际上是处于食物链较的顶端的位置，因为他通过E和G侵入了其他群落，不考虑群落内的关系，为了颠覆分量5的统治地位，我们需要反转各群落之间的关系——反转图。 
    >
    > 
    >
    > ![img](Chapter07Graph/v2-6e575542be651e87b685165dad538486_hd.jpg)![img](Chapter07Graph/v2-6e575542be651e87b685165dad538486_1440w.jpg)
    >
    > 
    > ***\*一个图的反向图有着和其相同的强连通分量划分情况\****
    >
    > 这样一来，之前被分量5掠夺的群落反过来掠夺它了，也就是说，之前在分量5中探索时能够走出去的路全都反转了，走不出去了，这就给我们机会确定了分量的范围。如果你是从5开始，那么它走不出去，它内部的顶点先探索完毕，放入栈的底部；如果你是从3或者1开始，那么又将会走进5，所以5中的所有顶点也会放入栈的底部。所以反向图中，无论是从从哪里开始，都能保证在逆后序中，分量1和分量3中能够至少有一个顶点在栈中的位置处于所有5中的顶点之上。上面这幅图的逆后序(之一)为(假设从C开始)：
    > *> D A B F G E C I H J*  
    >
    > 我们用这个逆后序去深度优先搜索(正向)图，可以发现每次递归都是在同一个强连通分量之中。当然大家可以多试试反向图中的不同的逆后序，得到的结果是一样的。举一反三，虽然这个图中的分量比较少，但基于逆后序的性质，可以推广到所有的有向图中。
    >
    > 这就是我理解的为什么要用反向图的逆后序去DFS正向图。

3. 实现的一个代码：

    采用邻接表为结构。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

class Kosaraju {
	vector<int>vis;
	int n;
	vector<vector<int>>g;
	vector<vector<int>>gReversed;

	int count;// 强连通分量的个数
	vector<int>reversedPost;// 逆后续
public:
	Kosaraju(vector<vector<int>>& _g) {
		g = _g;
		n = _g.size();
		vis.resize(n);
		count = 0;
		reversedPost.clear();
		// get gReversed()
		gReversed.resize(n, vector<int>(n));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				gReversed[j][i] = g[i][j];
			}
		}
	}

	void kosaraju() {
		getReversedPost();
		fill(vis.begin(), vis.end(), 0);
		while (reversedPost.size()) {
			int val = reversedPost[reversedPost.size() - 1];
			reversedPost.pop_back();
			if (!vis[val] && dfs(val)) {
				count++;
			}
		}
		cout << count << endl;
	}

private:
	bool dfs(int i) {
		if (vis[i]) {
			return false;
		}
		vis[i] = true;
		for (int j = 0; j < g.size(); j++) {
			if (!g[i][j] || vis[j])continue;
			dfs(j);
		}
		return true;
	}

	void getReversedPost() {
		fill(vis.begin(), vis.end(), false);
		for (int i = 0; i < n; i++) {
			if (!vis[i]) {
				getReversedPost1(i);
			}
		}
	}

	// 这样可以保证所有的后遍历的节点都在先遍历的节点的前面出现，也就是reversedPost的后面就都是先遍历的节点了
	void getReversedPost1(int i) {
		vis[i] = true;
		for (int j = 0; j < n; j++) {
			if (!gReversed[i][j] || vis[j]) {
				continue;
			}
			getReversedPost1(j);
		}
		reversedPost.push_back(i);
	}
};

int main() {
	vector<vector<int>>gs({ {0,1,1,0},{0,0,0,0},{1,0,0,1},{1,1,1,0} });
	Kosaraju sol(gs);
	sol.kosaraju();
}
```

伪代码：

```cpp
int finished[MAXVEX];// 计算上面所说的gRevsersed[]这个数组
void traverseDFS (Graph *pgraph)	 
{	
    int visited[MAXVEX];			
    for (i=0; i<pgraph->n; i++) 
        visited[i]=FALSE; 			/* 初始化数组visited */
    count=0;
    for (i=0; i<n; i++)
        if (!visited[i]) DFS (pgraph, visited, i);
}

void DFS (Graph *pgraph, int visited[], int i)
{
    visited[i]=TRUE;
    printf (“node: %c\n”, pgraph->vexs[i]);	/* 访问出发点vi */
    for (j=FirstAdjVex(pgraph,i)0; j>=0; j=NextAdjVex(pgraph, i, j))
         if ( !visited[j])  DFS (pgraph, visited, j);
    finished[++count]=i;
}
```

**tarjan算法**（待学）

[tarjan算法的求解学习](https://zhuanlan.zhihu.com/p/101923309)

[为什么有向图要操作栈](https://www.luogu.com.cn/blog/computerlover/lun-tarjan-suan-fa-zhong-zhan-di-zuo-yong)

知乎上的这篇文章讲的很好，讲述了tarjan算法的基本的思想，通俗易懂，但是需要**注意的是:tarjan算法求无向图的割点与桥，以及求有向图的强连通分量，在代码的实现的细节上是有不同的**，这个需要十分注意。

1. **无向图的割点与桥**

```cpp
// 没跑过
#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;

const int maxn=1005;
struct Node{
    int v;
    int isCut;// 该边是不是桥
    Node(){}
    Node(int _v,int _isCut){
        v=_v;
        isCut=_isCut;
    }
};
vector<vector<Node>>head;// 邻接表的头节点
vector<int>cut;// 判断顶点是不是割点

vector<int>dfn;// 顶点访问的顺序
int cnt=0;// 当前时间戳
vector<int>low;// 子节点最早能访问的非父亲节点的节点的dfn的值

// 无向连通图G中，一个顶点是割点
// 1、根结点u为割顶当且仅当它有两个或者多个子结点；
// 2、非根结点u为割顶当且仅当u存在结点v，使得v极其所有后代都没有反向边可以连回u的祖先（u不算）
// 第二个条件的代码中就是low[u]<=low[v]
// 一条边为桥
// 当且仅当该边的孩子节点没有反向边可以连向父亲或者是祖先节点
// 放在代码中就是low[u]<low[v]，少了一个=
void tarjan(int u,int fat){
    dfn[u]=low[u]=++cnt;// 0代表没有访问过
    // instack[u]=true;
    int son=0;//记录根节点有多少孩子节点，根节点满足u==fat
    int prevCnt=0;
    for(int i=0;i<head[u].size();i++){
        Node &node=head[u][i];
        int& v=node.v;
        if(v==fat&&prevCnt==0){// 处理重根，也可以放在下面的else if判断中处理
            prevCnt++;
            continue;
        }
        if(!dfn[v]){
            son++;
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            // 桥<=
            if(dfn[u]<low[v]){
                // 桥
                head[u][i].isCut=true;
                head[u][i^1].isCut=true;
            }
            // 割点,非根节点,和桥不一样的是一个=
            if(u!=fat&&dfn[u]<=low[v]){
                cut[i]=true;
            }
        }
        else if(low[u]>dfn[v]){// 上面已经处理过重边，这边不需要处理
           low[u]=dfn[v];
        }
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
    cnt=0;
    
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        head[u].push_back(Node(v,0)); 
        head[v].push_back(Node(u,0)); 
    }

    for(int i=0;i<n;i++){
        if(!dfn[i]){
            tarjan(i,i);
        }
    }
}
```

![image-20210326000455067](Chapter07Graph/image-20210326000455067.png)

![image-20210326000504106](Chapter07Graph/image-20210326000504106.png)

上面是kuangbin大神的原代码。

```cpp
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
```



有向图求强连通分量和无向图的不一样的地方：

![image-20210326000549500](Chapter07Graph/image-20210326000549500.png)

![image-20210326000558580](Chapter07Graph/image-20210326000558580.png)

**可以看到，增加了一个对栈的操作**？

为什么要判断一个东西是否入栈？

* tarjan算法中的栈，栈中的所有的元素很可能是在**同一个强连通分量之中**，对于边<u,v>，如果u在栈中v不在栈中，但是v又已经被访问过的话，<u,v>不会是在一个强连通分量之中，因此，节点是否在栈之重对我们的结果影响很大。
* 无向图来说，u和v的连通性并不会受到影响，v在不在栈中是无所谓的。

**另外，不能对边进行判重**



## 最小代价生成树和最短路径



## 拓扑排序