## 思路

1. 最坑的一点，题目理解错了。。。
2. 槽点一，自己看题目不仔细，想当然的认为肯定是找最先结束的去排队，挂了。
3. 槽点二，理解了前面的怎么排队之后，明白了，首先是每个窗口之前有$m$个空缺的位置，顾客找有空缺位置最多的去坐，如果空缺的位置一样多，那么找序号较小的窗口去坐。
4. 根据3的理解，也就是前$m*n$个人不需要在外面等的，直接分配就好，剩下的人需要等，等哪个窗口最先没有人（两个窗口一块没有人选序号较小的）进入。
5. **理解错了题意**，如果有人开始服务的时间在5点之前，结束服务的时间 >=17:00，那么这个人需要被服务完，找了快两小时问题呜呜┭┮﹏┭┮。
6. 那么简单了，直接看代码。

## 代码

```c++
#include<cstdio>
#include<iostream>
#include<sstream>
#include<vector>
#include<queue>
using namespace std;

int n,m,k,Q;

struct Node{
    int index;                          // 当前这个人在哪个窗口处理
    int time;                           // 当前这个人所在的窗口第一个人处理结束的时间
    Node(){}
    Node(int index_,int time_){
        index=index_;
        time=time_;
    }
    bool operator<(const Node&node)const{
        if(time!=node.time){            // 时间小的在前面
            return time>node.time;
        }
        return index>node.index;        // 索引小的在前面
    }
};

priority_queue<Node>start_time;
vector<int>start_pos;                   // 当前这个人所在的窗口的第一个人所在的位置+1
vector<int>end_time;                    // 最后一个人处理结束的时间
vector<vector<int>>v;                   // 每一个窗口前面要处理的人的时间

vector<int>res;

string getString(int min_){
    string res="";
    int hourr=8+min_/60;
    int minn=min_%60;
    if(hourr<10){
        res+="0";
    }
    res+=to_string(hourr)+":";
    if(minn<10){
        res+="0";
    }
    res+=to_string(minn);
    return res;
}

int main(){
    cin>>n>>m>>k>>Q;

    res.resize(k);

    v.resize(n);
    start_pos.resize(n);
    end_time.resize(n);
    fill(start_pos.begin(),start_pos.end(),0);
    fill(end_time.begin(),end_time.end(),0);

    int val;
    for(int i=0;i<k;i++){
        scanf("%d",&val);
        if(i<n*m){                          // 前面n*m个直接分布到各个窗口就好
            if(i<n){
                start_time.push(Node(i,val));
                start_pos[i]=1;
            }
            v[i%n].push_back(val);
//            end_time[i%n]+=val;
            if(end_time[i%n]<((17-8)*60)){
                end_time[i%n]+=val;
                res[i]=end_time[i%n];
            }
            else{
                res[i]=0;
            }
        }
        else{                               // 后面的所有的人找哪一个窗口最先空出来人的位置就插入到哪一个窗口
            Node topp=start_time.top();
            start_time.pop();
            v[topp.index].push_back(val);
            if(end_time[topp.index]<(17-8)*60){
                end_time[topp.index]+=val;
                res[i]=end_time[topp.index];
            }
            else{
                res[i]=0;
            }
            topp.time+=v[topp.index][start_pos[topp.index]];
            start_pos[topp.index]++;
            start_time.push(topp);
        }
    }
    while(Q--){
        scanf("%d",&val);
        if(res[val-1]!=0){
            cout<<getString(res[val-1])<<"\n";
        }
        else{
            printf("Sorry\n");
        }
    }
    return 0;
}

```

