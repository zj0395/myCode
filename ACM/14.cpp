/*************************************************************************
	> File Name: 14.cpp
	> Author: zj
	> Describe: 数字拆分，使乘积最大，与3相关进行大量优化
	> Created Time: Tue 09 Oct 2018 04:00:04 PM CST
 ************************************************************************/

#include <iostream>
#include <cstring>
using namespace std;

class Solution {
public:
    int integerBreak(int n) {
        if (n == 2 || n == 3) return n - 1;
        int res = 1;
        while (n > 4) {
            res *= 3;
            n -= 3;
        }
        return res * n;
    }
};

int main()
{
    Solution s;
    for( int i=2; i<19; ++i )
        cout<<i<<":"<<s.integerBreak(i)<<"\n";
}
