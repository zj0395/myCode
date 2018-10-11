/*************************************************************************
	> File Name: 55-2.cpp
	> Author: zj
	> Describe: 判断二叉树是否为平衡二叉树
                平衡二叉树左右子树深度差不超过1
	> Created Time: Thu 11 Oct 2018 04:45:15 PM CST
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
    bool IsBalanced_Solution(TreeNode* pRoot) {
        flag = true;
        getHeight(pRoot);
        return flag;
    }
private:
    int getHeight(TreeNode* pRoot)
    {
        if( pRoot == NULL || !flag )
            return 0;
        int left = getHeight(pRoot->left);
        int right = getHeight(pRoot->right);
        if( abs(left-right) > 1 )
            flag = false;
        return 1+max(left,right);
    }
    bool flag;
};
