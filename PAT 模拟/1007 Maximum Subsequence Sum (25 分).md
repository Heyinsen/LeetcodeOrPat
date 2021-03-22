## 题解
1. 想清楚怎么计算最长子序列的最大和呢？
2. 我们要想清楚这一件事，那就是**负数的贡献永远是要抛弃的**
3. 想想我们计算这个和肯定是想要正数累加到一块，从哪来时累加，肯定是从第一个正数开始累加，这个和记为$tmp_sum$，在这个$tmp_sum$一直为正数的时间内，我们要不断的更新我们的最终结果$sum\_$，当我们的$tmp_sum$为负数的时候我们肯定就不想要前面的这一块了，这个时候直接抛掉这一块就好了，继续在后面找到第一个正数重复上面的过程不断的更新我们的$sum\_$，这样得到的$sum\_$就一直是我们的最大值了。
4. 想到这一点还是挺简单的，有一点需要注意的是，一直没过的一个点**在代码中详细的说明了**。
## 代码
```c++
#include<cstdio>
#include<iostream>
#include<string>
using namespace std;
const int MAXN=20005;
int input_s[MAXN];

int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        scanf("%d",&input_s[i]);
    }
    // 这里sum_=0我第一次写的时候有一个点过不去，不知道什么原因，按照[](https://liuchuo.blog.csdn.net/article/details/52144554?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.control&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.control)的
    // 博客照着修改，发现就这边不一样，想了一下当出现0为最终答案的时候两个输出的结果是不一样的
    // 由于要选择index最小的，else 中的if(tmp_sum>sum_)只能这么写，因此写-1是必要的
    int left=0,right=n-1,sum_=-1;
    int tmp_sum=0,tmp_left=0;
    for(int i=0;i<n;i++){
        tmp_sum+=input_s[i];
        if(tmp_sum<0){
            tmp_left=i+1;
            tmp_sum=0;
        }
        else{
            if(tmp_sum>sum_){
                sum_=tmp_sum;
                left=tmp_left;
                right=i;
            }
        }
    }
    if(sum_<0){
        sum_=0;
    }
    cout<<sum_<<" "<<input_s[left]<<" "<<input_s[right]<<endl;
    return 0;
}

```