/*************************************************************************
	> File Name: 42.cpp
	> Author: zj
	> Describe: 连续子数组的最大和
	> Created Time: Wed 10 Oct 2018 04:56:37 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int FindGreatestSumOfSubArray(vector<int> array) {
        if( array.empty() )
            return 0;
        int maxSum = array[0];
        int curSum = array[0];
        for( int i=1; i<array.size(); ++i )
        {
            curSum += array[i];
            if( curSum < array[i] )
                curSum = array[i];
            if( maxSum < curSum )
                maxSum = curSum;
        }
        return maxSum;
    }
};
