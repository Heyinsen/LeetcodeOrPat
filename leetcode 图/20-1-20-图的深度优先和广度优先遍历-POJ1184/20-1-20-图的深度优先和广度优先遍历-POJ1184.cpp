#pragma warning(disable:4996)
#include<cstdio>
#include <iostream>
#include <map>
#include <string> 
#include <queue> 
using namespace std;

struct Node {
	string s;//6位数字, 第七位存储当前光标所在的位置[0,5]
	int step;//达到的最小的步数
	Node(string s_ = "", int step_ = 0) :s(s_), step(step_) {}
	~Node() {}
};

//起点和终点
Node beg, en;
//一个hash,判断该状态是否出现过
map<string, int> mp;
queue<Node> q;
int bfs() {
	Node tt;
	int i;

	while (!q.empty()) {
		q.pop();
	}
	q.push(beg);
	mp[beg.s] = 1;
	while (!q.empty()) {
		Node top = q.front();
		q.pop();
		string ss;
		ss = top.s;
		for (i = 0; i < 6; i++) {
			if (ss[i] != en.s[i]) {
				break;
			}
		}
		if (i == 6) {
			return top.step;
		}

		//Swap0:
		ss = top.s;
		swap(ss[0], ss[ss[6] - '0']);
		if (!mp.count(ss)) {
			tt.s = ss;
			tt.step = top.step + 1;
			q.push(tt);
			mp[ss] = 1;
		}

		//Swap1:
		ss = top.s;
		swap(ss[5], ss[ss[6] - '0']);
		if (!mp.count(ss)) {
			tt.s = ss;
			tt.step = top.step + 1;
			q.push(tt); mp[ss] = 1;
		}

		//Up:
		ss = top.s;
		if (ss[ss[6] - '0'] != '9' && ss[ss[6] - '0'] != en.s[ss[6] - '0']) {
			ss[ss[6] - '0'] += 1;
		}
		if (!mp.count(ss)) {
			tt.s = ss;
			tt.step = top.step + 1;
			q.push(tt);
			mp[ss] = 1;
		}

		//Down
		ss = top.s;
		if (ss[ss[6] - '0'] != '0' && ss[ss[6] - '0'] != en.s[ss[6] - '0']) {
			ss[ss[6] - '0'] -= 1;
		}
		if (!mp.count(ss)) {
			tt.s = ss; tt.step = top.step + 1;
			q.push(tt); mp[ss] = 1;
		}

		//shift left
		//左移的操作[1,4]的位置区间里面:
			//如果[1,4]的区间里面光标所在的位置和目标状态不同, 进行左移和右移操作没有意义
			//这里的证明?
			//所有仅仅当相同的时候移动光标
		ss = top.s;
		if (ss[6] != '0') {
			if (ss[6] != '5') {//光标所在的位置为1,2,3,,当且仅当相同的时候移动光标
				if (ss[ss[6] - '0'] == en.s[ss[6] - '0']) {
					ss[6] -= 1;
				}
			}
			else {//光标所在的位置为5
				ss[6] -= 1;
			}
		}
		if (!mp.count(ss)) {
			tt.s = ss; tt.step = top.step + 1;
			q.push(tt); mp[ss] = 1;
		}

		//shift right
		ss = top.s;
		if (ss[6] - '0' != 5) {
			if (ss[6] != '0') {
				if (ss[ss[6] - '0'] == en.s[ss[6] - '0']) ss[6] += 1;
			}
			else {
				ss[6] += 1;
			}
		}
		if (!mp.count(ss)) {
			tt.s = ss;
			tt.step = top.step + 1;
			q.push(tt);
			mp[ss] = 1;
		}
	}
}
int main() {
	while (cin >> beg.s >> en.s) {
		mp.clear();
		beg.s += '0';
		beg.step = 0;
		cout << bfs() << endl;
	}
	return 0;
}