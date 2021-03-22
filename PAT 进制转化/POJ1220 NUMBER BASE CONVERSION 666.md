# POJ1220 NUMBER BASE CONVERSION

## 思路

1.  没有什么好的思路，就是**模拟短除法**。
2.  我们来回顾一下短除法，$old\_base$的数字想要转化成$new\_base$的数字，我们使用$old\_base$的数字不断除以$new\_base$的数字，倒取余数就是我们的结果。[百度百科详细的解释](https://baike.baidu.com/item/%E5%8D%81%E8%BF%9B%E5%88%B6%E8%BD%AC%E4%BA%8C%E8%BF%9B%E5%88%B6/393189?fr=aladdin)
3.  具体的处理的细节比较繁琐，可以看代码。
4.  [参考文献附上，高精度模板，进制转换](https://blog.csdn.net/u011558005/article/details/17712351)

## 代码

```c++
/*
1
16 8 C2
*/
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;

const int MAXN=1005;
char c_s[MAXN];
int num_s[MAXN];    // 存放我们除法的结果,存放除数
int res_s[MAXN];    // 存放我们除法的结果,临时存放得到的商，最后要num_s[]=res_s[]
int remain_s[MAXN]; // 存放我们的商，也是我们最终的结果，倒叙输出就是我们要的答案
int len_remain_s=0; // remain_s[]的长度

// 给定一个字母，转化成10进制数字
int getNum(char c){
    if(c>='0'&&c<='9'){
        return (int)(c-'0');
    }
    else if(c>='A'&&c<='Z'){
        return (int)((c-'A')+10);
    }
    return (int)((c-'a')+36);
}

// 给定一个数字，转化成字母
char getChar(int num){
    if(0<=num&&num<=9){
        return (char)(num+'0');
    }
    else if(10<=num&&num<=35){
        return (char)(num-10+'A');
    }
    return (char)(num-36+'a');

}

// 
void solve(int old_base,int new_base){
    // remain_s[]的长度
    len_remain_s=0;
    int len_of_num_s=strlen(c_s);		// 当前被除数的长度
    for(int i=0;i<len_of_num_s;i++){	// 获取当前的被除数，转化成10进制数方便计算
        num_s[i]=getNum(c_s[i]);
    }
    while(len_of_num_s>0){  // 当我们的被除数不是0的时候不断的循环
        int res=0;			// 竖式计算，当前做除法的余数
        for(int i=0;i<len_of_num_s;i++){
            res=res*old_base+num_s[i];
            res_s[i]=res/new_base;
            res=res%new_base;
        }
        remain_s[len_remain_s++]=res;   // 存放我们的最终的结果，得到了第一个结果相关的余数
        int i=0;
        while(i<len_of_num_s&&res_s[i]==0){ // 去除商前面的前导0
            i++;
        }
        int cur_len=0;                      // 更新被除数的长度
        while(i<len_of_num_s){				// 得到的余数还要放回我们的num_s[]进入下一轮的循环
            num_s[cur_len]=res_s[i];
            cur_len++;
            i++;
        }
        len_of_num_s=cur_len;				// 更新num_s[]的长度
    }
}

int main(){
    int n;
    cin>>n;
    int old_base,new_base;
    while(n--){
        scanf("%d%d%s",&old_base,&new_base,c_s);
        // 处理这一组输出
        solve(old_base,new_base);
        // 下面做的是打印结果，结果就是remain_s[]数组倒序打印。
        printf("%d ",old_base);
        for(int i=0;i<strlen(c_s);i++){
            printf("%c",c_s[i]);
        }
        printf("\n");
        printf("%d ",new_base);
        for(int i=len_remain_s-1;i>=0;i--){
            // printf("%d",remain_s[i]);
            char c=getChar(remain_s[i]);
            printf("%c",c);
            if(i==0){
                printf("\n");
            }

        }
        printf("\n");
    }

}

```



