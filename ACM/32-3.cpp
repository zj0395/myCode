/*************************************************************************
	> File Name: 32-3.cpp
	> Author: zj
	> Describe: 按之字形打印二叉树
                第一行从左到右，第二行右到左，第三行左倒右
	> Created Time: Wed 10 Oct 2018 11:20:37 AM CST
 ************************************************************************/

#include <iostream>
#include <queue>
#include <vector>
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
     vector<vector<int> > Print(TreeNode* pRoot) {
        vector< vector<int> > ret;
        queue<TreeNode*> tQ;
        tQ.push( pRoot );
        int reverse = 0;
        while( ! tQ.empty() )
        {
            vector<int> oneLayer;
            int cnt = tQ.size(); // size of current layer
            while( cnt-- )
            {
                TreeNode* cur = tQ.front();
                tQ.pop();
                if( cur != NULL )
                {
                    tQ.push( cur->left );
                    tQ.push( cur->right );
                    oneLayer.push_back( cur->val );
                }
            }
            if( reverse )
            {
                vector<int> tmp{ oneLayer.rbegin(), oneLayer.rend() };
                tmp.swap(oneLayer);
            }
            reverse = reverse ? 0 : 1;
            if( ! oneLayer.empty() )
                ret.push_back( oneLayer );
        }
        return ret;
    }
};
