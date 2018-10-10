/*************************************************************************
	> File Name: 28.cpp
	> Author: zj
	> Describe: 判断二叉树是否对称，即二叉树是否与本身的镜像相同
	> Created Time: Wed 10 Oct 2018 09:57:33 AM CST
 ************************************************************************/

#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};

class Solution {
public:
    bool isSymmetrical(TreeNode* pRoot)
    {
        if( pRoot == NULL )
            return true;
        return isSymmetrical( pRoot->left, pRoot->right );
    }
    bool isSymmetrical( TreeNode* left, TreeNode* right )
    {
        if( left == NULL && right == NULL )
            return true;
        if( left == NULL || right == NULL )
            return false;
        if( left->val != right->val )
            return false;
        return isSymmetrical( left->left, right->right ) && isSymmetrical(left->right, right->left);
    }

};
