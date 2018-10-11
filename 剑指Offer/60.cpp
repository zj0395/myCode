/*************************************************************************
	> File Name: 60.cpp
	> Author: zj
	> Describe: 求n个骰子的点数和为S的概率，本文件只设计解法1
                解法1：动态规划，空间复杂度O(N*2)
                解法2：动态规划+旋转数组，空间复杂度O(N)
	> Created Time: Thu 11 Oct 2018 07:38:26 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    /**
     * @param n an integer
     * @return a list of pair<sum, probability>
     */
    vector<pair<int, double>> dicesSum(int n) {
        // Write your code here
        int place = 6;
        vector< vector<long long> > dp( n+1, vector<long long>(6*n+1, 0) ); // times
        for( int i=1; i<=6; ++i )
            dp[1][i] = 1;
        for( int i=2; i<=n; ++i )
            for( int j=i; j<=6*n+1; ++j )
                for( int k=1; k<=6&&k<=j; ++k )
                    dp[i][j] += dp[i-1][j-k];

        double count = pow(6, n);

        vector<pair<int, double>> ret;
        for( int i=n; i<6*n+1; ++i )
        {
            ret.push_back( make_pair(i, dp[n][i]/count) );
        }
        return ret;
    }
};

int main()
{
    for( pair<int, double> t: Solution().dicesSum(15) )
        cout<<t.first<<" "<<t.second<<"\n";
}
