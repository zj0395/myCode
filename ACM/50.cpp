/*************************************************************************
	> File Name: 50.cpp
	> Author: zj
	> Describe: 第一个只出现一次的字符，返回索引
                每个字符只有三种状态，0、1、多个，只需要2bit
	> Created Time: Thu 11 Oct 2018 02:52:15 PM CST
 ************************************************************************/

#include <iostream>
#include <bitset>
using namespace std;

class Solution {
public:
    int FirstNotRepeatingChar(string str) {
        int len = str.size();
        bitset<256> b1, b2;
        for( int i=0; i<len; ++i )
        {
            int c = str[i];
            if( ! b1[c] && !b2[c]  )
                b1.set(c);
            else if( b1[c] && !b2[c] )
                b2.set(c);
        }
        for( int i=0; i<len; ++i )
            if( b1[ str[i] ] && !b2[ str[i] ] )
                return i;
        return -1;
    }
};

int main()
{
    bitset<320> f;
    bitset<321> s;
    cout<<sizeof(f)<<" "<<sizeof(s)<<"\n";
}
