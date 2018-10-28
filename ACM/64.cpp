/*************************************************************************
	> File Name: 64.cpp
	> Author: zj
	> Describe: 求1+2+3+...+n
                不使用乘除法、for、while、if、else、switch、case及(A?B:C)
	> Created Time: Thu 11 Oct 2018 08:55:12 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;

class Solution {
public:
    int Sum_Solution(int n) {
        int ret = n;
        n==0 || (ret += Sum_Solution(n-1));
        return ret;
    }
};
