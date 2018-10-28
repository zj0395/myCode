/*************************************************************************
	> File Name: 27.cpp
	> Author: zj
	> Describe: 二叉树的镜像
	> Created Time: Wed 10 Oct 2018 09:55:01 AM CST
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
    void Mirror(TreeNode *pRoot) {
        if( pRoot == NULL )
            return;
        Mirror( pRoot->left );
        Mirror( pRoot->right );
        TreeNode* tmp = pRoot->left;
        pRoot->left = pRoot->right;
        pRoot->right = tmp;
    }
};
