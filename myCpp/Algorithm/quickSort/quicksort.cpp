/*************************************************************************
	> File Name: quicksort.cpp
	> Author: zj
	> Mail: zj0395@163.com
	> Created Time: Tue 23 May 2017 05:00:03 PM CST
 ************************************************************************/
#include<iostream>
#include <vector>
#include <random>
#include <set>
using namespace std;
inline void swap(int & a ,int & b )
{
    int tmp=a;
    a=b;
    b=tmp;
}
void QuickSort(int*a , int b ,int e)
{
    if( b >= e )
        return;
    int k=a[b];
    int i=b,j=e;
    while ( i != j )
    {
        while( j > i && a[j]>=k )
            --j;
        swap( a[i],a[j] );
        while ( i < j&& a[i]<=k )
            ++i;
        swap(a[i],a[j]);
    }
    QuickSort(a , b ,i-1);
    QuickSort(a , i+1 , e);
}
int main()
{
    const int N=8;
    default_random_engine e(time(0));
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
    QuickSort(&a[0], 0 ,N-1);
    cout << time(0)<<endl;
    cout<<"Sort Ok!"<<endl;

    uniform_int_distribution<unsigned> u(0,N);
    set<int> si;
    for( int i=0 ; i < 8 ; ++i )
    {
        si.insert(  i);
    }
    set<int>::iterator it;
    for( it=si.begin() ; it!=si.end() ; ++it )
        cout<<a[*it]<<" ";
    cout<<endl;
    return 0;
}
