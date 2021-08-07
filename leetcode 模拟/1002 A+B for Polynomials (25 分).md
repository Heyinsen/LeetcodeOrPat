## **1002 A+B for Polynomials (25 分)**

1.  下面的代码展示的是一个节省空间的做法，这种做法编码需要花费较长的时间，在实际的比赛中不推荐。
2.  下面的这种做法需要注意的是，当两个系数相加位0的时候的特殊情况处理，这里错了一次。
3.  比赛的过程中的最快的做法是直接声明两个1005的数字，对应的位置上存储对应的系数，然后直接相加输出就可以。

```c++
#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
int main(){
    int k1,k2;
    int x1[15];
    double a[15];
    double b[15];
    int y1[15];
    for(int i=0;i<2;i++){

        if(i==0){
            scanf("%d",&k1);
            for(int j=0;j<k1;j++){
                scanf("%d %lf", &x1[j],&a[j]);
            }
        }
        else{
            scanf("%d",&k2);
            for(int j=0;j<k2;j++){
                scanf("%d %lf", &y1[j],&b[j]);
            }
        }
    }

    int p1=0,p2=0;
    double c[30];
    int z[30];
    int len=0;
    while(p1<k1&&p2<k2){
        if(x1[p1]==y1[p2]){
            z[len]=x1[p1];
            c[len]=a[p1]+b[p2];
            // 这里需要进行特殊处理，错了一次
            if(abs(c[len])>=0.000000000000000001){
                len++;
            }
//            len++;
            p1++;
            p2++;
        }
        else if(x1[p1]>y1[p2]){
            z[len]=x1[p1];
            c[len]=a[p1];
            len++;
            p1++;
        }
        else{
            z[len]=y1[p2];
            c[len]=b[p2];
            len++;
            p2++;
        }
    }
    while(p1<k1){
        z[len]=x1[p1];
        c[len]=a[p1];
        len++;
        p1++;
    }
    while(p2<k2){
        z[len]=y1[p2];
        c[len]=b[p2];
        len++;
        p2++;
    }
    if(len==0){
        printf("%d\n",len);
        return 0;
    }
    else{
        printf("%d ",len);
    }

    for(int i=0;i<len-1;i++){
        printf("%d %.1f ",z[i],c[i]);
    }
    printf("%d %.1f\n",z[len-1],c[len-1]);
    return 0;
}
```

1.  下面的代码直接把系数相加了，简单一些。

```c++
#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;

int main(){
    int k1,k2;
    double a[1005]={0},b[1005]={0};
    scanf("%d",&k1);

    for(int i=0;i<k1;i++){
        int t1;
        double t2;
        scanf("%d%lf",&t1,&t2);
        a[t1]=t2;
    }

    scanf("%d",&k2);
    for(int i=0;i<k2;i++){
        int t1;
        double t2;
        scanf("%d%lf",&t1,&t2);
        b[t1]=t2;
    }

    double c[1005]={0};
    int n=0;
    int last=1000;
    for(int i=1000;i>=0;i--){
        double t3=a[i]+b[i];
        c[i]=t3;
        if(abs(t3)>=0.0000000000001){
            n++;
            last=i;
        }
    }
    if(n>0){
        printf("%d ",n);
    }
    else{
        printf("%d\n");
        return 0;
    }
    for(int i=1000;i>=0;i--){
        if(abs(c[i])>=0.000000000001){
            if(i!=last){
                printf("%d %.1f ",i,c[i]);
            }
            else{
                printf("%d %.1f\n",i,c[i]);
            }
        }
    }
}

```

[写的更加简洁一些](https://blog.csdn.net/I_HOPE_SOAR/article/details/83064733)