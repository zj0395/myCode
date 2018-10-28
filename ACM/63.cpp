/*************************************************************************
	> File Name: 63.cpp
	> Author: zj
	> Describe: 股票最大利润
                贪心算法
	> Created Time: Thu 11 Oct 2018 08:49:21 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if( prices.empty() )
            return 0;
        int minPrice = prices[0];
        int maxResult = 0;
        for( int i=1; i<prices.size(); ++i )
        {
            minPrice = min( minPrice, prices[i] );
            maxResult = max( maxResult, prices[i]-minPrice );
        }
        return maxResult;
    }
};
