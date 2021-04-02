/*
 * 划分树（查询区间第k 大）
 */
#pragma warning(disable : 4996)
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int MAXN = 100010;

// tree[0][]存放初始的数组
int tree[20][MAXN];   //表示每层每个位置的值
int sorted[MAXN];     //已经排序好的数
int toleft[20][MAXN]; // toleft[p][i] 表示第i 层从1 到i 有数分入左边

void build(int l, int r, int dep) {
  if (l == r)
    return;
  int mid = (l + r) >> 1;
  int same = mid - l + 1;      //左子树的容量(可以放多少个数)
  for (int i = l; i <= r; i++) //注意是l, 不是one
    if (tree[dep][i] < sorted[mid])
      same--;
  //上面计算得到的same是除去相同的数以外, 左边还可以放多少个数
  int lpos = l;
  int rpos = mid + 1;
  //到这里

  for (int i = l; i <= r; i++) {
    if (tree[dep][i] < sorted[mid])
      tree[dep + 1][lpos++] = tree[dep][i];
    else if (tree[dep][i] == sorted[mid] && same > 0) {
      tree[dep + 1][lpos++] = tree[dep][i];
      same--;
    } else
      tree[dep + 1][rpos++] = tree[dep][i];
    toleft[dep][i] = toleft[dep][l - 1] + lpos - l;
  }
  build(l, mid, dep + 1);
  build(mid + 1, r, dep + 1);
}

//查询区间第k大的数,[L,R]是大区间，[l,r]是要查询的小区间
int query(int L, int R, int l, int r, int dep, int k) {
  if (l == r)
    return tree[dep][l];
  int mid = (L + R) >> 1;
  int cnt = toleft[dep][r] -
            toleft[dep][l - 1]; //[l,r]的范围内, 排在左半部分的数字的个数
  if (cnt >= k) {               //排在左半部分的数字的个数>=k,
                  //说明应该在[l,r]范围内的左边查找, 也是在[L,R]的左子树寻找
    //下面要做的是确定下面要查找的区间的左右范围.
    // toleft[dep][l - 1] - toleft[dep][L -
    // 1]代表了[L,l-1]范围内分到左子树的个数
    int newl =
        L + toleft[dep][l - 1] -
        toleft[dep]
              [L - 1]; // newl是[l,r]的范围内, 排在左边的数的第一个数字的位置
    int newr =
        newl + cnt - 1; // newr是[l,r]的范围内, 排在左边的数的最后一个数的位置
    return query(L, mid, newl, newr, dep + 1, k);
  } else {
    //如果排在右子树,
    // toleft[dep][R] - toleft[dep][r]代表[r+1,R]的范围内排在左子树的个数,
    // 1. [r+1,R]没有排在左边的, 那么newr的位置不变
    // 2. [r+1,R]内有排到左边的, 那么r的位置被向右挤压
    int newr = r + toleft[dep][R] - toleft[dep][r];
    //括号里面求得的是分配到右子树的个数-1
    int newl = newr - (r - l /*r-l是区间的个数减去1*/ - cnt);
    // k编程l-cnt
    return query(mid + 1, R, newl, newr, dep + 1, k - cnt);
  }
}

int main() {
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    // 20*maxn
    memset(tree, 0, sizeof(tree));
    for (int i = 1; i <= n; i++) {
      scanf("%d", &tree[0][i]);
      sorted[i] = tree[0][i];
    }
    // O(log(n))
    sort(sorted + 1, sorted + n + 1);
    build(1, n, 0);
    for (int i = 0; i <= 20; i++) {
      for (int j = 1; j <= n; j++) {
        printf("%d ", tree[i][j]);
      }
      puts("");
    }

    int s, t, k;
    while (m--) {
      scanf("%d%d%d", &s, &t, &k);
      printf("%d\n", query(1, n, s, t, 0, k));
    }
  }
  return 0;
}
/*
6 1
1 7 2 5 4 8
2 5 2
*/