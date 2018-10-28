/*************************************************************************
	> File Name: 32-1.cpp
	> Author: zj
	> Describe: 从上往下打印二叉树
                使用队列，一层一层解决
	> Created Time: Wed 10 Oct 2018 11:09:41 AM CST
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
    vector<int> PrintFromTopToBottom(TreeNode* root) {
        vector<int> ret;
        queue<TreeNode*> tQ;
        tQ.push( root );
        while( ! tQ.empty() )
        {
            int cnt = tQ.size(); // size of current layer
            while( cnt-- )
            {
                TreeNode* cur = tQ.front();
                tQ.pop();
                if( cur != NULL )
                {
                    tQ.push( cur->left );
                    tQ.push( cur->right );
                    ret.push_back( cur->val );
                }
            }
        }
        return ret;
    }
};
