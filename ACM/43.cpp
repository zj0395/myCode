/*************************************************************************
	> File Name: 43.cpp
	> Author: zj
	> Describe: 统计从1到n整数中，数字1出现的次数
	> Created Time: Wed 10 Oct 2018 09:24:30 PM CST
 ************************************************************************/

// https://www.cnblogs.com/xuanxufeng/p/6854105.html

#include <iostream>
using namespace std;

class Solution {
public:
    int NumberOf1Between1AndN_Solution(int n)
    {
        int cnt = 0;
        for( int m=1; m<=n; m*=10 )
        {
            int a=n/m, b=n%m;
            cnt += (a+8)/10*m + ((a%10==1)?(b+1):0 );
        }
        return cnt;
    }
};

int main()
{
    Solution s;
    cout<<s.NumberOf1Between1AndN_Solution(55)<<"\n";
}
