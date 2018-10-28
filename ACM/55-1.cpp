/*************************************************************************
	> File Name: 55-1.cpp
	> Author: zj
	> Describe: 求二叉树的深度
                根节点到叶节点经过的最长路径是树的深度
	> Created Time: Thu 11 Oct 2018 04:42:31 PM CST
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
    int TreeDepth(TreeNode* pRoot)
    {
        return (pRoot==NULL) ? 0 : 1+max( TreeDepth(pRoot->left), TreeDepth(pRoot->right) );
    }
};
