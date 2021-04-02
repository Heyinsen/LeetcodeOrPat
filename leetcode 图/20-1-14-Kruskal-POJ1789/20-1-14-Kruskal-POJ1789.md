## POJ1789

Truck History

| **Time Limit:** 2000MS       |      | **Memory Limit:** 65536K |
| ---------------------------- | ---- | ------------------------ |
| **Total Submissions:** 38419 |      | **Accepted:** 14697      |

Description

Advanced Cargo Movement, Ltd. uses trucks of different types. Some trucks are used for vegetable delivery, other for furniture, or for bricks. The company has its own code describing each type of a truck. The code is simply a string of exactly seven lowercase letters (each letter on each position has a very special meaning but that is unimportant for this task). At the beginning of company's history, just a single truck type was used but later other types were derived from it, then from the new types another types were derived, and so on.

Today, ACM is rich enough to pay historians to study its history. One thing historians tried to find out is so called derivation plan -- i.e. how the truck types were derived. They defined the distance of truck types as the number of positions with different letters in truck type codes. They also assumed that each truck type was derived from exactly one other truck type (except for the first truck type which was not derived from any other type). The quality of a derivation plan was then defined as
**1/Σ(to,td)d(to,td)**
where the sum goes over all pairs of types in the derivation plan such that to is the original type and td the type derived from it and d(to,td) is the distance of the types.
Since historians failed, you are to write a program to help them. Given the codes of truck types, your program should find the highest possible quality of a derivation plan.

Input

The input consists of several test cases. Each test case begins with a line containing the number of truck types, N, 2 <= N <= 2 000. Each of the following N lines of input contains one truck type code (a string of seven lowercase letters). You may assume that the codes uniquely describe the trucks, i.e., no two of these N lines are the same. The input is terminated with zero at the place of number of truck types.

Output

For each test case, your program should output the text "The highest possible quality is 1/Q.", where 1/Q is the quality of the best derivation plan.

Sample Input

```
4
aaaaaaa
baaaaaa
abaaaaa
aabaaaa
0
```

Sample Output

```
The highest possible quality is 1/3.
```

Source

[CTU Open 2003](http://poj.org/searchproblem?field=source&key=CTU+Open+2003)

* 以每一个类型为顶点, 两两之间类型的不同字母个数为边建立图, 求最小生成树. 
* kruskal算法对于稀疏图较为优秀. (prime算法加堆优化时间上一般更优, 但空间消耗大)
* [Prim、Kruskal、Prim+Heap算法效率实测](https://blog.csdn.net/gykimo/article/details/8538275)

```c++
#pragma warning(disable:4996)
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<map>
using namespace std;

/*
* Kruskal 算法求MST
*/
const int MAXN = 2005;//最大点数
const int MAXM = 2100000;//最大边数

int F[MAXN];//并查集使用

struct Edge {
	int u, v, w;
}edge[MAXM];//存储边的信息，包括起点/终点/权值

int tol;//边数，加边前赋值为0

void addEdge(int u, int v, int w) {
	edge[tol].u = u;
	edge[tol].v = v;
	edge[tol++].w = w;
}

//排序函数，讲边按照权值从小到大排序
bool cmp(Edge a, Edge b) {
	return a.w < b.w;
}

int find(int x) {
	if (F[x] == -1)
		return x;
	else
		return F[x] = find(F[x]);
}

//传入点数，返回最小生成树的权值，如果不连通返回-1
int kruskal(int n) {
	memset(F, -1, sizeof(F));
	sort(edge, edge + tol, cmp);

	int cnt = 0;//计算加入的边数
	int ans = 0;

	for (int i = 0; i < tol; i++) {
		int u = edge[i].u;
		int v = edge[i].v;
		int w = edge[i].w;
		int t1 = find(u);
		int t2 = find(v);
		if (t1 != t2) {
			ans += w;
			F[t1] = t2;
			cnt++;
		}
		if (cnt == n-1)break;
	}
	if (cnt < n-1)return -1;//不连通
	else return ans;
}

char vec[MAXN][8];
//vector<string>vec;
int main() {
    //ios::sync_with_stdio(false);
    //cin.tie(0);
    int n;
    while (cin >> n && n) {
        //string str;
		tol = 0;
        //vec.clear();
        //vec.reserve(2100000);
        for (int i = 0; i < n; i++) {
            //cin >> str;
            //vec.push_back(str);
			scanf("%s", vec[i]);
        }
        for (int i = 0; i < n/*vec.size()*/; i++) {
            for (int j = i + 1; j < n; j++) {
                int cnt = 0;
                for (int k = 0; k < 7; k++) {
                    if (vec[i][k] != vec[j][k]) {
                        cnt++;
                    }
                }
                addEdge(i, j, cnt);
            }
        }
        int ans = kruskal(n);
        cout << "The highest possible quality is " << "1/" << ans << ".\n";
    }
    return 0;
}

/*
4
aaaaaaa
baaaaaa
abaaaaa
aabaaaa
0
*/
```

