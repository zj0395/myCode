/*************************************************************************
	> File Name: 44.cpp
	> Author: zj
	> Describe: 数字序列中的某一位数字
                0123456789101112131415... 的字符串中，求第 n 位
	> Created Time: Thu 11 Oct 2018 09:12:21 AM CST
 ************************************************************************/

#include <iostream>
#include <cmath>
#include <string>
#include <assert.h>
using namespace std;

class Solution
{
public:
    int getDigitIndex(int idx)
    {
        int place = 1;
        while( 1 )
        {
            int placeCount = (place==1?10:pow(10, place-1)*9) * place;
            if( placeCount >= idx )
                return getPlaceIndex(place, idx);
            idx -= placeCount;
            ++place;
        }
    }
private:
    int getPlaceIndex(int place, int idx)
    {
        --idx;
        int num = idx / place;
        int destNum = (place==1?0:pow(10, place-1)) + num;
        int offset = idx % place;
        return to_string(destNum)[offset] - '0';
    }
};

int main()
{
    Solution s;
    string testStr;
    for( int i=0; i<1000000; ++i )
        testStr += to_string(i);
    for( int i=100; i<testStr.size(); ++i )
    {
        assert( (testStr[i]-'0') == s.getDigitIndex(i+1));
    }
}
