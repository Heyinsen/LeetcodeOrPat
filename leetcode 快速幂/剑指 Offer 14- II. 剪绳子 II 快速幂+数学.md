## 思路

1. 数学推导
2. [leetcode官方题解贪心法和数学推导](https://leetcode-cn.com/problems/jian-sheng-zi-ii-lcof/solution/mian-shi-ti-14-ii-jian-sheng-zi-iitan-xin-er-fen-f/)

## 代码

数学推导法+快速幂

```c
class Solution {
public:
    vector<int>res;
    int cal(int n){
        if(n==0){
            return 1;
        }
        long long res_=1; 
        long long a=3;
        while(n){
            if(n&1){
                res_=res_*a%1000000007;
            }
            a=a*a%1000000007;
            n>>=1;
        }
        return (int)res_;
    }
    int cuttingRope(int n) {
        if(n<=3){
            return n-1;
        }
        int denominator=n/3;
        int remainder=n%3;
        if(remainder==0){
            int res=cal(denominator);
            return res;
        }
        else if(remainder==2){
            int res=cal(denominator);
            res*=2;
            res%=1000000007;
            return res;
        }
        else {
            int res=cal(denominator-1);
            res*=2;
            res%=1000000007;
            res*=2;
            res%=1000000007;
            return res;
        }
    }
};
```



