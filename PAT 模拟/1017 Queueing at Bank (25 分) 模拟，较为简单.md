## 思路

1. 模拟题，优先队列维护每一个窗口完成的时间就可以了。
2. 不知道会不会有人的处理时间>60，这个要不要处理，没处理过了。
3. 写的麻烦了，看这个简洁的代码比较好。
4. [简洁的代码](https://blog.csdn.net/liuchuo/article/details/54573734)

```c++
#include<cstdio>
#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std;
int N,K;
struct Node1{
    int begin_time;
    int proc_time;
    Node1(){}
    Node1(int begin_time_,int proc_time_){
        begin_time=begin_time_;
        proc_time=proc_time_;
    }
    bool operator <(const Node1& node1)const{
        return begin_time<node1.begin_time;
    }
};
vector<Node1>inputs;
int waiting_time=0;
int num_people=0;

int begin_sec,end_sec;
struct Node{
    int index;
    int time;
    Node(){}
    Node(int index_,int time_){
        index=index_;
        time=time_;
    }
    bool operator<(const Node& node)const{
        return time>node.time;
    }
};

priority_queue<Node>q;

int toNum(string str){
    int res=0;
    res=((int)(str[0]-'0'))*10+(int)(str[1]-'0');
    return res;
}
int getSeconds(string str){
    int res=0;
    int hour=toNum(str.substr(0,2));
    int min=toNum(str.substr(3,2));
    int sec=toNum(str.substr(6,2));
    res=hour*60*60+min*60+sec;
    return res;
}

int main(){
    begin_sec=getSeconds("08:00:00");
    end_sec=getSeconds("17:00:00");
    scanf("%d%d",&N,&K);
    string str;
    int proc_time;
    for(int i=0;i<N;i++){
        cin>>str;
        scanf("%d",&proc_time);
        int sec=getSeconds(str);
        if(sec>end_sec){
            continue;
        }
        
//         if(proc_time>60){
//             proc_time=60;
//             continue;
//         }
        inputs.push_back(Node1(sec,proc_time*60));
        num_people++;
    }
    sort(inputs.begin(),inputs.end());

    for(int i=0;i<K;i++){
        q.push(Node(i,begin_sec));
    }
    for(int i=0;i<inputs.size();i++){
        int &cur_time=inputs[i].begin_time;
        int &proc_time=inputs[i].proc_time;
        Node top=q.top();
        int ok_time=top.time;
        int ok_index=top.index;
        if(cur_time<ok_time){
            waiting_time+=ok_time-cur_time;
            q.pop();
            q.push(Node(ok_index,ok_time+proc_time));
        }
        else{
            q.pop();
            q.push(Node(ok_index,cur_time+proc_time));
        }
       
    }
    
    if(num_people==0){
        printf("0.0\n");
    }else{
        double res=(double)waiting_time/60./(double)num_people;
        printf("%.1f\n",res);
    }
    return 0;
}

```

