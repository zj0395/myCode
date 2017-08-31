/*************************************************************************
	> File Name: c9_14.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年03月18日 星期六 09时49分29秒
 ************************************************************************/

#include<iostream>
#include<list>
#include<vector>
using namespace std;
int main()
{
    char a[5]="you",b[5]="he",c[5]="her";
    list<char*>ls={a,b,c};
    vector<char*>vec;
    for(char*s:ls)
        vec.push_back(s);
    for(char*s:vec)
        cout<<s<<'\n';
    return 0;
}
