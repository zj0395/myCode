/*************************************************************************
	> File Name: 31.cpp
	> Author: zj
	> Describe: 栈的弹出序列是否可匹配亚压入序列
                进行模拟压入弹出
                要求栈中所有数字都不相等
	> Created Time: Wed 10 Oct 2018 10:56:37 AM CST
 ************************************************************************/

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        stack<int> tS;
        for( int i=0, popIdx=0; i<pushV.size(); ++i )
        {
            tS.push( pushV[i] );
            while( popIdx<popV.size() && !tS.empty() && tS.top() == popV[popIdx] )
            {
                tS.pop();
                ++popIdx;
            }
        }
        return tS.empty();
    }
};

int main()
{
    vector<int> pushV = {1, 2, 3, 4, 5};
    vector<int> popV =  {4, 3, 5, 1, 2};
    cout<<Solution().IsPopOrder(pushV, popV)<<"\n";
}
