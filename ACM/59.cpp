/*************************************************************************
	> File Name: 59.cpp
	> Author: zj
	> Describe: 滑动窗口最大值
                维护一个存储最大值索引的序列
	> Created Time: Thu 11 Oct 2018 07:23:13 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

class Solution {
public:
    vector<int> maxInWindows(const vector<int>& num, unsigned int size)
    {
        vector<int> ret;
        if( size == 0 )
            return ret;
        deque<int> iq;
        for( unsigned int i=0; i<num.size(); ++i )
        {
            while( !iq.empty() && i>=iq.front()+size )
                iq.pop_front();

            while( !iq.empty() && num[iq.back()] <= num[i] )
            {
                iq.pop_back();
            }

            iq.push_back(i);

            if( i+1>=size )
                ret.push_back( num[iq.front()] );
        }
        return ret;
    }
};

int main()
{
    vector<int> f = {2,3,4,2,6,2,5,1};
    for( int i:Solution().maxInWindows( f, 3 ) )
        cout<<i<<" ";
}
