/*************************************************************************
	> File Name: 58-1.cpp
	> Author: zj
	> Describe: 翻转单词序列
                “student. a am I” >> “I am a student.”
	> Created Time: Thu 11 Oct 2018 07:13:42 PM CST
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string ReverseSentence(string str) {
        int b=0;
        for( int i=0; i<str.size(); ++i )
        {
            if( str[i] == ' ' )
            {
                reverse( str, b, i-1 );
                b = i+1;
            }
        }
        reverse( str, b, str.size()-1 );
        return string( str.rbegin(), str.rend() );
    }
private:
    void reverse( string& str, int b, int e )
    {
        while( b < e )
        {
            swap( str[b], str[e] );
            b++;
            --e;
        }
    }
};
