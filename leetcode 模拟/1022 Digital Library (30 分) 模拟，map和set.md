## 思路



1. 其实我们不需要存储每一本书的所有的信息，只需要知道其对应的$id$就可以了，这样的话我们只需要建立$title,author,keyword,publisher,year$到$id$的映射，由于每一个映射的$value$值不一定为1，我们可以用$vector<>$来存储，题目要求从小到达输出序号，$set<>$刚好满足这个条件，在$map$中查询的话需要使用$find()$方法。
2. 输入的处理较为麻烦
3. [参考链接](https://blog.csdn.net/CV_Jason/article/details/81515982)

## 精简的代码

**注意控制输出的id是七位数，不然最后两个点过不去。**

```cpp
#include<cstdio>
#include<iostream>
#include<sstream>
#include<map>
#include<cstring>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
int N, M;



map<string,set<int>>title,author,keyword,publisher,year;
void findID(map<string,set<int>>&mp,string &word){
    if(mp.find(word)!=mp.end()){//这里是不等于
        for(auto it=mp[word].begin();it!=mp[word].end();it++){
            printf("%07d\n",*it);
        }
    }
    else{
        cout<<"Not Found\n";
    }
}
int main(){
    cin>>N;
    int tid;
    string ttitle,tauthor,tkeyword,tpublisher,tyear;
    for(int i=0;i<N;i++){
        scanf("%d\n",&tid);//这里把\n读了防止对getline()函数产生干扰
        getline(cin,ttitle);
        title[ttitle].insert(tid);
        getline(cin,tauthor);
        author[tauthor].insert(tid);
        while(cin>>tkeyword){
            keyword[tkeyword].insert(tid);
            char c=getchar();
            if(c=='\n'){
                break;
            }
        }
        getline(cin,tpublisher);
        publisher[tpublisher].insert(tid);
        getline(cin,tyear);
        year[tyear].insert(tid);
    }
    cin>>M;
    int type;
    for(int i=0;i<M;i++){
        scanf("%d: ",&type);
        string word;
        getline(cin,word);
        cout << type << ": " << word << "\n";
        switch(type){
            case 1:{
                findID(title,word);
                break;
            }
            case 2:{
                findID(author,word);
                break;
            }
            case 3:{
                findID(keyword,word);
                break;
            }
            case 4:{
                findID(publisher,word);
                break;
            }
            case 5:{
                findID(year,word);
                break;
            }
        }
    }
}

```



## 思路

1. 首先一个**全局变量**存储一个结构体，这个结构体里面存储了有关这本书的所有的信息。
2. 然后我们需要分别按照**标题，作者，关键字，出版社，出版时间**建立其到$Node*的索引$，这样的话我们便节省了空间，每一个map 的元素用$vector<Node*>$存储，每次查询的时候就以$logn$的时间找到，然后按照id排序后输出。
3. 注意需要用全局变量存储$Node$数组，不能用$vector$,$vector<>$里面的元素的地址是变化的（经查发现），
4. 还有两个点没过的原因还没发现。

## 代码 （30‘ 的代码），用时，1h40’

**注意，最后两个点的id有前导0，输出的时候要注意。**

```cpp
#include<cstdio> 
#include<iostream>
#include<sstream>
#include<map>
#include<cstring>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
int N, M;

struct Node {
    int id;
    string title, author;
    vector<string> keywords;
    string publisher;
    int year;
    Node() {}
    Node(int id_, string title_, string author_, vector<string> keywords_, string publisher_, int year_) {
        keywords.resize(5);
        this->id = id_;
        this->title = title_;
        this->author = author_;
        for (int i = 0; i < keywords_.size(); i++) {
            keywords[i] = keywords_[i];
        }
        publisher = publisher_;
        year = year_;
    }
};

//vector<Node>v;
Node v[10005];
int v_len = 0;

void mySplit(string keyword, vector<string>& keywords) {
    int n = keyword.size();
    string cur = "";
    for (int i = 0; i < n; i++) {
        if (keyword[i] != ' ') {
            cur += keyword[i];
        }
        else {
            keywords.push_back(cur);
            cur = "";
        }
    }
    keywords.push_back(cur);
}


//map<int,Node*>idq;
map<string, vector<Node*>>titleq, authorq;
map<string, vector<Node*>>keywordsq;
map<string, vector<Node*>>publisherq;// ³ö°æÉÌ
map<int, vector<Node*>>yearq;

bool cmp(Node* p1, Node* p2) {
    return p1->id < p2->id;
}

int toNum(string year) {
    int res = 0;
    for (int i = 0; i < year.size(); i++) {
        res = res * 10 + (int)(year[i] - '0');
    }
    return res;
}

int main() {
    cin >> N;

    int id;
    string title, author;
    vector<string> keywords;
    string keyword;
    string publisher;
    int year;

    for (int i = 0; i < N; i++) {
        cin >> id;
        getchar();
        getline(cin, title);
        getline(cin, author);
        getline(cin, keyword);
        keywords.clear();
        mySplit(keyword, keywords);
        getline(cin, publisher);
        cin >> year;

        //v.push_back(Node(id, title, author, keywords, publisher, year));
        v[v_len++] = Node(id, title, author, keywords, publisher, year);
        //Node* node = &v[v.size() - 1];
        Node* node = &v[v_len - 1];

        //        idq[id]=node;
        if (titleq.count(title) == 0) {
            titleq[title] = vector<Node*>();
        }
        titleq[title].push_back(node);                                                                                                  
        
        if (authorq.count(author) == 0) {
            authorq[author] = vector<Node*>();
        }
        authorq[author].push_back(node);

        for (int j = 0; j < keywords.size(); j++) {
            if (keywordsq.count(keywords[j]) == 0) {
                keywordsq[keywords[j]] = vector<Node*>();
            }
            keywordsq[keywords[j]].push_back(node);
        }

        if (publisherq.count(publisher) == 0) {
            publisherq[publisher] = vector<Node*>();
        }
        publisherq[publisher].push_back(node);

        if (yearq.count(year) == 0) {
            yearq[year] = vector<Node*>();
        }
        yearq[year].push_back(node);
    }
    // 2: Yue Chen
    cin >> M;
    getchar();
    string line;
    string tmp;
    for (int i = 0; i < M; i++) {
        getline(cin, line);
        tmp = line.substr(3);
        cout << line << "\n";
        switch (line[0]) {
        case '1': {
            if (titleq.count(tmp) == 0) {
                cout << "Not Found\n";
                break;
            }
            vector<Node*>& vt = titleq[tmp];
            sort(vt.begin(), vt.end(), cmp);        //
            for (Node* node_ : vt) {
                // cout << node_->id << "\n";		// 注意输出是7位数
                printf("%07d\n",node_->id);
            }
            break;
        }
        case '2': {
            if (authorq.count(tmp) == 0) {
                cout << "Not Found\n";
                break;
            }
            vector<Node*>& vt = authorq[tmp];
            sort(vt.begin(), vt.end(), cmp);        //
            for (Node* node_ : vt) {
                // cout << node_->id << "\n";
                printf("%07d\n",node_->id);
            }
            break;
        }
        case '3': {  // ¹Ø¼ü×Ö
            if (keywordsq.count(tmp) == 0) {
                cout << "Not Found\n";
                break;
            }
            vector<Node*>& vt = keywordsq[tmp];
            sort(vt.begin(), vt.end(), cmp);        //
            for (Node* node_ : vt) {
                // cout << node_->id << "\n";
                printf("%07d\n",node_->id);
            }
            break;
        }
        case '4': {
            if (publisherq.count(tmp) == 0) {
                cout << "Not Found\n";
                break;
            }
            vector<Node*>& vt = publisherq[tmp];
            sort(vt.begin(), vt.end(), cmp);        //
            for (Node* node_ : vt) {
                // cout << node_->id << "\n";
                printf("%07d\n",node_->id);
            }
            break;
        }
        case '5': {
            int year_tmp = toNum(tmp);
            if (yearq.count(year_tmp) == 0) {
                cout << "Not Found\n";
                break;
            }
            vector<Node*>& vt = yearq[year_tmp];
            sort(vt.begin(), vt.end(), cmp);        //
            for (Node* node_ : vt) {
                // cout << node_->id << "\n";
                printf("%07d\n",node_->id);
            }
            break;
        }
        default: {
            cout << "Not Found\n";
        }
        }
    }
    return 0;
}

```

