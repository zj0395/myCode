/*************************************************************************
	> File Name: isNumber.cpp
	> Author: zj
	> Mail: zhangjian0395@163.com
	> Created Time: Sat 29 Jul 2017 09:47:55 AM CST
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;
bool isNumber(string s) {
        bool flag = true;
        bool dotflag=true, eflag=false, spaceflag=true, numberflag=true, ngflag=true;
        int dottimes=0, etimes=0, spacetimes=0, numtimes=0,ngtimes=0;
        bool numberMust=0;
        const int nums = s.size();
        for( int i=0; i<nums;  ++i)
        {
            if(('9' >= s[i]&& s[i]>='0'))
            {
                if( !numberflag )
                    flag = false;
                dotflag=eflag=spaceflag=true;
                ngflag = false;
                numberMust=false;
                ++numtimes;
            }
            else if( s[i]==' ')
            {
                if( numtimes || dottimes || ngtimes)
                {
                    dotflag=eflag=numberflag=false;
                }
                if (!spaceflag)
                    flag=false;
                ++spacetimes;
            }
            else if( s[i] == '.')
            {
                if(dotflag)
                {
                    ngflag = dotflag = false;
                    numberflag = true;
                }
                else
                    flag = false;
                ++dottimes;
            }
            else if( s[i] == 'e')
            {
                if(eflag)
                {
                    dotflag = eflag = spaceflag = false;
                    ngflag = numberflag = true;
                }
                else
                    flag = false;
                numberMust=true;
                ++etimes;
                dottimes = dottimes ? dottimes : 1;
            }
            else if( s[i] == '-' || s[i] =='+' )
            {
                if( i-1>=0 && s[i-1]=='e' )
                    continue;
                if( !ngflag )
                    flag = false;
                else
                {
                    ngflag = eflag = spaceflag = false;
                    dotflag = true;
                }
                numberflag=true;
                ++ngtimes;
            }
            else
                flag = false;
        }
        if( etimes>1 || dottimes>1 || numberMust || ngtimes>1 )
            return false;
        return flag;
    }
int main()
{
    cout<<isNumber(" 005047e+6")<<endl;//1
    cout<<isNumber(" -.7e+0432")<<endl;//1
    return 0;
}
