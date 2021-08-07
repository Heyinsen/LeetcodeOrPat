## 解体思路

1. 模拟题，怎么说怎么做就好了，刚开始把所有的输入记录首先按照名字排序，名字相同的话按照时间从小到大排序。
2. 这样的话我们始终去寻找匹配的那一组开始通话和结束通话计算其花费的分钟数和花费的钱数就好了，这里不难，但是写起来有一些麻烦。
3. 使用map辅助寻找。
4. 时间复杂度$O(n*logn)$
5. 用时，1.5h，还要加速啊。

## 代码

```c++
#include<cstdio>
#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN=25;
int moneys[MAXN];
int N;

struct Node1{
    string name;
    string time;
    string begin_or_end;
    Node1(){}
    Node1(string name_,string time_,string begin_or_end_){
        name=name_;
        time=time_;
        begin_or_end=begin_or_end_;
    }
    bool operator<(Node1 node){
        if(name!=node.name){
            return name<node.name;
        }
        return time<node.time;
    }
};

struct Node{
    string name;
    string begin_time,end_time;
    int sum_min;
    double money;
    Node(){}
};

int tranverse2Time(string time){
    int month=(int)(time[0]-'0')*10+(int)(time[1]-'0');
    int day=(int)(time[3]-'0')*10+(int)(time[4]-'0');
    int hour=(int)(time[6]-'0')*10+(int)(time[7]-'0');
    int min=(int)(time[9]-'0')*10+(int)(time[10]-'0');
    int res=day*24*60+hour*60+min;
    return res;
}
int calMin(string begin_time,string end_time){
    int begin_time_min=tranverse2Time(begin_time);
    int end_time_min=tranverse2Time(end_time);
    return end_time_min-begin_time_min;
}

int toNum(string str){
    int res=0;
    for(int i=0;i<str.size();i++){
        res=res*10+(int)(str[i]-'0');
    }
    return res;
}

void updateRes(int begin_hour,int end_hour,int begin_min,int end_min,int*res){
    if(end_hour>begin_hour){
        res[begin_hour]+=60-begin_min;
    }
    else{
        res[begin_hour]+=end_min-begin_min;
    }
    for(int i=begin_hour+1; i<end_hour;i++){
        res[i]+=60;
    }
    if(end_hour>begin_hour){
        res[end_hour]+=end_min;
    }
}
double calMoney(string begin_time,string end_time){
    int res[25]={0};
    int begin_day=toNum(begin_time.substr(3,2)),end_day=toNum(end_time.substr(3,2));
    if(begin_day==end_day){
        int begin_hour=toNum(begin_time.substr(6,2)),end_hour=toNum(end_time.substr(6,2));
        int begin_min=toNum(begin_time.substr(9,2)),end_min=toNum(end_time.substr(9,2));
        updateRes(begin_hour,end_hour,begin_min,end_min,res);
    }
    else if(end_day>begin_day){
        int begin_hour=toNum(begin_time.substr(6,2)),end_hour=24;
        int begin_min=toNum(begin_time.substr(9,2)),end_min=0;
        updateRes(begin_hour,end_hour,begin_min,end_min,res);
        for(int j=0;j<24;j++){
            res[j]+=60*(end_day-begin_day-1);
        }
        begin_hour=0,end_hour=toNum(end_time.substr(6,2));
        begin_min=0,end_min=toNum(end_time.substr(9,2));
        updateRes(begin_hour,end_hour,begin_min,end_min,res);
    }
    double ret=0;
    for(int i=0;i<24;i++){
        ret+=res[i]*moneys[i];
    }
    return ret/100;
}

map<string,string>mp;
vector<Node>res;
vector<Node1>input;

int main(){
    for(int i=0;i<24;i++){
        scanf("%d",&moneys[i]);
    }
    scanf("%d",&N);
//     char tmp[25],tmp1[25],tmp2[25];
    string tmp,tmp1,tmp2;
    for(int i=0;i<N;i++){
//         scanf("%s%s%s",tmp,tmp1,tmp2);
        cin>>tmp>>tmp1>>tmp2;
        Node1 node1(tmp,tmp1,tmp2);
        input.push_back(node1);
    }
    sort(input.begin(),input.end());

    for(int i=0;i<N;i++){
        Node1 &input_=input[i];
        tmp=input_.name;
        tmp1=input_.time;
        tmp2=input_.begin_or_end;
        if(mp.count(tmp)==0||mp[tmp]==""){
            if(tmp2=="on-line"){
                mp[tmp]=tmp1;
            }
        }
        else{
            if(tmp2=="off-line"){
                Node node;
                node.name=tmp;
                node.begin_time=mp[tmp];
                node.end_time=tmp1;
                node.sum_min=calMin(node.begin_time,node.end_time);
                node.money=calMoney(node.begin_time,node.end_time);
                res.push_back(node);
                mp[tmp]="";
            }
            else{
                mp[tmp]=tmp1;
            }
        }
    }

    // 输出
    string prev_name="-1";
    double sum_=0;
    for(int i=0;i<res.size();i++){
        if(res[i].name!=prev_name){
            if(i!=0){
                printf("Total amount: $%.2f\n",sum_);
                sum_=0;
            }
            cout<<res[i].name<<" "<<res[i].begin_time.substr(0,2)<<"\n";
            prev_name=res[i].name;
        }
        cout<<res[i].begin_time.substr(3,res[i].begin_time.size()-3)<<" "<<res[i].end_time.substr(3,res[i].begin_time.size()-3)<<" "<<res[i].sum_min<<" $";
        sum_+=res[i].money;
        printf("%.2f\n",res[i].money);

    }
   printf("Total amount: $%.2f\n",sum_);
}

/*
CYJJ 01
01:05:59 01:07:00 61 $12.10
Total amount: $12.10
CYLL 01
01:06:01 01:08:03 122 $24.40
28:15:41 28:16:05 24 $3.85
Total amount: $28.25
aaa 01
02:00:01 04:23:59 4318 $638.80
Total amount: $638.80
*/

```





