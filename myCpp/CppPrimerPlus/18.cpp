/*************************************************************************
	> File Name: 18.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年02月24日 星期五 19时39分33秒
 ************************************************************************/

#include<iostream>
#include<array>
#include<algorithm>
const int Size=5;
using namespace std;
template<typename T>
void sum(array<double,Size>a,T&& fp);
int main()
{
    double total=0.0;
    array<double,Size> temp_c={32.1,34.3,37.8,35.2,34.7};
    sum(temp_c, [&total](double w){total += w;} );
    cout<<"total: "<<total<<'\n';
    return 0;
}
template<typename T>
void sum(array<double,Size>a,T&&fp)
{
    for_each(a.begin(),a.end(),fp);
}
