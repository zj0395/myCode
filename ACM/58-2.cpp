/*************************************************************************
	> File Name: 58-2.cpp
	> Author: zj
	> Describe: 左旋转字符串
	> Created Time: Thu 11 Oct 2018 07:19:22 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;

class Solution {
public:
    string LeftRotateString(string str, int n) {
        reverse( str, 0, n-1 );
        reverse( str, n, str.size()-1 );
        return string( str.rbegin(), str.rend() );
    }
private:
    void reverse( string& str, int b, int e )
    {
        while( b < e )
        {
            swap( str[b++], str[e--] );
        }
    }
};

int main()
{
    cout<< Solution().LeftRotateString("abcXYZdef", 3)<<"\n";
}
