/*************************************************************************
	> File Name: 45.cpp
	> Author: zj
	> Describe: 把数组排成最小的数
                [3, 32, 321] >> 321323
	> Created Time: Thu 11 Oct 2018 10:06:49 AM CST
 ************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution {
public:
    string PrintMinNumber(vector<int> numbers) {
        std::sort( numbers.begin(), numbers.end(),
                [](int a, int b)->bool
                {
                    string a1 = to_string(a)+to_string(b);
                    string b1 = to_string(b)+to_string(a);
                    return a1 < b1;
                });
        string ret;
        for( int n : numbers )
            ret += to_string(n);
        return ret;
    }
};

int main()
{
    vector<int> f = {3, 32, 321};
    string ret = Solution().PrintMinNumber(f);
    cout<<ret<<"\n";
}
