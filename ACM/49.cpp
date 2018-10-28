/*************************************************************************
	> File Name: 49.cpp
	> Author: zj
	> Describe: 丑数，只包含因子 2、3、5 的数字
                求从小到大的第 n 个丑数
	> Created Time: Thu 11 Oct 2018 02:10:50 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int GetUglyNumber_Solution(int index)
    {
        if( index <= 6 )
            return index;
        vector<int> result( index, 0 );
        result[0] = 1;
        int idx1=0, idx2=0, idx3=0;
        for( int i=1; i<index; ++i )
        {
            int p1 = result[idx1]*2;
            int p2 = result[idx2]*3;
            int p3 = result[idx3]*5;
            result[i] = min( p1, min(p2, p3) );
            if( result[i] == p1 )
                ++idx1;
            if( result[i] == p2 )
                ++idx2;
            if( result[i] == p3 )
                ++idx3;
        }
        return result.back();
    }
};

int main()
{
    Solution s;
//    for(int i=1; i<8; ++i)
        cout<<s.GetUglyNumber_Solution(7)<<"\n";
}
