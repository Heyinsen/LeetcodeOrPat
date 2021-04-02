Radar Installation

| **Time Limit:** 1000MS        |      | **Memory Limit:** 10000K |
| ----------------------------- | ---- | ------------------------ |
| **Total Submissions:** 130723 |      | **Accepted:** 28687      |

Description

Assume the coasting is an infinite straight line. Land is in one side of coasting, sea in the other. Each small island is a point locating in the sea side. And any radar installation, locating on the coasting, can only cover d distance, so an island in the sea can be covered by a radius installation, if the distance between them is at most d.

We use Cartesian coordinate system, defining the coasting is the x-axis. The sea side is above x-axis, and the land side below. Given the position of each island in the sea, and given the distance of the coverage of the radar installation, your task is to write a program to find the minimal number of radar installations to cover all the islands. Note that the position of an island is represented by its x-y coordinates.
![img](D:\AFiles\TyporaPictures\1328_1.jpg)
Figure A Sample Input of Radar Installations



Input

The input consists of several test cases. The first line of each case contains two integers n (1<=n<=1000) and d, where n is the number of islands in the sea and d is the distance of coverage of the radar installation. This is followed by n lines each containing two integers representing the coordinate of the position of each island. Then a blank line follows to separate the cases.

The input is terminated by a line containing pair of zeros

Output

For each test case output one line consisting of the test case number followed by the minimal number of radar installations needed. "-1" installation means no solution for that case.

Sample Input

```
3 2
1 2
-3 1
2 1

1 2
0 2

0 0
```

Sample Output

```
Case 1: 2
Case 2: 1
```

Source

[Beijing 2002](http://poj.org/searchproblem?field=source&key=Beijing+2002)



* 以小岛为圆心，d为半径作圆，与x轴会有两个交点, 形成一个线段, 由相交部分的线段认为可以共用一个雷达, 转化为线段的相交问题.

```c++
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn = 1005;

struct Point {
	double x, y;
};
Point point[maxn];
double min_(double xx, double yy) {
	return xx < yy ? xx : yy;
}
struct LineSegment {
	double x1, x2;//线段左和右
};
LineSegment segment[maxn];

//按照线段的左端点排序, 后按照右端点排序
bool cmp(const LineSegment& a, const LineSegment& b) {
	if (a.x1 != b.x1) return a.x1 < b.x1;
	else return a.x2 < b.x2;
}

int n, d;
void lineSegment(int i) {
	segment[i].x1 = point[i].x - sqrt(double(d * d - point[i].y * point[i].y));
	segment[i].x2 = point[i].x + sqrt(double(d * d - point[i].y * point[i].y));
}

//返回ans
int solve() {
	double left = segment[0].x1;
	double right = segment[0].x2;
	int ans = 1;
	//当前线段所在的位置
	int cur = 1;
	while (cur < n) {
		//下一条线段的左端点小于上一条线段的右端点, 说明这两个线段之间有交点, 共用一个radar
		while (cur < n && segment[cur].x1 <= right) {
			left = segment[cur].x1;
			right = min_(right, segment[cur].x2);
			cur++;
		}
		//这两个线段之间没交点
		if (cur < n) {
			ans++;
			left = segment[cur].x1;
			right = segment[cur].x2;
		}
	}
	return ans;
}


int main() {
	int casei = 0;
	while (cin >> n >> d && (n || d)) {
		int ans = 0;
		for (int i = 0; i < n; i++) {
			cin >> point[i].x >> point[i].y;
			//计算线段的两个端点存入segment[i]中
			if (point[i].y > d)ans = -1;
			lineSegment(i);
		}
		if (ans != -1) {
			sort(segment, segment + n, cmp);
			ans = solve();
		}
		cout << "Case " << ++casei << ": " << ans << "\n";
	}
	return 0;
}
```

