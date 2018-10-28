/*************************************************************************
	> File Name: 68.cpp
	> Author: zj
	> Describe: 二叉树中两个节点的最低公共祖先
	> Created Time: Thu 11 Oct 2018 09:13:08 PM CST
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
        if( root==NULL || root==q || root==p  )
            return root;
        TreeNode* left = lowestCommonAncestor( root->left, p, q );
        TreeNode* right = lowestCommonAncestor( root->right, p, q );
        if( left==NULL )
            return right;
        if( right==NULL )
            return left;
        return root;
    }
};
