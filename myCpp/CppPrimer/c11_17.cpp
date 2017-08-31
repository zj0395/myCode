/*************************************************************************
	> File Name: c11_17.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 28 Mar 2017 10:24:07 AM CST
 ************************************************************************/

#include<iostream>
#include<vector>
#include<set>
int main()
{
    std::multiset<std::string>c{"fuck","no","thanks","oh"};
    for(std::string a:c)
        std::cout<<a<<" ";
    std::cout<<std::endl;
    std::vector<std::string>v{"shit"};
    copy(v.begin(),v.end(),inserter(c,c.end()));
    for(std::string a:c)
        std::cout<<a<<" ";
    std::cout<<std::endl;
    //copy(v.begin(),v.end(),back_inserter(c));
    copy(c.begin(),c.end(),inserter(v,v.end()));
    copy(c.begin(),c.end(),back_inserter(v));
    for(std::string a:v)
        std::cout<<a<<" ";
    std::cout<<std::endl;
    for(std::string a:c)
        std::cout<<a<<" ";
    std::cout<<std::endl;
    return 0;
}
