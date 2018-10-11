/*************************************************************************
	> File Name: A69.cpp
	> Author: zj
	> Describe: 判断字符串是否表示数值（包括整数和小数）
                "+100","5e2","-123","3.1416","-1E-16" >> true
                "12e","1a3.14","1.2.3","+-5","12e+4.3" >> false
	> Created Time: Thu 11 Oct 2018 09:27:36 PM CST
 ************************************************************************/

#include <iostream>
#include <cstring>
using namespace std;

class Solution {
public:
    bool isNumeric(char* str)
    {
        int len = strlen(str);
        int eIdx = 0;
        for( ; eIdx < len; ++eIdx )
            if( str[eIdx] == 'e' || str[eIdx] == 'E' )
                break;
        if( eIdx == len )
            return isOneNum( str, len, 0 );
        return isOneNum( str, eIdx, 0 ) && isOneNum( str+eIdx+1, len-eIdx-1, 1 );
    }
private:
    bool isDigit( char c )
    {
        return c>='0' && c<='9';
    }
    bool isOneNum( char*str, int len, bool pointFlag )
    {
        if( len == 0 )
            return false;
        char first = str[0];
        if( ! isDigit(first) && first!='-' && first!='+' )
            return false;
        for( int i=1; i<len; ++i  )
        {
            char c = str[i];
            if( c=='e' || c=='E' || c=='-'||c=='+' )
                return false;
            else if( c=='.' )
            {
                if( pointFlag || i+1>len || !isDigit( str[i+1] ) )
                    return false;
                pointFlag = 1;
            }
            else if( c<'0' || c>'9' )
                return false;
        }
        return true;
    }
};

int main()
{
}
