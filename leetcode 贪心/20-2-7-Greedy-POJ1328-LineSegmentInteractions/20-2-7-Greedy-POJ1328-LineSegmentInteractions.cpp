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
		//下一条线段的左端点小于上一条线段的右端点, 说明这两个线段之间有交点
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