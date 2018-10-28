/*************************************************************************
	> File Name: 57-2.cpp
	> Author: zj
	> Describe: 和为S的连续正数序列
	> Created Time: Thu 11 Oct 2018 07:01:48 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int> > FindContinuousSequence(int sum) {
        int b=1, e=2;
        int cur = 1;
        vector< vector<int> > ret;
        while( b < sum )
        {
            if( cur > sum )
            {
                cur -= b++;
            }
            else if( cur < sum )
            {
                cur += e++;
            }
            else
            {
                vector<int> oneLine;
                for( int i=b; i<e; ++i )
                    oneLine.push_back(i);
                ret.push_back(oneLine);
                cur -= b;
                ++b;
            }
        }
        return ret;
    }
};

int main()
{
    Solution s;
    auto rr = s.FindContinuousSequence( 100 );
    for( auto & s : rr )
    {
        for( int a:s )
            cout<<a<<" ";
        cout<<"\n";
    }
}
