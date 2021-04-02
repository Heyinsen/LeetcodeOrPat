#pragma warning(disable:4996)
#include <cstring>
#include<iostream>

#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn = 10;
const int MAXN = 100000;

char g[maxn][maxn];

int path[17];
int cntt;

int cnt;
//当前的值cur, 需要翻转的个数times, 当前光标所在的位置pos, 当前已翻转的个数cur_times
bool traverse(int cur, int times, int pos, int cur_times) {
	if (cur_times == times) {
		if (cur == 0 || cur == 0xffff) {
			return true;
		}
		/*if (times == 8) {
			cnt += 1;
			printf("%d, %x\n", cnt, cur);
		}*/
		return false;
	}
	if (pos >= 16) {
		return false;
	}
	int curr;
	for (int i = pos; i < 16; i++) {
		curr = cur ^ (1 << i);
		path[i] = 1;
		if (i - 4 >= 0) {
			curr ^= (1 << (i - 4));
		}
		if (i + 4 < 16) {
			curr ^= (1 << (i + 4));
		}
		if (i >= 1 && i <= 3 || i >= 5 && i <= 7 || i >= 9 && i <= 11 || i >= 13 && i <= 15) {
			curr ^= (1 << (i - 1));
		}
		if (i >= 0 && i <= 2 || i >= 4 && i <= 6 || i >= 8 && i <= 10 || i >= 12 && i <= 14) {
			curr ^= (1 << (i + 1));
		}
		if (traverse(curr, times, i + 1, cur_times + 1)) {
			return true;
		}
		path[i] = 0;
	}
	return false;
}

//白色用1
int solve() {
	int cur = g[0][0] == 'w' ? 1 : 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i + j == 0) {
				continue;
			}
			//左移一位
			cur <<= 1;
			if (g[i][j] == 'w') {
				cur += 1;
			}
		}
	}
	if (cur == 0 || cur == 0xffff) {
		return 0;
	}
	//
	int last = cur;
	for (int i = 1; i <= 16; i++) {
		if (traverse(last, i, 0, 0)) {
			return i;
		}
	}
	return -1;
}
int main() {
	//freopen("1/flip.05", "r", stdin);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			g[i][j] = getchar();
		}
		getchar();
	}
	int ans = solve();
	if (ans == -1) {
		cout << "Impossible\n";
	}
	else {
		cout << ans << "\n";
	}
	return 0;
}