/*************************************************************************
	> File Name: c9_26.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年03月18日 星期六 10时01分15秒
 ************************************************************************/

#include<iostream>
#include<forward_list>
int main()
{
    int ia[]={0,1,1,2,3,5,8,13,21,55,89};
    std::forward_list<int>fls(ia,ia+11);
    std::forward_list<int>::iterator prev=fls.before_begin();
    std::forward_list<int>::iterator curr=fls.begin();
    while(curr!=fls.end())
    {
        if(*curr%2)
            curr=fls.erase_after(prev);
        else{
            prev=curr++;
        }
    }
    for(int a:fls)
        std::cout<<a<<" ";
    return 0;
}
