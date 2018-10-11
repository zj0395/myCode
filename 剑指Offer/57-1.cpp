/*************************************************************************
	> File Name: 57.cpp
	> Author: zj
	> Describe: 有序数组中找到和为S的两个数字
	> Created Time: Thu 11 Oct 2018 06:55:34 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> FindNumbersWithSum(vector<int> array,int sum) {
        vector<int> ret;
        vector<int>::iterator b = array.begin();
        auto e = array.end()-1;
        while( b!=e && b<array.end() && e>=array.begin() )
        {
            if( *b + *e > sum )
                --e;
            else if( *b + *e < sum )
                ++b;
            else
            {
                ret.push_back(*b);
                ret.push_back(*e);
                return ret;
            }
        }
        return ret;
    }
};
