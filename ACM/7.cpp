/*************************************************************************
	> File Name: 7.cpp
	> Author: zj
	> Describe: 根据前序和中序遍历的结果重建二叉树
	> Created Time: Tue 09 Oct 2018 10:40:26 AM CST
 ************************************************************************/

#include <iostream>
#include <vector>
#include <map>
using namespace std;

// https://www.nowcoder.com/practice/8a19cbe657394eeaac2f6ea9b0f6fcf6?tpId=13&tqId=11157&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
/**
 * Definition for binary tree
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* reConstructBinaryTree(vector<int>pre, int b, int e, map<int, int>&idxs, int inL)
    {
        if( b > e )
            return NULL;
        TreeNode * root = new TreeNode( pre[b] );
        int vinIdx = idxs[ pre[b] ];
        int leftSize = vinIdx - inL;
        root->left = reConstructBinaryTree(pre, b+1, b+leftSize, idxs, inL );
        root->right = reConstructBinaryTree(pre, b+1+leftSize, e, idxs, vinIdx+1);
        return root;
    }
    // 前序遍历的第一个作为根节点
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        map<int, int> idxs;
        for( int i=0; i<vin.size(); ++i )
            idxs[ vin[i] ] = i;
        return reConstructBinaryTree( pre, 0, pre.size()-1, idxs, 0);
    }
};

int main()
{
    Solution s;
    vector<int> a = {3, 9, 20, 15, 7};
    vector<int> b = {9, 3, 15, 20, 7};
    TreeNode* f = s.reConstructBinaryTree(a, b);
    cout<<f->val;
}
