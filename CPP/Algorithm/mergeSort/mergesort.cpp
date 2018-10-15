/*************************************************************************
	> File Name: mergesort.cpp
	> Author: zj
	> Mail: zj0395@163.com
	> Created Time: Tue 23 May 2017 03:29:59 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
#include <random>
#include <set>
using namespace std;
void Merge(int*sou ,int *tmp ,int b ,int e1 ,int e)
{
    int b1=b, b2=e1+1;
    for( int i=b; i<=e; ++i )
        tmp[i] = sou[i];
    for( int i=b; i<=e; ++i )
    {
        if( b1 > e1 )
            sou[i] = tmp[b2++];
        else if( b2 > e )
            sou[i] = tmp[b1++];
        else if( tmp[b1] <= tmp[b2] )
            sou[i] = tmp[b1++];
        else
            sou[i] = tmp[b2++];
    }
}
void MergeSort(int* sou , int *tmp , int b , int e)
{
    if( b < e )
    {
        int e1 = b + (e-b)/2;
        MergeSort(sou, tmp, b, e1);
        MergeSort(sou, tmp, e1+1, e);
        Merge(sou, tmp, b, e1, e);
    }
}
int main()
{
    const int N=50, MOD=100;
    default_random_engine e;
    vector<int>a;
    a.resize(N);
    for( int i=0; i< N ;++i )
    {
        a[i]=e()%MOD;
    }
    vector<int>r;
    r.resize(N);
    MergeSort(&a[0],&r[0] , 0 ,N-1);

    int last = a[0];
    bool flag = true;
    for( int i=1; i<N; ++i )
    {
        if( a[i] < last )
            flag = false;
        last = a[i];
    }
    cout<<(flag ? "Ok\n":"Fail\n");
    return 0;
}
