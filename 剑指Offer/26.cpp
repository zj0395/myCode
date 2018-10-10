/*************************************************************************
	> File Name: 26.cpp
	> Author: zj
	> Describe: 树B是否为树A的子结构
	> Created Time: Wed 10 Oct 2018 09:38:54 AM CST
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
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if( pRoot1==NULL || pRoot2==NULL )
            return false;
        return isSameWithRoot(pRoot1, pRoot2) || HasSubtree( pRoot1->left, pRoot2 ) || HasSubtree( pRoot1->right, pRoot2 );
    }
    bool isSameWithRoot(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if( pRoot2 == NULL )
            return true;
        if( pRoot1 == NULL )
            return false;
        if( pRoot1->val != pRoot2->val )
            return false;
        return isSameWithRoot( pRoot1->left, pRoot2->left ) && isSameWithRoot(pRoot1->right, pRoot2->right);
    }
};
