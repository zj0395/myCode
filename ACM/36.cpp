/*************************************************************************
	> File Name: 36.cpp
	> Author: zj
	> Describe: 二叉搜索树与双向链表
                将二叉搜索树转为排序的双向链表
                不创建任何新节点，只调整指针
	> Created Time: Wed 10 Oct 2018 03:07:42 PM CST
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
    void Transform( TreeNode* root )
    {
        if( root == NULL )
            return;
        Transform( root->left );
        root->left = pre;
        if( pre != NULL )
            pre->right = root;
        pre = root;
        if( head == NULL )
            head = root;
        Transform( root->right );
    }
    TreeNode* Convert(TreeNode* pRootOfTree)
    {
        pre = NULL;
        head = NULL;
        Transform(pRootOfTree);
        return head;
    }
private:
    TreeNode* pre;
    TreeNode* head;
};
