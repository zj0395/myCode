/*************************************************************************
	> File Name: 54.cpp
	> Author: zj
	> Describe: 二叉搜索树查找
                中序遍历
	> Created Time: Thu 11 Oct 2018 04:18:42 PM CST
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
    TreeNode* KthNode(TreeNode* pRoot, int k)
    {
        cnt = 0;
        ret = NULL;
        Find( pRoot, k );
        return ret;
    }
private:
    void Find( TreeNode* pRoot, int k )
    {
        if( pRoot == NULL || cnt >= k )
        {
            return;
        }
        Find( pRoot->left, k );
        if( ++cnt == k )
            ret = pRoot;
        Find( pRoot->right, k );
    }
    int cnt;
    TreeNode* ret;
};

int main()
{
    TreeNode* root = new TreeNode(8);

    root->left = new TreeNode(6);
    root->left->left = new TreeNode(5);
    root->left->right = new TreeNode(7);

    root->right = new TreeNode(10);
    root->right->left = new TreeNode(9);
    root->right->right = new TreeNode(11);

    Solution s;
    cout<<s.KthNode( root, 2 )->val<<"\n";
}
