/*************************************************************************
	> File Name: p359.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 28 Mar 2017 10:09:10 AM CST
 ************************************************************************/

#include<iostream>
#include<list>
int main()
{
    std::list<int>lst1{1,2,3,4};
    std::list<int>lst3;
    //std::list<int>::iterator pos=lst3.begin();
    copy(lst1.begin(),lst1.end(),inserter(lst3,lst3.end()));
    for(auto& a:lst3)
        std::cout<<a<<" ";
    return 0;
}

