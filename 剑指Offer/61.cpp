/*************************************************************************
	> File Name: 61.cpp
	> Author: zj
	> Describe: 扑克牌顺子
	> Created Time: Thu 11 Oct 2018 08:37:15 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool IsContinuous( vector<int> numbers ) {
        if( numbers.size()<5 )
            return false;
        std::sort(numbers.begin(), numbers.end());
        int cnt = 0;
        int idx = 0;
        while( idx<numbers.size() && numbers[idx] ==0 )
        {
            ++idx;
            ++cnt;
        }
        for( ; idx<numbers.size()-1; ++idx )
        {
            if( numbers[idx+1] == numbers[idx] )
                return false;
            cnt -= numbers[idx+1] - numbers[idx] - 1;
        }
        return cnt >= 0;
    }
};

int main()
{
    cout<<Solution().IsContinuous( vector<int>{1,3,2,4,6} )<<"\n";
}
