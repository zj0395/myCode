/*************************************************************************
	> File Name: 34.cpp
	> Author: zj
	> Describe: 打印二叉树中和为输入整数的所有路径，从根到子节点
	> Created Time: Wed 10 Oct 2018 02:30:04 PM CST
 ************************************************************************/

#include <iostream>
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
    vector<vector<int> > FindPath(TreeNode* root,int expectNumber)
    {
        vector< vector<int> > ret;
        dfs( root, expectNumber, vector<int>(), ret );
        return ret;
    }
    void dfs( TreeNode*root, int expectNumber, vector<int>ret, vector< vector<int> >& all )
    {
        if( root == NULL || root->val > expectNumber )
            return;
        ret.push_back( root->val );
        expectNumber -= root->val;
        if( expectNumber == 0 && root->left==NULL && root->right==NULL )
        {
            all.push_back( ret );
            return;
        }
        dfs( root->left,  expectNumber, ret, all );
        dfs( root->right, expectNumber, ret, all );
    }
};
