/*************************************************************************
	> File Name: 68-1.cpp
	> Author: zj
	> Describe: 二叉搜索树中两个节点的最低公共祖先
	> Created Time: Thu 11 Oct 2018 09:23:05 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if( root == NULL )
            return root;
        if( p->val < root->val && q->val < root->val )
            return lowestCommonAncestor(root->left, p, q);
        if( p->val > root->val && q->val > root->val )
            return lowestCommonAncestor(root->right, p, q);
        return root;
    }
};
