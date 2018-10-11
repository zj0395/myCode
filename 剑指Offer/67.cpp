/*************************************************************************
	> File Name: 67.cpp
	> Author: zj
	> Describe: 字符转换为整数
                +2147483647 >> 2147483647
                1a33 >> 0
	> Created Time: Thu 11 Oct 2018 09:06:45 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;

class Solution {
public:
    int StrToInt(string str) {
        if( str.empty() )
            return 0;
        bool isNegative = str[0] == '-';
        int ret = 0;
        for( int i=0; i<str.size(); ++i )
        {
            char c = str[i];
            if( i==0 && (c=='+' ||c=='-') )
                continue;
            if( c<'0' || c>'9' )
                return 0;
            ret = ret*10 + c-'0';
        }
        return isNegative ? -ret : ret;
    }
};
