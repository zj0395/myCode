/*************************************************************************
	> File Name: Manacher.cpp
	> Author: zj
	> Describe: Manacher 算法
                计算字符串的最长回文子串
                https://www.cnblogs.com/z360/p/6375514.html
	> Created Time: Wed 31 Oct 2018 04:46:16 PM CST
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    string getMaxSubPalindrome(const string& str)
    {
        int len = str.size();
        string t( 2*len+1, '#' );
        int idx = -1;
        // 为奇偶长度都处理方便，添加分隔符
        while( ++idx < len )
        {
            t[idx*2+1] = str[idx];
        }

        len = 2*len+1;
        vector<int> lens( len, 1 );
        int maxBord = 0;
        int maxIdx = 0;
        for( int i=1; i<len; ++i )
        {
            int j = 1;
            if( i<maxBord )
                j = min( lens[2*maxIdx-i], maxBord-i );
            while( i-j>=0 && i+j<len && t[i-j] == t[i+j] )
            {
                ++j;
            }
            if( j+i > maxBord )
            {
                maxBord = j+i;
                maxIdx = i;
            }
            lens[i] = j*2-1;
        }

        // 算法部分已完成，开始取结果

        int maxLen = 0;
        maxIdx = 0;
        for( int i=0; i<len; ++i )
        {
            if( lens[i] > maxLen )
            {
                maxLen = lens[i];
                maxIdx = i;
            }
        }
        string ret;
        for( int i=maxIdx-(maxLen-1)/2; i<=maxIdx+(maxLen-1)/2; ++i )
        {
            if( t[i] != '#' )
                ret.push_back(t[i]);
        }
        return ret;
    }
};

int main()
{
    string t1 = "abcdefedc";
    string t2 = "aaaaefssfe";
    Solution s;
    cout<<s.getMaxSubPalindrome(t1)<<"\n";
    cout<<s.getMaxSubPalindrome(t2)<<"\n";
}
