## 解体思路

1. 给一个数字（**以十进制的形式给出**），以及一个进制，让判断这个数字以这个进制翻转之后是否仍然是素数。
2. 朴素的判断素数的方法第二个点过不去
3. 使用欧拉线性筛，时间复杂度$O(n)$。

## 代码



```c++
#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
// #include<queue>
#include<cstring>
#include<cstdlib>
using namespace std;

int tmp[105];

int toBase10(int N,int base){
    int len=0,res=0,remainder;
    while(N>0){
        remainder=N%base;
        N/=base;
        tmp[len++]=remainder;
    }
    // 转化为10进制数
    for(int i=0;i<len;i++){
        res=res*base+tmp[i];
    }
    return res;
}

// 第二个点过不去
int judgeIf(int N){
    int res=1;
    for(int i=2;i<N;i++){
        if(N%i==0){
            res=0;
            break;
        }
    }
    return res;
}

const int maxn=50005;
int prime[maxn];
bool is_prime[maxn];
int cnt=0;
bool vis[maxn];

void makePrime(){
    memset(is_prime,0,sizeof(is_prime));
    for(int i=2;i<=maxn;i++){
        if(!vis[i]){
            is_prime[i]=true;
            prime[cnt++]=i;
            vis[i]=true;
        }
        for(int j=0;j<cnt;j++){
            if(i*prime[j]>maxn){
                break;
            }
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                break;
            }
        }
    }
}

// 注意，输入的数字是10进制
int main(){
    int N,D;
    makePrime();
    while(~scanf("%d",&N)&&N>=0){
        scanf("%d",&D);
//         int res1=judgeIf(N);
        int N_10=toBase10(N,D);
//         int res=judgeIf(N_10);
//         if(res&&res1){
//             printf("Yes\n");
//         }
//         else{
//             printf("No\n");
//         }
        if(is_prime[N]&&is_prime[N_10]){
            printf("Yes\n");
        }
        else{
            printf("No\n");
        }
    }
    return 0;
}

// 素数筛理解加默写
// int prime[maxn],cnt=0;
// int vis[maxn];
// void makePrime(){
//     for(int i=2;i<maxn;i++){
//         if(!vis[i]){
//             prime[cnt++]=i;
//             vis[i]=true;
//         }
//         for(int j=0;j<cnt;j++){
//             if(i*prime[i]>=maxn){
//                 break;
//             }
//             vis[i*prime[j]]=true;
//             if(i%prime[j]){
//                 break;
//             }
//         }
//     }
// }
```

