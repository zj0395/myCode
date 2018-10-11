/*************************************************************************
	> File Name: 48.cpp
	> Author: zj
	> Describe: 最长不含重复字符的子串
	> Created Time: Thu 11 Oct 2018 01:55:24 PM CST
 ************************************************************************/

#include <iostream>
#include <cstring>
using namespace std;

class Solution
{
public:
    int getLongOnlySubStr(string str)
    {
        int idxs[26];
        memset(idxs, -1, sizeof(int)*26);
        int maxLen = 0;
        int curLen = 0;
        for( int i=0; i<str.size(); ++i )
        {
            int preI = idxs[ str[i]-'a' ];
            if( preI == -1 || (i - preI) > curLen )
            {
                ++curLen;
            }
            else
            {
                maxLen = max( curLen, maxLen );
                curLen = i - preI;
            }
            idxs[ str[i]-'a' ] = i;
        }
        maxLen = max( curLen, maxLen );
        return maxLen;
    }
};
int main()
{
    Solution s;
    cout<<s.getLongOnlySubStr( "arabcacfr" )<<"\n";
}
