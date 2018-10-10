/*************************************************************************
	> File Name: c9_33.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年03月18日 星期六 16时18分26秒
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;
int main()
{
    vector<int>s{1,2,3,4,5,6,7};
    s.reserve(11);
    s.resize(10);
    vector<int>::iterator beg=s.begin();
//    while(beg!=s.end())
    {
        ++beg;
        s.insert(beg,43);
        ++beg;
        beg=s.insert(beg,55);
    }
    for(int a:s)
        cout<<a<<" ";
    cout<<endl;
    return 0;
}
