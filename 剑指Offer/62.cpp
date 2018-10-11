/*************************************************************************
	> File Name: 62.cpp
	> Author: zj
	> Describe: 圆圈中最后剩下的树
                约瑟夫环
	> Created Time: Thu 11 Oct 2018 08:46:39 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;

class Solution {
public:
    int LastRemaining_Solution(int n, int m)
    {
        if( n==0 )
            return -1;
        if( n==1 )
            return 0;
        return (LastRemaining_Solution(n-1, m) + m)%n;
    }
};
