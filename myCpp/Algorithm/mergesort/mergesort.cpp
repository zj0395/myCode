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
    int pb=b;
    int b1=b , b2=e1;
    while( b1<e1 && b2<e)
    {
        tmp[pb++] = sou[b1] > sou[b2] ? sou[b1++] : sou[b2++];
    }
    while( b1 < e1 )
        tmp[pb++] = sou[b1++];
    while( b2 < e )
        tmp[pb++] = sou[b2++];
    for(  ; b<e ; ++b )
        sou[b] = tmp[b];
}
void MergeSort(int* sou , int *tmp , int b , int e)
{
    if( b < e-1 )
    {
        int e1 = b + (e-b)/2;
        MergeSort(sou ,tmp , b ,e1);
        MergeSort(sou ,tmp , e1 ,e);
        Merge(sou , tmp , b , e1 ,e);
    }
}
int main()
{
    const int N=100000000;
    default_random_engine e;
    vector<int>a;
    a.resize(N);
    for( int i=0; i< N ;++i )
    {
        a[i]=e();
    }
    vector<int>r;
    r.resize(N);
    cout<<"begin sort"<<endl;
    cout << time(0)<<endl;
    MergeSort(&a[0],&r[0] , 0 ,N);
    cout << time(0)<<endl;
    cout<<"Sort Ok!"<<endl;

    uniform_int_distribution<unsigned> u(0,N);
    set<int> si;
    for( int i=0 ; i < 100 ; ++i )
    {
        si.insert(  u(e) );
    }
    set<int>::iterator it;
    for( it=si.begin() ; it!=si.end() ; ++it )
        cout<<a[*it]<<" ";
    cout<<endl;
    return 0;
}
