/*************************************************************************
	> File Name: binaryAdd.cpp
	> Author: zj
	> Mail: zhangjian0395@163.com
	> Created Time: Thu 27 Jul 2017 09:21:43 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
inline int orNot( int a, int b )
{
    if(a!=b)
        return 1;
    return 0;
}

int* binaryAdd(int *a, int *b, int n)
{
    int tmp = 0;
    int *result = new int[n+1];
    for( int i=n-1; i>=0; --i )
    {
        cout<<a[i]<< " "<<b[i]<<" ";
        result[i+1] = orNot( orNot(a[i],b[i]), tmp );
        tmp = (a[i]&&b[i]) || ( orNot(a[i],b[i]) && tmp);
        cout<<result[i]<<" "<<tmp<<endl;
    }
    result[0] = tmp;
    return result;
}
int main()
{
    const int num = 9;
    int a[num]={1,0,1,0,0,1,1,1,0};
    int b[num]={1,1,0,1,1,1,1,1,1};
    int* result = binaryAdd(a, b, num);
    for( int i=0; i<num+1; ++i )
        cout<<result[i];
    delete []result;
    cout<<endl;
    return 0;
}
