## POJ1094

Sorting It All Out

| **Time Limit:** 1000MS       |      | **Memory Limit:** 10000K |
| ---------------------------- | ---- | ------------------------ |
| **Total Submissions:** 42961 |      | **Accepted:** 15022      |

Description

An ascending sorted sequence of distinct values is one in which some form of a less-than operator is used to order the elements from smallest to largest. For example, the sorted sequence A, B, C, D implies that A < B, B < C and C < D. in this problem, we will give you a set of relations of the form A < B and ask you to determine whether a sorted order has been specified or not.

Input

Input consists of multiple problem instances. Each instance starts with a line containing two positive integers n and m. the first value indicated the number of objects to sort, where 2 <= n <= 26. The objects to be sorted will be the first n characters of the uppercase alphabet. The second value m indicates the number of relations of the form A < B which will be given in this problem instance. Next will be m lines, each containing one such relation consisting of three characters: an uppercase letter, the character "<" and a second uppercase letter. No letter will be outside the range of the first n letters of the alphabet. Values of n = m = 0 indicate end of input.

Output

For each problem instance, output consists of one line. This line should be one of the following three:

Sorted sequence determined after xxx relations: yyy...y.
Sorted sequence cannot be determined.
Inconsistency found after xxx relations.

where xxx is the number of relations processed at the time either a sorted sequence is determined or an inconsistency is found, whichever comes first, and yyy...y is the sorted, ascending sequence.

Sample Input

```
4 6
A<B
A<C
B<C
C<D
B<D
A<B
3 2
A<B
B<A
26 1
A<Z
0 0
```

Sample Output

```
Sorted sequence determined after 4 relations: ABCD.
Inconsistency found after 2 relations.
Sorted sequence cannot be determined.
```

Source

[East Central North America 2001](http://poj.org/searchproblem?field=source&key=East+Central+North+America+2001)



* [参考博文](https://www.jianshu.com/p/9db01daf978e)
* [参考博文(主要)](https://www.cnblogs.com/yueshuqiao/archive/2011/08/16/2140485.html)
* 主思想: 拓扑排序
* 题的意思: 
    * n个顶点, m条边(m条偏序关系), 每一个偏序关系抽象成一个由<左边的点指向右边的点的一条边, 用一个g\[maxn]\[maxn]存起来, 作为一张图. 下面执行拓扑排序算法的操作:
        1. g\[maxn]\[maxn]存储图
        2. indegree[maxn]存储每一个顶点的入度
        3. queue<char>q;存储拓扑排序的结果
        4. 执行拓扑排序
    * 题要求求三种输出:
        1. 输入m个偏序关系, 当输入到第i个偏序关系时, 需要先判断:
            * 如果前i个偏序关系存在环, 需要输出`Inconsistency found after %d relations.`也就是说, 输出环具有最高的优先级. 
            * 如果由前i个偏序关系已经能得出这n个顶点的唯一的确定的大小关系, 输出`Sorted sequence determined after %d relations: ABCD`(这里的ABCD是第一个样例的输出)
            * 如果前两个条件都不满足, 那么需要在所有m个关系输入完毕后, 判断其是否不可以得出唯一的大小的关系. 
    * 代码简单, 但其中蕴含的思想需要好好的体会揣摩一下. 
    * Wa了好几发, 对着参考博文写的, 觉着其代码很精炼.....

```c++
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
```

