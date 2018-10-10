/*************************************************************************
	> File Name: 40.cpp
	> Author: zj
	> Describe: 选出数组中前K个最小数字，本文件使用方法2
                方法1： 基于快速排序改编，见https://github.com/zj0395/myCode/tree/master/CPP/Algorithm/MaxM
                方法2： 基于堆排序
	> Created Time: Wed 10 Oct 2018 04:28:06 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        vector<int> ret;
        if( input.size() < k )
            return ret;
        make_heap( input.begin(), input.end(), greater<int>());
        while( k-- )
        {
            pop_heap( input.begin(), input.end(), greater<int>());
            ret.push_back( input[ input.size()-1 ] );
            input.pop_back();
        }
        return ret;
    }
};

int main()
{
    vector<int> input{4,5,1,6,2,7,3,8};
    for( int m : Solution().GetLeastNumbers_Solution(input, 4) )
        cout<<m<<" ";
    cout<<"\n";
}
