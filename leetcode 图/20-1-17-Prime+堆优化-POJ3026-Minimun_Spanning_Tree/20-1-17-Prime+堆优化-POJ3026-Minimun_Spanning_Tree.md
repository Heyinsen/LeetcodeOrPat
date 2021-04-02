## POJ3026

Borg Maze

| **Time Limit:** 1000MS       |      | **Memory Limit:** 65536K |
| ---------------------------- | ---- | ------------------------ |
| **Total Submissions:** 20728 |      | **Accepted:** 6604       |

Description

The Borg is an immensely powerful race of enhanced humanoids from the delta quadrant of the galaxy. The Borg collective is the term used to describe the group consciousness of the Borg civilization. Each Borg individual is linked to the collective by a sophisticated subspace network that insures each member is given constant supervision and guidance.

Your task is to help the Borg (yes, really) by developing a program which helps the Borg to estimate the minimal cost of scanning a maze for the assimilation of aliens hiding in the maze, by moving in north, west, east, and south steps. The tricky thing is that the beginning of the search is conducted by a large group of over 100 individuals. Whenever an alien is assimilated, or at the beginning of the search, the group may split in two or more groups (but their consciousness is still collective.). The cost of searching a maze is definied as the total distance covered by all the groups involved in the search together. That is, if the original group walks five steps, then splits into two groups each walking three steps, the total distance is 11=5+3+3.

Input

On the first line of input there is one integer, N <= 50, giving the number of test cases in the input. Each test case starts with a line containg two integers x, y such that 1 <= x,y <= 50. After this, y lines follow, each which x characters. For each character, a space `` '' stands for an open space, a hash mark ``#'' stands for an obstructing wall, the capital letter ``A'' stand for an alien, and the capital letter ``S'' stands for the start of the search. The perimeter of the maze is always closed, i.e., there is no way to get out from the coordinate of the ``S''. At most 100 aliens are present in the maze, and everyone is reachable.

Output

For every test case, output one line containing the minimal cost of a succesful search of the maze leaving no aliens alive.

Sample Input

```
2
6 5
##### 
#A#A##
# # A#
#S  ##
##### 
7 7
#####  
#AAA###
#    A#
# S ###
#     #
#AAA###
#####  
```

Sample Output

```
8
11
```

Source

[Svenskt Mästerskap i Programmering/Norgesmesterskapet 2001](http://poj.org/searchproblem?field=source&key=Svenskt+Mästerskap+i+Programmering%2FNorgesmesterskapet+2001)

* 理解了题意后, 就是要求最小生成树的最小value
* 刚开始给的迷宫使用bfs求得各个顶点之间的距离, 然后使用prime算法求最小生成树的value即可
* 这题的输入有毒

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
const int maxn = 105;
const int INF = 0x3f3f3f3f;

int graph[maxn << 1][maxn << 1];

int dist[maxn << 1];
bool vis[maxn << 1];

//n为顶点的个数, 和输入的n不是一个n
//start为开始点的序号
int prime(int n, int start) {
	memset(vis, false, sizeof(vis));
	for (int i = 1; i <= n; i++) {
		dist[i] = graph[start][i];
	}
	int ans = 0;
	vis[start] = true;
	for (int i = 1; i < n; i++) {
		int minn = INF, min_pos = 0;
		for (int j = 1; j <= n; j++) {
			if (!vis[j] && minn > dist[j]) {
				minn = dist[j];
				min_pos = j;
			}
		}
		if (min_pos == 0) {
			return -1;
		}
		vis[min_pos] = true;
		ans += minn;
		for (int j = 1; j <= n; j++) {
			if (!vis[j] && dist[j] > graph[min_pos][j]) {
				dist[j] = graph[min_pos][j];
			}
		}
	}
	return ans;
}

int m, n;

//S点在迷宫的位置
int sx, sy;
//maze, 1 represents for wall, 0 represents for road, 2 represents for point "A"
int maze[maxn][maxn];

//位置(i,j)对应的顶点的序号
int index[maxn][maxn];
//顶点i对应的位置为
pair<int, int> index1[maxn];
//迷宫的(i,j)位置是否被浏览过
bool is_maze_vis[maxn][maxn];

struct Node {
	int x, y;
	int cost;
	Node(int x_ = 0, int y_ = 0, int z_ = 0) :x(x_), y(y_), cost(z_) {}
};

// bfs的队列
queue<Node>q;
//n:迷宫的行数, m:迷宫的列数, (si,sj)开始bfs的点--graph的顶点的坐标
//执行一次一下函数,得到顶点index[si][sj]到其他所有顶点的距离存入图graph[][]中
void bfs(int n, int m, int si, int sj) {
	memset(is_maze_vis, false, sizeof(is_maze_vis));
	int dirx[] = { 0,0,-1,1 };
	int diry[] = { -1,1,0,0 };

	q.push(Node(si, sj, 0));
	is_maze_vis[si][sj] = true;
	while (!q.empty()) {
		Node top = q.front();
		q.pop();
		if (maze[top.x][top.y] == 2) {
			graph[index[si][sj]][index[top.x][top.y]] = top.cost;
		}
		for (int i = 0; i < 4; i++) {
			int tx = top.x + dirx[i];
			int ty = top.y + diry[i];
			if (tx >= 1 && ty >= 1 && tx <= n && ty <= m && !is_maze_vis[tx][ty] && maze[tx][ty] != 1) {
				is_maze_vis[tx][ty] = true;
				q.push(Node(tx, ty, top.cost + 1));
			}
		}
	}
}

//这题的输入有毒, m,n后面可能有别的东西
char s[maxn];
int main() {
	int t;
	//scanf("%d", &t);
	ios::sync_with_stdio(false); cin.tie(0);

	cin >> t;
	cin.get();		//读入回车
	while (t--) {
		memset(graph, 0x3f, sizeof(graph));
		memset(maze, false, sizeof(maze));
		memset(index, 0, sizeof(index));

		cin >> m >> n;
		gets(s); //注意可能有多个空格
		int cnt_vert = 1;		//顶点的个数
		
		string str;		//输入一行的临时变量
		for (int i = 1; i <= n; i++) {
			getline(cin, str);
			//char c;
			for (int j = 1; j <= m; j++) {
				//scanf("%c", &c);
				switch (str[j - 1]) {
				case '#': {
					maze[i][j] = 1;
					break;
				}
				case 'A': {
					maze[i][j] = 2;
					index[i][j] = ++cnt_vert;
					index1[cnt_vert] = pair<int, int>(i, j);
					break;
				}
				case ' ': {
					maze[i][j] = 0;
					break;
				}
				default: {
					sx = i;
					sy = j;
					maze[i][j] = 2;
					index[i][j] = 1;
					index1[1] = pair<int, int>(i, j);
				}
				}
			}
		}

		for (int i = 1; i <= cnt_vert; i++) {
			bfs(n, m, index1[i].first, index1[i].second);
		}
		cout << prime(cnt_vert, 1) << "\n";
	}
	return 0;
}
```

