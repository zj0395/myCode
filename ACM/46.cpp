/*************************************************************************
	> File Name: 46.cpp
	> Author: zj
	> Describe: 数字翻译为字符串
                1 -> a, 26 -> z
	> Created Time: Thu 11 Oct 2018 10:18:32 AM CST
 ************************************************************************/

#include <iostream>
using namespace std;

class Solution {
public:
    int numDecodings(string s) {
        if( s.empty() || s.front() == '0' )
            return 0;;
        int len = s.size();
        int r1 = 1, r2 = 1;
        for( int i=1; i<len; ++i )
        {
            // zeor only can be a part of number, as 20, 10
            if( s[i] == '0' )
                r1 = 0;
            if(s[i - 1] == '1' || (s[i - 1] == '2' && s[i] <= '6') )
            {
                int t = r1;
                r1 = r2 + t;
                r2 = t;
            }
            else
            {
                r2 = r1;
            }
        }
        return r1;
    }
};
