/*************************************************************************
	> File Name: 65.cpp
	> Author: zj
	> Describe: 不适用加减乘除做加法
                写一个函数，求两个整数之和，要求不得使用 +、-、*、/ 四则运算符号。
	> Created Time: Thu 11 Oct 2018 08:57:35 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;

class Solution {
public:
    int Add(int num1, int num2)
    {
        return num2==0 ? num1 : Add( num1^num2, (num1&num2)<<1 );
    }
};
