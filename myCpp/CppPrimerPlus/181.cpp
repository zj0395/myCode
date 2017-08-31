/*************************************************************************
	> File Name: 181.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年02月24日 星期五 20时06分09秒
 ************************************************************************/

#include<iostream>
#include<algorithm>
template<typename T>
void show2(double x,T fp){std::cout<<x<<" -> "<<fp(x)<<'\n';}
using namespace std;
int main()
{
    show2(18.0,[](double x){return 1.8*x+32;});
    return 0;
}
