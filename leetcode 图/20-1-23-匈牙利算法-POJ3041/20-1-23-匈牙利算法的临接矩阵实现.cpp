/* ***********************************************************
//二分图匹配（匈牙利算法的DFS 实现）(邻接矩阵形式)
//初始化：g[][] 两边顶点的划分情况
	//建立g[i][j] 表示i->j 的有向边就可以了，是左边向右边的匹配
	//g 没有边相连则初始化为0
//uN 是匹配左边的顶点数，vN 是匹配右边的顶点数

//调用：res=hungary(); 输出最大匹配数
//优点：适用于稠密图，DFS 找增广路，实现简洁易于理解
//时间复杂度:O(VE)
//临接矩阵的最坏时间复杂度:O(n^3)
//*************************************************************/
//顶点编号从0 开始的
#include<cstring>

const int MAXN = 510;
int uN, vN;//u,v 的数目，使用前面必须赋值
int g[MAXN][MAXN];//邻接矩阵
int linker[MAXN];//存储结果, 顶点i匹配得到的顶点j的编号
bool used[MAXN];//顶点V是否匹配过

bool dfs(int u) {
	for (int v = 0; v < vN; v++) {
		if (g[u][v] && !used[v]) {//匹配到第一个空闲的节点
			used[v] = true;
			if (linker[v] == -1 || dfs(linker[v])) {//被匹配的那个节点没有和其它人已匹配或者和该节点匹配的其他人能找到人匹配
				linker[v] = u;
				return true;
			}
		}
	}
	return false;
}

int hungary() {
	int res = 0;//成功匹配的最大个数
	memset(linker, -1, sizeof(linker));//存储结果
	for (int u = 0; u < uN; u++) {//给每一个顶点匹配
		memset(used, false, sizeof(used));
		if (dfs(u)) {//成功匹配
			res++;
		}
	}
	return res;
}