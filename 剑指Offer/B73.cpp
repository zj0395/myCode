/*************************************************************************
	> File Name: B73.cpp
	> Author: zj
	> Describe: 判断数字是否是回文数字
                如 1234321、567898765
	> Created Time: Thu 25 Oct 2018 08:00:25 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;

class Solution
{
public:
    bool isPalindrome(int num)
    {
        if( num<0 )
            return false;
        int help = 1;
        while( num / help >= 10 )
            help *= 10;
        while( num != 0 )
        {
            if( num/help != num%10 )
                return false;
            num = num%help/10;
            help /= 100;
        }
        return true;
    }
};

int main()
{
    Solution s;
    cout<<s.isPalindrome(123454321)<<"\n";
    cout<<s.isPalindrome(12345654321)<<"\n";
}
