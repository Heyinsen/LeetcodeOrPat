## 思路

1. 后序和中序构造二叉树
2. 唯一一个注意的地方，在注释中。

```c++
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;

const int MAXN=10005;
int n=0;
int postorder[MAXN],inorder[MAXN];

struct Node{
    int val=-1;
    Node*left=NULL,*right=NULL;
    Node(int val_=0):val(val_){
    }
};

int findPos(int val,int left,int right){
    for(int i=left;i<=right;i++){
        if(val==inorder[i]){
            return i;
        }
    }
    return -1;
}

Node* makeTree(int pos,int pos_inl,int pos_inr){
    if(pos_inl>pos_inr){
        return NULL;
    }
    Node *node=NULL;
    node=new Node(postorder[pos]);
    int pos_in_inorder=findPos(postorder[pos],pos_inl,pos_inr);
    int right_num=pos_inr-pos_in_inorder;
    // 注意这里是pos-right_num-1而不是想当然的pos_inr-1，这两个的位置并不一定对应
    node->left=makeTree(pos-right_num-1,pos_inl,pos_in_inorder-1);
    node->right=makeTree(pos-1,pos_in_inorder+1,pos_inr);
    return node;
}

vector<int>res;
void levelSearch(Node*root){
    if(root==NULL){
        return;
    }
    queue<Node*>q;
    q.push(root);
    while(!q.empty()){
        Node* top=q.front();
        q.pop();
        res.push_back(top->val);
        if(top->left){
            q.push(top->left);
        }
        if(top->right){
            q.push(top->right);
        }
    }
}
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        scanf("%d",&postorder[i]);
    }
    for(int i=0;i<n;i++){
        scanf("%d",&inorder[i]);
    }
    Node* root=NULL;
    root=makeTree(n-1,0,n-1);
    levelSearch(root);
//    cout<<"size: "<<res.size()<<endl;
    for(int i=0;i<res.size();i++){
        if(!i){
            printf("%d",res[i]);
        }
        else{
            printf(" %d",res[i]);
        }
    }
    printf("\n");
    return 0;
}

```

