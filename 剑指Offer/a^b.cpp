/*************************************************************************
	> File Name: a^b.cpp
	> Author: zj
	> Describe: 获取 a^b % n 的结果
	> Created Time: Mon 15 Oct 2018 08:52:50 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;

unsigned Montgomery(unsigned a,unsigned b,unsigned n)
{
    unsigned ans = 1;
    a %= n;
    while (b >= 1)
    {
        if (b & 1)
            ans = (ans * a) % n;

        a = (a * a) % n;
        b >>= 1;
    }

    return ans;

}

int main()
{
    cout<<Montgomery(2, 10000000, 1000)<<"\n";
    return 0;
}
