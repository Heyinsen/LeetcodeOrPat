#pragma warning(disable:4996)
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<map>
#include<queue>
using namespace std;

const int maxn = 30;
int g[maxn][maxn];
int indegree[maxn];
queue<char>q;

int topology(int n) {
	while (!q.empty()) {
		q.pop();
	}

	int tmp_indegree[maxn];
	for (int i = 1; i <= n; i++) {
		tmp_indegree[i] = indegree[i];
	}
	//不能判断其序列的顺序,flag=2;
	//已经可以判断序列的顺序, flag=1
	int flag = 1;
	for (int i = 1; i <= n; i++) {
		int cnt_zero = 0;
		int pos = 0;
		for (int j = 1; j <= n; j++) {
			if (tmp_indegree[j] == 0) {
				cnt_zero++;
				pos = j;
			}
		}
		//这里的return要放在最上面.
		//首先需要判断是否存在环, 如果存在环了, 就需要输出环存在的信息, 这个具有最高的优先权
		if (cnt_zero == 0) {
			return 0;
		}
		//如果不能判断其序列是否有序
		//这里不return的原因是:
			//如果return了, 如果后面仍然存在环, 那么就会输出错误的结果, 这种情况下应该先输出是否有环的信息.
		else if (cnt_zero > 1) {
			flag = 2;
		}
		tmp_indegree[pos] = -1;
		q.push(char(pos - 1 + 'A'));
		for (int j = 1; j <= n; j++) {
			if (g[pos][j]) {
				tmp_indegree[j]--;
			}
		}
	}
	return flag;
}

int main() {
	int n, m;
	char ch[maxn];
	while (scanf("%d%d", &n, &m) && (n || m)) {
		memset(indegree, 0, sizeof(indegree));
		memset(g, 0, sizeof(g));

		int ok = 0;
		for (int i = 1; i <= m; i++) {
			scanf("%s", ch);
			//已经输出结果后, 后面不做处理
			if (ok) {
				continue;
			}

			int u = ch[0] - 'A' + 1;
			int v = ch[2] - 'A' + 1;
			g[u][v] = 1;
			indegree[v]++;
			//int flag;
			//flag==0,代表有环, 
			//flag==1,代表已经能确定序列
			//flag==2,代表无序, 无序的时候需要判断一张完整的图才能确定, 因为后面的加边会减少topology的indegree为0的点的个数
			int flag = topology(n);
			//存在环直接输出结果, 将ok置为1
			if (flag == 0) {
				printf("Inconsistency found after %d relations.\n", i);
				ok = 1;
			}
			//已经可以根据前面的偏序关系判断出大小关系的, 直接输出
			else if (flag == 1) {
				printf("Sorted sequence determined after %d relations: ", i);
				for (int i = 0; i < n; i++) {
					cout << q.front();
					q.pop();
				}
				cout << ".\n";
				ok = 1;
			}
		}
		//不能确定序列的关系需要整张图全部输入后才能判定
		if (!ok) {
			cout << "Sorted sequence cannot be determined.\n";
		}
	}
	return 0;
}