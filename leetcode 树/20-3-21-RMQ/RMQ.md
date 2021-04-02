[RMQ 算法详解](https://blog.csdn.net/qq_41311604/article/details/79900893)

- RMQ 算法是用来求解区间最值的算法， 假设有一个 array a[MAXN];
- 下标从 1 开始， 我们要查询 n 次， 每一次查询为区间[l, r]内的最值？
- 采用暴力的遍历算法， 时间复杂度为 O(m\*(r-l+1)), m 为查询的次数
- 采用 RMQ 算法， 可以将时间复杂度降到 O(m+nlogn), 其为建立查询表的时间， 查询的时间为 O(1)
- 具体的解释详见本文开头的博客

```c++
/**
 * @implNote one dimensional RMQ
 * get maximum value, the array index starts at 1
 * get minmum value, the array index starts at 1
 * modify corresponding part if you want to start from 0
 * @params:
 */
#include <cstdio>
const int MAXN = 50010; // length of array
int dp[MAXN][20]; // dp[i][j]represents for in range(i, 2**j) the maximum value
                  // is dp[i][j]
int mm[MAXN];
// 2**20=1048576=10**6
/**
 * @initialize: the array index of b starts at 1
 * if want it starts at zero, modify corresponding part
 */

void initRMQ(int n, int b[]) {
  mm[0] = -1;
  for (int i = 1; i <= n; i++) {
    mm[i] = ((i & (i - 1)) == 0 ? mm[i - 1] + 1 : mm[i - 1]);
    dp[i][0] = b[i];
  }
  for (int j = 1; j <= mm[n]; j++) {
    for (int i = 1; i + (1 << j) - 1 <= n; i++) {
      dp[i][j] = max(dp[i][j - 1], dp[i + 1 << (j - 1)][j - 1]);
    }
  }
}

int rmq(int x, int y) {
  int k = mm[y - x + 1];
  return max(dp[x][k], dp[y - (1 << k) + 1][k]);
}

void rmq_init() {
  for (int i = 1; i <= N; i++)
    dp[i][0] = arr[i]; //初始化
  for (int j = 1; (1 << j) <= N; j++)
    for (int i = 1; i + (1 << j) - 1 <= N; i++)
      dp[i][j] = min(dp[i][j - 1], dp[i + (1 << j - 1)][j - 1]);
}

int rmq(int l, int r) {
  int k = log2(r - l + 1);
  return min(dp[l][k], dp[r - (1 << k) + 1][k]);
}

// int test[100];
// int main() {
//   test[0] = -1;
//   for (int i = 1; i <= 10; i++) {
//     test[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
//     printf("%d", test[i]);
//   }
// }
```
