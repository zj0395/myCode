/*************************************************************************
	> File Name: 53.cpp
	> Author: zj
	> Describe: 数字在排序数组中出现的次数
	> Created Time: Thu 11 Oct 2018 04:07:22 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int GetNumberOfK(vector<int> data ,int k) {
        return upper_bound(data.begin(), data.end(), k) - lower_bound(data.begin(), data.end(), k);
    }
};
