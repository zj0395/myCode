/*************************************************************************
	> File Name: test.cpp
	> Author: zj
	> Mail: zhangjian0395@163.com
	> Created Time: Sun 16 Jul 2017 08:10:38 PM CST
 ************************************************************************/

#include<iostream>
#include <sys/time.h>
#include"crackBinary.h"
using namespace std;
int main()
{
    int nums[][9]={
        {8,0,0,0,0,0,0,0,0},
        {0,0,3,6,0,0,0,0,0},
        {0,7,0,0,9,0,2,0,0},
        {0,5,0,0,0,7,0,0,0},
        {0,0,0,0,4,5,7,0,0},
        {0,0,0,1,0,0,0,3,0},
        {0,0,1,0,0,0,0,6,8},
        {0,0,8,5,0,0,0,1,0},
        {0,9,0,0,0,0,4,0,0}
    };
    timeval t1 ,t2;
    char temp;
    crackBinary::initAll();
    while(cin.good())
    {
        for(int i=0;i<9;++i)
        {
            for(int j=0; j<9; ++j)
            {
                cin>>temp;
                nums[i][j]=temp-'0';
                cout<<temp;
            }
        }
        cout<<"\n";
    gettimeofday(&t1,NULL);
        crackBinary s(nums);
        s.begin();
    gettimeofday(&t2,NULL);
    cerr<<"TIME: "<<1000000*(t2.tv_sec-t1.tv_sec)+t2.tv_usec-t1.tv_usec<<endl;
    }

    return 0;
}

