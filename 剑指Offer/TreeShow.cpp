/*************************************************************************
	> File Name: TreeShow.cpp
	> Author: zj
	> Describe: 二叉树非递归遍历
                前序、中序、后序
	> Created Time: Thu 25 Oct 2018 05:45:18 PM CST
 ************************************************************************/

#include <iostream>
#include <stack>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v){val=v; left=right=NULL;}
};

// 非递归前序遍历
void preOrder(TreeNode* pRoot)
{
    if( pRoot == NULL )
        return;
    stack<TreeNode*> treeStack;
    TreeNode* p = pRoot;
    while( p != NULL || ! treeStack.empty() )
    {
        while( p != NULL )
        {
            cout<<p->val<<" ";
            treeStack.push( p );
            p = p->left;
        }
        if( ! treeStack.empty() )
        {
            p = treeStack.top()->right;
            treeStack.pop();
        }
    }
}

// 非递归中序遍历
void inOrder( TreeNode* pRoot )
{
    if( pRoot == NULL )
        return;
    stack<TreeNode*> treeStack;
    TreeNode* p = pRoot;
    while( p != NULL || ! treeStack.empty() )
    {
        while( p!=NULL )
        {
            treeStack.push(p);
            p = p->left;
        }
        if( ! treeStack.empty() )
        {
            p = treeStack.top();
            cout << p->val<<" ";
            treeStack.pop();
            p = p->right;
        }
    }
}

// 非递归后序遍历
void postOrder(TreeNode* pRoot)
{
    if( pRoot == NULL )
        return;
    stack<TreeNode*> treeStack;
    TreeNode* p = NULL;
    TreeNode* pre = NULL;
    treeStack.push( pRoot );
    while( ! treeStack.empty() )
    {
        p = treeStack.top();
        if( (p->left==NULL && p->right==NULL) ||
            (pre!=NULL && (pre==p->left || pre==p->right)) )
        {
            cout<<p->val<<" ";
            pre = p;
            treeStack.pop();
            continue;
        }
        if( p->left != NULL )
            treeStack.push(p->right);
        if( p->right != NULL )
            treeStack.push(p->left);
    }
}

int main()
{
    TreeNode* root = new TreeNode(7);
    root->left = new TreeNode(5);
    root->right = new TreeNode(9);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(6);
    root->right->left = new TreeNode(8);
    root->right->right = new TreeNode(10);
    cout<<"PreOrder:";
    preOrder( root );
    cout<<"\n";
    cout<<"InOrder:";
    inOrder( root );
    cout<<"\n";
    cout<<"PostOrder:";
    postOrder(root);
}
