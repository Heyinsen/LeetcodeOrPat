#pragma warning(disable:4996)
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn = 15;
//每个月盈利还是亏本, 盈利为1
bool ok[maxn];

int main() {
	int p, d;
	while (scanf("%d%d", &p, &d) != EOF) {
		//先假设所有的月都盈利
		for (int i = 1; i <= 12; i++) {
			ok[i] = true;
		}
		//遍历所有的连续5个月
		for (int i = 1; i <= 8; i++) {
			int cnt = 0;//亏损的月数
			for (int j = i + 4; j >= i; j--) {
				if (ok[j] == false) {
					cnt++;
				}
			}
			int surplus = (5 - cnt) * p;
			int deficit = cnt * d;
			if (deficit < surplus) {
				//去掉一个坑位给dicifit, surplus的坑位就少了一个, 所以除以d+p
				double tmp = double(surplus - deficit) / double(d + p);
				int num = int(ceil(tmp));
				for (int j = i + 4; j >= i; j--) {
					if (ok[j] == true && num > 0) {
						num--;
						ok[j] = false;
					}
					
				}
			}
		}
		int earning = 0;
		for (int i = 1; i <= 12; i++) {
			if(ok[i]==false){
				earning -= d;
			}
			else {
				earning += p;
			}
		}
		if (earning > 0) {
			cout << earning << "\n";
		}
		else {
			cout << "Deficit" << "\n";
		}
	}
	return 0;
}