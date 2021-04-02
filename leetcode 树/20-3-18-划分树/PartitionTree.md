# 划分树

[有关于化分树比较详细的介绍](https://blog.csdn.net/mikasa3/article/details/51160062)

- 有关化分树, 这里先放出 kuangbin 的模板[^1], 随后给出详细的介绍.

```c++
/*
划分树（查询区间第k 大）
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
int toleft[20][MAXN]; // toleft[i][j] 表示第i层的子树中从1到j有tolleft[i][j]个数分入左子树

/**
 * @implNote 建树
 * @param l序列最左端下表, r序列最右端下标, dep当前数的深度
*/
void build(int l, int r, int dep) {
  if (l == r)
    return;
  int mid = (l + r) >> 1;
  int same = mid - l + 1;      //左子树的容量(可以放多少个数)
  for (int i = l; i <= r; i++)
    if (tree[dep][i] < sorted[mid])
      same--;
  //上面计算得到的same是除去相同的数以外, 左边还可以放多少个数

  int lpos = l; // 建立下一层树的左子树的最左边位置
  int rpos = mid + 1;   // 建立下一层树的右子树的最左边位置

  for (int i = l; i <= r; i++) {
      //该元素应当被放倒到左子树, 因为其小于中间值
    if (tree[dep][i] < sorted[mid])
      tree[dep + 1][lpos++] = tree[dep][i];
      //该元素等于中间值且左子树仍然可以容纳一定的和中间数相等的数
    else if (tree[dep][i] == sorted[mid] && same > 0) {
      tree[dep + 1][lpos++] = tree[dep][i];
      same--;
    } else
    //只能放在右子树
      tree[dep + 1][rpos++] = tree[dep][i];
    //lpos-l是左子树已经放置的元素的个数
    //这里的tolleft加上了一个toleft[dep][l - 1], 和上面介绍的那篇博客有些许的不一样, 只不过是进行了同一层的放置元素的累加, 其相互之间的差并没有改变
    //如果要改成和上面的那篇博客一样的话, 只需要将这个+toleft[dep][l-1]去掉, 下面的query做出修改, 修改的方法类似于上述博客所述
    toleft[dep][i] = toleft[dep][l - 1] + lpos - l;
  }
  //递归建树
  build(l, mid, dep + 1);
  build(mid + 1, r, dep + 1);
}

//查询区间第k大的数,[L,R]是大区间，[l,r]是要查询的小区间
int query(int L, int R, int l, int r, int dep, int k) {
  //查询到叶子节点找到了这个数
  if (l == r)
    return tree[dep][l];
    //建树时的mid, 这个mid指示了该节点的左右两边各有多少个元素
    //左边的元素的个数为mid-l+1, 右边的元素的个数为r-mid
  int mid = (L + R) >> 1;
  int cnt = toleft[dep][r] -
            toleft[dep][l - 1]; //[l,r]的范围内, 被分配到左子树的数字的个数
  if (cnt >= k) {               //被分配到左子树的数字的个数>=k,
                  //说明应该是在[L,R]的左子树寻找
    //下面要做的是确定下面要查找的区间的左右端点的索引.
    // toleft[dep][l - 1] - toleft[dep][L - 1]代表了[L,l-1]范围内分到左子树的个数, 除去这个个数, 剩下的分配的便是[l,r]范围内的数字, 只要用这个数字加上L便可以得到newl
    int newl =
        L + toleft[dep][l - 1] -
        toleft[dep]
              [L - 1]; // newl是[l,r]的范围内, 左子树的数中的第一个数字的位置
    int newr =
        newl + cnt - 1; // newr是[l,r]的范围内, 左子树的数中的最后一个数的位置
    //查询左子树中的第k个数
    return query(L, mid, newl, newr, dep + 1, k);
  } else {
    //如果排在右子树,
    // toleft[dep][R] - toleft[dep][r]代表[r+1,R]的范围内排在左子树的个数,
    // 1. [r+1,R]没有排在左子树的, 那么newr的位置不变为r
    // 2. [r+1,R]内有排到左子树的, 那么r的位置被向右挤压
    int newr = r + toleft[dep][R] - toleft[dep][r];
    //括号里面求得的是分配到右子树的个数-1
    int newl = newr - (r - l /*r-l是区间的个数减去1*/ - cnt);
    // k变成k-cnt
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
```

---

- 下面的代码来自上述博客[^1], 建树

```c++
void buildtree(int l, int r, int d)//d是深度
{
    if (l == r)//递归出口
    {
        return;
    }
    int mid = (l+r)>>1;//划分左右区间
    int opleft = l, opright = mid+1;//对左右子树的操作位置的初始化
    int same_as_mid = 0;//和sor[mid]相同的数的数目
    //计算在mid左边有多少个和sor[mid]相同的数（包括mid）,都要放到左子树
    for (int i = mid; i > 0; i--)
    {
        if (sor[i] == sor[mid])
            same_as_mid++;
        else
            break;
    }
    int cnt_left = 0;//被划分到左子树的个数
    for (int i = l; i <= r; i++)
    {
        //从l到r开始遍历
        if (tree[d].num[i] < sor[mid])//左
        {
            tree[d+1].num[opleft++] = tree[d].num[i];
            cnt_left++;
            tree[d].cnt[i] = cnt_left;
        }
        else if(tree[d].num[i] == sor[mid] && same_as_mid)
        {
            //相同的都放在左子树
            tree[d+1].num[opleft++] = tree[d].num[i];
            cnt_left++;
            tree[d].cnt[i] = cnt_left;
            same_as_mid--;
        }
        else//右
        {
            tree[d].cnt[i] = cnt_left;
            tree[d+1].num[opright++] = tree[d].num[i];
        }
    }
    //递归建树
    buildtree(l, mid, d+1);
    buildtree(mid+1, r, d+1);
}
```

- 下面的代码来自上述博客[^1], 查询

```c++
int query(int l, int r, int d, int ql, int qr, int k)
//1 n 0 a b k
//在d层[l,r]的节点里查找[a,b]中的第k大值
{
    if (l == r)//递归出口
        return tree[d].num[l];
    int mid = (l+r)>>1;
    int sum_in_left;//区间内元素位于下一层左子树的个数
    int left;//[l,ql-1]左边的元素中位于下一层左子树的个数
    if (ql == l)
    {//如果ql是节点的左边界则有cnt[qr]个数进入左子树
        sum_in_left = tree[d].cnt[qr];
        left = 0;
    }
    else
    {//如果ql不是节点的左边界则有cnt[qr]-cnt[ql-1]个数进入了左子树
        sum_in_left = tree[d].cnt[qr] - tree[d].cnt[ql-1];
        left = tree[d].cnt[ql-1];
    }
    if (sum_in_left >= k)
    {//要找的点在左子树
        //确定下一步询问的位置：
        //如果在ql的左边有left个进入左子树
        //那么ql到qr中第一个进入左子树的必定在l+left的位置
        int new_ql = l+left;
        int new_qr = new_ql+sum_in_left-1;
        return query(l, mid, d+1, new_ql, new_qr, k);
    }
    else//要找的点在右子树
    {
        //确定下一步询问的位置
        int a = ql - l - left;//表示当前区间左半部分即[l,ql-1]中在下一层是右孩子的个数
        int b = qr - ql + 1 - sum_in_left;//表示当前区间右半部分即[ql,qr]中在下一层是右孩子的个数
        int new_ql = mid + a + 1;
        int new_qr = mid + a + b;
        //k-sum_in_left表示要减去区间里已经进入左子树的个数
        return query(mid+1, r, d+1, new_ql, new_qr, k - sum_in_left);
    }
}
```
