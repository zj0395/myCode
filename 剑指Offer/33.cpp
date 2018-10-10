/*************************************************************************
	> File Name: 33.cpp
	> Author: zj
	> Describe: 判断是否是二叉搜索树的后序遍历序列
                数组中任意两个数字都不相同
	> Created Time: Wed 10 Oct 2018 02:10:19 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool VerifySquenceOfBST(vector<int> sequence)
    {
        if( sequence.size() == 0 )
            return false;
        return isValid( sequence, 0, sequence.size()-1 );
    }
    bool isValid( vector<int> seq, int b, int e )
    {
        if( e-b <= 1 )
            return true;
        int rootValue = seq[e];
        int leftEnd = 0;
        for( ; leftEnd<e; ++leftEnd )
        {
            if( seq[leftEnd] >= rootValue )
                break;
        }
        for( int i=leftEnd; i<e; ++i )
            if( seq[i] < rootValue )
            {
                return false;
            }
        return isValid(seq, b, leftEnd-1) && isValid(seq, leftEnd, e-1);
    }
};

int main()
{
    vector<int> f{ 1, 3, 2 };
    cout<<Solution().VerifySquenceOfBST(f)<<"\n";
}
