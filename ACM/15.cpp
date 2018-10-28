/*************************************************************************
	> File Name: 15.cpp
	> Author: zj
	> Describe: 二进制中1的个数
	> Created Time: Tue 09 Oct 2018 04:36:43 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;

// 解法2，每次减1再进行与运算，均会去除最低位的1
int NumberOf1(int n) {
    int cnt = 0;
    while (n != 0) {
        cnt++;
        n &= (n - 1);
    }
    return cnt;
}

class Solution {
public:
    int  NumberOf1(int n) {
        int num = sizeof(int)*8;
        int count = 0;
        int a = 1;
        do
        {
            if( a&n )
                ++count;
            a <<= 1;
        }while( num-- );
        return count;
    }
};
