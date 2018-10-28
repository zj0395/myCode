/*************************************************************************
	> File Name: 32-2.cpp
	> Author: zj
	> Describe: 把二叉树打印成多行
	> Created Time: Wed 10 Oct 2018 11:15:41 AM CST
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
            if( ! oneLayer.empty() )
                ret.push_back( oneLayer );
        }
        return ret;
    }
};
