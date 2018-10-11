/*************************************************************************
	> File Name: A71.cpp
	> Author: zj
	> Describe: 二叉树的下一个节点
                输出中序遍历下，给定节点的下一个节点
	> Created Time: Thu 11 Oct 2018 10:13:09 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;

struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {

    }
};

class Solution {
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode)
    {
        if( pNode->right != NULL )
        {
            pNode = pNode->right;
            while( pNode->left != NULL )
            {
                pNode = pNode->left;
            }
        }
        else
        {
            while( pNode->next != NULL && pNode->next->left != pNode )
            {
                pNode = pNode->next;
            }
            pNode = pNode->next;
        }
        return pNode;
    }
};
