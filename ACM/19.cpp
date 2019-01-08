/*************************************************************************
	> File Name: 19.cpp
	> Author: zj
	> Describe: 正则表达式匹配，动态规划
	> Created Time: Tue 09 Oct 2018 06:35:10 PM CST
 ************************************************************************/

/*
 * 请实现一个函数用来匹配包括'.'和'*'的正则表达式。
 * 模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（包含0次）。
 * 在本题中，匹配是指字符串的所有字符匹配整个模式。
 * 例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但是与"aa.a"和"ab*a"均不匹配
 */

#include <iostream>
#include <cstring>
using namespace std;

class Solution {
public:
    bool match(char* str, char* pattern)
    {
        int m = strlen(str), n=strlen(pattern);
        bool ** dp = new bool* [m+1];
        for(int i=0; i<=m; ++i)
        {
            dp[i] = new bool[n+1];
            memset(dp[i], 0, sizeof(bool)*n);
        }
        dp[0][0] = true;
        for( int i=1; i<=n; ++i )
            if( pattern[i-1] == '*' )
                dp[0][i] = dp[0][i-2];

        for( int i=1; i<=m; ++i )
        {
            for( int j=1; j<=n; ++j )
            {
                if( str[i-1] == pattern[j-1] || pattern[j-1] == '.' )
                    dp[i][j] = dp[i-1][j-1];
                else if( pattern[j-1] == '*' )
                {
                    if( pattern[j-2] == str[i-1] || pattern[j-2] == '.' )
                    {
                        dp[i][j] |= dp[i][j-1]; // a* as single a
                        dp[i][j] |= dp[i][j-2]; // a* as empty
                        dp[i][j] |= dp[i-1][j]; // a* as multipe a
                    }
                    else
                        dp[i][j] = dp[i][j-2]; // a* only can be count as empty
                }
            }
        }
        bool result = dp[m][n];
        for(int i=0; i<=m; ++i)
        {
            delete []dp[i];
        }
        delete []dp;
        return result;
    }
};
