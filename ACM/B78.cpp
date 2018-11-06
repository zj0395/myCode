/*************************************************************************
	> File Name: B78.cpp
	> Author: zj
	> Describe: 满足最大最小值差小于一定值的子数组个数
给定数组arr和整数num,共返回有多少个子数组满足如下情况:
max(arr[i..j]) - min(arr[i..j]) <= num
max(arr[i..j])表示子数组arr[i..j]中的最大值,min(arr[i..j])表示子数组arr[i.
中的最小值。
【要求】
如果数组长度为N,请实现时间复杂度为O(N)的解法
	> Created Time: Tue 06 Nov 2018 07:51:07 PM CST
 ************************************************************************/

#include <iostream>
#include <deque>
#include <vector>
#include <cassert>
using namespace std;

class Solution
{
public:
    int getNumOfSumArray( vector<int> & array, int diff )
    {
        deque<int> mins, maxs;
        int l = 0;
        int r = 0;
        int len = array.size();
        int ret = 0;
        while( l<len )
        {
            while( r<len )
            {
                while( ! mins.empty() && array[mins.back()]>=array[r] )
                    mins.pop_back();
                mins.push_back(r);
                while( ! maxs.empty() && array[mins.back()]<=array[r] )
                    maxs.pop_back();
                maxs.push_back(r);
                if( array[maxs.front()] - array[mins.front()] > diff )
                    break;
                ++r;
            }
            if( mins.front() == l )
                mins.pop_front();
            if( maxs.front() == l )
                maxs.pop_front();
            ret += r-l-1;
            ++l;
        }
        return ret;
    }
};

int main()
{
    vector<int> t1{1, 4, 5, 7, 6};
    Solution s;
    assert( s.getNumOfSumArray(t1, 4) == 8);
    vector<int> t2{1, 3, 4, 5, 7, 6};
    assert( s.getNumOfSumArray(t2, 4) == 13);
}
