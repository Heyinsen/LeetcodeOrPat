#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;

class TreeNode{
public:
    int val;
    TreeNode*left,*right;
    TreeNode(){}
    TreeNode(int _val,TreeNode*_left=NULL,TreeNode*_right=NULL){
        val=_val;
        left=_left;
        right=_right;
    }
};

class PreOrder{
public:
    stack<TreeNode*>sstack;//先序遍历的栈
    stack<int>res;//存放先序遍历的结果
    TreeNode*root;

    PreOrder(){
        root=NULL;
    }
    // 简单的建立一颗二叉搜索树
    void addTreeNode(int _val){
        // root=addNode0(root,_val);
        addNode(root,_val);
    }
private:
    // 这样写要更改的指针太多
    TreeNode* addNode0(TreeNode*_node,int _val){
        if(_node==NULL){
            TreeNode*node=new TreeNode(_val);
            return node;
        }
        if(_node->val==_val){
            return _node;
        }
       	if(_node->val>_val){
            return _node->left=addNode(_node->left,_val);
        }
        if(_node->val<_val){
            return _node-<right=addNode(_node->right,_val);
        }
        return _node;
    }
    void addNode(TreeNode*&node,int val){
        if(node==NULL){
            node=new TreeNode(val);
            return;
        }
        if(node->val==val){
            return;
        }
        else if(node->val>val){
            addNode(node->left,val);
        }
        else{
            addNode(node->right,val);
        }
    }
public:
    void preOrder(){
        TreeNode*curNode=root;
        if(root==NULL){
            return;
        }
        sstack.push(root);
        res.push(root->val);

        while(!sstack.empty()){
            curNode=sstack.top();
            if(curNode->left){
                while(curNode->left){
                    curNode=curNode->left;
                    sstack.push(curNode);
                    res.push(curNode->val);
                }
            }
            sstack.pop();
            if(curNode->right){
                curNode=curNode->right;
                sstack.push(curNode);
             	res.push(curNode->val);
                continue;
            }
            
        }
        for(auto&val:res){
            cout<<val<<" ";
        }
        cout<<endl;
    }
};



int main(){
    vector<int>a({2,6,3,4,8,1});
    // 建立二叉搜索树
    // 2 1 6 3 4 8
    PreOrder preorder;
    for(auto&val:a){
    	preorder.addTreeNode(val);
    }
    preorder.preOrder();
}