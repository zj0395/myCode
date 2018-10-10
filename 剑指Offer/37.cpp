/*************************************************************************
	> File Name: 37.cpp
	> Author: zj
	> Describe: 序列化二叉树
                二叉树转为字符串，再转回二叉树
	> Created Time: Wed 10 Oct 2018 03:25:39 PM CST
 ************************************************************************/

#include <iostream>
#include <cstring>
#include <string>
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
    char* Serialize(TreeNode *root) {
        if( root == NULL )
        {
            char* ret = new char[2];
            strcpy( ret, "#" );
            return ret;
        }
        string r = to_string(root->val);
        r.push_back(',');
        char* left  = Serialize(root->left);
        char* right = Serialize(root->right);
        char *ret = new char[strlen(left) + strlen(right) + r.size() + 1];
        strcpy(ret, r.c_str());
        strcat(ret, left);
        strcat(ret, right);
        return ret;
    }
    TreeNode* Deserialize(char *str) {
        return deCode(str);
    }
private:
    TreeNode* deCode(char *& str)
    {
        if( str[0] == '#' )
        {
            ++str;
            return NULL;
        }
        int num = 0;
        while( *str != ',' )
            num = num*10 + (*(str++)-'0');
        str++;
        TreeNode* root = new TreeNode(num);
        root->left = deCode(str);
        root->right = deCode(str);
        return root;
    }
};
