/*************************************************************************
	> File Name: quicksort.cpp
	> Author: zj
	> Mail: zj0395@163.com
	> Created Time: Tue 23 May 2017 06:00:03 PM CST
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
        while ( i < j&& a[i]<=k )
            ++i;
        swap(a[i],a[j]);
    }
    swap( a[i], a[b] );
    QuickSort(a , b ,i-1);
    QuickSort(a , i+1 , e);
}
void MaxM(int* a , int m,int b, int e)
{
//    cout<<"The M is: "<<m<<endl;
    int k=a[b];
    int i=b,j=e;
    while ( i !=j  )
    {
       while( j > i && a[j]>=k )
            --j;
        while( i<j && a[i]<=k )
            ++i;
        swap(a[i],a[j]);
    }
    swap(a[i], a[b]);
    int right=e-i+1;
    if( m>right  )
        MaxM(a , m-right , 0 , i-1);
    else if( m <right )
        MaxM(a , m ,i+1 ,e);
}
int main()
{
    const int N=50, MOD=100;
    const int m=5;
    default_random_engine e(time(0));
    uniform_int_distribution<unsigned> u(0 , 200000000);
    vector<int>a;
    a.resize(N);
    for( int i=0; i< N ;++i )
    {
        a[i]=u(e)%MOD;
    }

    cout<<"Before:\n";
    for( int f:a )
        cout<<f<<" ";
    cout<<"\n";

    cout << time(0)<<endl;
    MaxM(&a[0],m,0,N-1);
    QuickSort(&a[0] , N-m ,N-1);
    cout << time(0)<<endl;

    for( int i=m ; i>0 ; --i )
        cout<<a[N-1-i]<<" ";
    cout<<endl;
    return 0;
}
