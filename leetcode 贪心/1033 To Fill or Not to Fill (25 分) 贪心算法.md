## 思路

1. 刚开始想到的是dp，想不出来。
2. 其实贪心就可以解决。

3. 1. 假设当前车在站点i，车中有油cur_oil，那么当前车可以行驶的距离未cur_oil*Davg，现在考虑在站点i冲不冲油，冲多少油？
        1) 当前的油量cur_oil不足以到达下一个站点，需要充油，怎么冲油，转到2中处理
        2) 当前站点接下来的若干个站点中，也就是cur_oil这些油量可以到达的站点中，没有油价比当前便宜的站点，需要在当前站点充油，怎么充油，转到2中处理
        3) 当前站点的油量cur_oil可以到达的所有站点中，有站点的油价比当前站点便宜，那么我们直接去那个站点，转到1

    2. 充油策略，1中我们说到，我们需要充油，怎么充？
        1) 油充满了也到达不了下一个站点，失败
        2) 缓慢冲油，也就是cur_oil增加了，直到发现当前油量可以到达的所有站点中，有比当前站点更加便宜的站点，停止充油，到达这个便宜的站点，转到1处理
        3) 如果充满了都没有发现更加便宜的站点，直接当前位置充满，行驶到当前油量可以达到的最远距离中所有站点中最便宜的站点，转到1

4. 其实上面的思路有一些复杂，里面有一些重合的情况，现在来简化上面的思路。
    当前在站点i，当前的油量为cur_oil，充油量x，首先查看当前油量能够到达的所有的后序站点j，找到一个油价低于当前的，若找到了，直接行驶到那个地方，回到1重复进行处理，若没有找到，在i处开始充油，一直充到找到了一个低于当前油价的地方，行驶到那个地方，回到1重复进行处理，若没有找到，当前满油，行驶到接下来可达的站点中有最便宜油价的地方，回到1处理

5. 上面的思路还是有一些复杂，进一步简化：

    首先，汽车在每一个站点必定需要充油。

    1. 汽车行驶的开始必充油

    2. 到达一个站点，可能是两种情况到达这个站点的，一个是刚好行驶到这个站点，没油了，需要充油。

        到达一个站点i，这个站点的油价比之前的站点的油价贵，但是是之前那个站点充满油可以到达的最远的距离中最便宜的站点，这个时候这个站点i的后序的若干个站点的油价肯定比当前站点i的油价高，所以必定需要充油去寻找后序油价较低的站点，若是没有，也没关系，当前站点i的油价最低，还是要充油。

        // 实现的一个思路如下：

## 代码

```cpp
#pragma warning(disable:4996)
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;
double Cmax = 0;
double Davg = 0;
double D = 0;
int N = 0;

struct Node {
	double Pi;
	double Di;
	Node() {}
	Node(double _Pi, double _Di) :Pi(_Pi), Di(_Di) {}
	bool operator<(const Node& next) {
		return Di < next.Di;
	}
};

vector<Node>station;

int main() {
	cin >> Cmax >> D >> Davg >> N;

	for (int i = 0; i < N; i++) {
		double Di, Pi;
		scanf("%lf%lf", &Pi, &Di);
		station.push_back(Node(Pi, Di));
	}
	station.push_back(Node(0, D));
	sort(station.begin(), station.end());
	N = N + 1;

	int target_station;
	for (int i = N - 1; i >= 0; i--) {
		if (station[i].Di == D) {
			target_station = i;
			break;
		}
	}
	if (N == 0) {
		if (D == 0) {
			printf("%.2f\n", 0);
			return 0;
		}
		else {
			printf("The maximum travel distance = %.2f\n", 0);
			return 0;
		}
	}
	if (station[0].Di != 0) {
		if (D == 0) {
			printf("%.2f\n", 0);
			return 0;
		}
		else {
			printf("The maximum travel distance = %.2f\n", 0);
			return 0;
		}
	}

	int cur_station = 0;
	double cur_oil = 0;
	double cur_cost = 0;
	double all_dis = 0;

	while (1) {
		// 充油
		if (cur_station == target_station) {
			printf("%.2f\n", cur_cost);
			return 0;
		}
		double& cur_price = station[cur_station].Pi, & cur_dis = station[cur_station].Di;

		int next_station = cur_station + 1;
		int min_price_station = next_station;
		double min_price = (double)INF;
		// cur_station只可能是 <= N-2的数字
		while (next_station < N && Cmax * Davg >= (station[next_station].Di - cur_dis) && station[next_station].Pi >= cur_price) {
			if (min_price > station[next_station].Pi) {
				min_price = station[next_station].Pi;
				min_price_station = next_station;
			}
			next_station++;
		}

		// 直接跑到终点
		if (next_station == N) {
			double& next_dis = station[N - 1].Di;
			cur_cost += ((next_dis - cur_dis) / Cmax - cur_oil) * cur_price;
			printf("%.2f\n", cur_cost);
			return 0;
		}
		// 下一个站点不能到达，需要加油到达next中最便宜的站点
		else if (Cmax * Davg < (station[next_station].Di - cur_dis)) {
			// 一个站点也不能到达
			if (next_station == cur_station + 1) {
				all_dis = cur_dis + Davg * Cmax;
				printf("The maximum travel distance = %.2f\n", all_dis);
				return 0;
			}
			double& next_price = station[min_price_station].Pi, & next_dis = station[min_price_station].Di;
			cur_cost += (Cmax - cur_oil) * cur_price;
			cur_oil = (Cmax - (next_dis - cur_dis) / Davg);
			all_dis = next_dis;
			cur_station = min_price_station;
		}
		// 找到了比当前位置便宜的站点了，直接充油，到达这个站点
		else {
			double& next_price = station[next_station].Pi, & next_dis = station[next_station].Di;
			cur_cost += ((next_dis - cur_dis) / Davg - cur_oil) * cur_price;
			cur_oil = 0;
			all_dis = next_dis;
			cur_station = next_station;
		}
	}
	return 0;
}
```



0,1,2第二个测试点被卡了一下。