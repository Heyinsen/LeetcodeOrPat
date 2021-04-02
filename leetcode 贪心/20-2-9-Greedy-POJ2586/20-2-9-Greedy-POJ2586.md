## POJ2586

Y2K Accounting Bug

| **Time Limit:** 1000MS       |      | **Memory Limit:** 65536K |
| ---------------------------- | ---- | ------------------------ |
| **Total Submissions:** 19190 |      | **Accepted:** 9689       |

Description

Accounting for Computer Machinists (ACM) has sufferred from the Y2K bug and lost some vital data for preparing annual report for MS Inc.
All what they remember is that MS Inc. posted a surplus or a deficit each month of 1999 and each month when MS Inc. posted surplus, the amount of surplus was s and each month when MS Inc. posted deficit, the deficit was d. They do not remember which or how many months posted surplus or deficit. MS Inc., unlike other companies, posts their earnings for each consecutive 5 months during a year. ACM knows that each of these 8 postings reported a deficit but they do not know how much. The chief accountant is almost sure that MS Inc. was about to post surplus for the entire year of 1999. Almost but not quite.

Write a program, which decides whether MS Inc. suffered a deficit during 1999, or if a surplus for 1999 was possible, what is the maximum amount of surplus that they can post.

Input

Input is a sequence of lines, each containing two positive integers s and d.

Output

For each line of input, output one line containing either a single integer giving the amount of surplus for the entire year, or output Deficit if it is impossible.

Sample Input

```
59 237
375 743
200000 849694
2500000 8000000
```

Sample Output

```
116
28
300612
Deficit
```

Source

[Waterloo local 2000.01.29](http://poj.org/searchproblem?field=source&key=Waterloo+local+2000.01.29)

* 某公司每个月要么盈利s元，要么亏损d元，一年之中任意连续的五个月的利润和是亏损的，最后问一年的总收入是多少，如果盈利即输出数额，如果亏损，则输出Deficit。
* 贪心
* 先假设所有的月份都盈利, 连续的5个月是否是亏损, 如果总盈利不是亏损, 则将最后一个月设为亏损, 之道连续五个月的总盈利为亏损为止, 重复这个过程. 

```c++
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
```

