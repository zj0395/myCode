/*************************************************************************
	> File Name: numof1.cpp
	> Author: zj
	> Mail: zhangjian0395@163.com
	> Created Time: Sun 16 Jul 2017 06:20:46 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
int getNumOf1(int num)
{
    int n=0;
    while(num>0)
    {
        num=num&num-1;//beautiful
        ++n;
    }
    return n;
}

int main()
{
    for( int i=0;i<10;++i )
        cout<<getNumOf1(i)<<endl;
}
