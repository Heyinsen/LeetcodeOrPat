## [剑指 Offer 36. 二叉搜索树与双向链表](https://leetcode-cn.com/problems/er-cha-sou-suo-shu-yu-shuang-xiang-lian-biao-lcof/)

## 思路

1. 思路，中序遍历的时候顺便修改left和right的指针。
2. [官方题解](https://leetcode-cn.com/problems/er-cha-sou-suo-shu-yu-shuang-xiang-lian-biao-lcof/solution/mian-shi-ti-36-er-cha-sou-suo-shu-yu-shuang-xian-5/)

## 代码

```cpp
class Solution {
public:
    Node*head=NULL,*pre=NULL;
    void solve(Node*root){
        if(root==NULL){
            return;
        }
        solve(root->left);
        if(pre!=NULL){
            root->left=pre;
            pre->right=root;
        }
        else{
            head=root;
        }
        pre=root;
        solve(root->right);
    }
    Node* treeToDoublyList(Node* root) {
        if(root==NULL){
            return NULL;
        }
        solve(root);
        pre->right=head;
        head->left=pre;
        return head;
    }
};


// #include<cstdio>
// #include<iostream>
// #include<stack>
// using namespace std;
// // Definition for a Node.
// class Node {
// public:
// 	int val;
// 	Node* left;
// 	Node* right;

// 	Node() {}

// 	Node(int _val) {
// 		val = _val;
// 		left = NULL;
// 		right = NULL;
// 	}

// 	Node(int _val, Node* _left, Node* _right) {
// 		val = _val;
// 		left = _left;
// 		right = _right;
// 	}
// };

// class Solution {
// public:
// 	stack<Node*>nodes;
// 	stack<int>leftOrRight;  // 0代表当前节点为父亲的左节点，1代表右节点处，-1代表当前节点为根

// 	Node* treeToDoublyList(Node* root) {
// 		if (root == NULL) {
// 			return NULL;
// 		}

// 		Node* curNode, * fatNode, * nextNode;

// 		// 首先获取链表的第一个节点   
// 		curNode = root;
// 		while (curNode) {
// 			nodes.push(curNode);
// 			if (curNode == root) {
// 				leftOrRight.push(-1);
// 			}
// 			else {
// 				leftOrRight.push(0);
// 			}
// 			curNode = curNode->left;
// 		}
// 		curNode = nodes.top();
// 		nodes.pop();
// 		int curLeftOrRight = leftOrRight.top();
// 		leftOrRight.pop();
// 		root = curNode;

// 		// 进入主程序
// 		while (!nodes.empty()) {
// 			// 当前的curNode必定为当前没有维护好的某颗子树的最左节点
// 			while (curNode->right == NULL && !nodes.empty() && curLeftOrRight == 0) {// 当前节点为父亲节点的左孩子节点，右孩子节点为空的时候并且栈中存在其父亲节点
// 				fatNode = nodes.top();
// 				nodes.pop();
// 				curLeftOrRight = leftOrRight.top();
// 				leftOrRight.pop();

// 				curNode->right = fatNode;     // 更改节点的指针
// 				curNode = fatNode;
// 			}
// 			// 栈需要非空, 当前节点为父亲的右节点
// 			// 当前有点有右孩子，那么当前节点入栈，给右孩子打上标签
// 			if (curNode->right) {
// 				nodes.push(curNode);    // 当前节点为下面进栈的右孩子节点的父亲
// 				leftOrRight.push(curLeftOrRight);

// 				nextNode = curNode->right;
// 				// 寻找右孩子的最左节点
// 				while (nextNode) {
// 					nodes.push(nextNode);
// 					nextNode = nextNode->left;
// 					if (nextNode == curNode->right) {
// 						leftOrRight.push(0);
// 					}
// 					else {
// 						leftOrRight.push(1);
// 					}
// 				}
// 				nextNode = nodes.top();
// 				nodes.pop();
// 				curLeftOrRight = leftOrRight.top();
// 				leftOrRight.pop();

// 				curNode->right = nextNode;
// 				curNode = nextNode;
// 			}
// 			else if (!nodes.empty() && curLeftOrRight == 1) {
// 				curNode = nodes.top();
// 				nodes.pop();
// 				curLeftOrRight = leftOrRight.top();
// 				leftOrRight.pop();

// 				while (!nodes.empty() && curLeftOrRight == 1) {
// 					curNode = nodes.top();
// 					nodes.pop();
// 					curLeftOrRight = leftOrRight.top();
// 					leftOrRight.pop();
// 				}
// 			}

// 			// 栈为空，但是当前节点有右边孩子
// 		}
// 		return root;
// 	}
// };


// void makeTree(Node*& root, int val) {
// 	if (root == NULL) {
// 		Node* node = new Node(val);
// 		root = node;
// 		return;
// 	}
// 	else if (root->val > val) {
// 		makeTree(root->left, val);
// 	}
// 	else {
// 		makeTree(root->right, val);
// 	}
// }

// int main() {

// 	Solution sol;
// 	Node* root = NULL;
// 	int a[] = { 4,2,1,3,5 };
// 	int n = 5;
// 	for (int i = 0; i < n; i++) {
// 		makeTree(root, a[i]);
// 	}
// 	sol.treeToDoublyList(root);
// }
```

