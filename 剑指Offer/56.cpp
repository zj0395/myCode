/*************************************************************************
	> File Name: 56.cpp
	> Author: zj
	> Describe: 找到数组中只出现了一次的数字
                数组中，除了两个数字外，其它数字都出现了两次
                找到这两个数字
                原理1：对同一个数字异或两次，值不变
                原理2：一个数字与运算它的负数，会得到原数字中第一个为1的比特位
	> Created Time: Thu 11 Oct 2018 04:50:15 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
        int ret = 0;
        for( int t:data )
            ret ^= t; // 结果相当与两个不同数字的异或，重复的数字被消去了

        // ret中第一个为1的比特上，两个数字的值不同，根据该比特来区分两个数字
        ret &= -ret; // 结果中只有一个比特值为1;

        int ret1=0, ret2=0;
        for( int t:data )
        {
            if( ret & t )
                ret1 ^= t; // 有重复的数字都会被消去
            else
                ret2 ^= t;
        }
        *num1 = ret1;
        *num2 = ret2;
    }
};
