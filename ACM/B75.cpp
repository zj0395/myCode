/*************************************************************************
	> File Name: B75.cpp
	> Author: zj
	> Describe: 找出矩阵中的最长递增路径
                动态规划，记录子状态
                https://leetcode.com/problems/longest-increasing-path-in-a-matrix/description/
	> Created Time: Tue 30 Oct 2018 08:27:19 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

const int dr[] = {0, 0, 1, -1};
const int dc[] = {1, -1, 0, 0};

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& array)
    {
        if( array.empty() || array[0].empty() )
            return 0;
        int rows = array.size();
        int cols = array[0].size();
        vector< vector<int> > dp( rows, vector<int>(cols, 0) );
        int ret = 0;
        for( int r=0; r<rows; ++r )
        {
            for( int c=0; c<cols; ++c )
                ret = max( ret, process( array, dp, r, c ) );
        }
        return ret;
    }
private:
    int process( vector<vector<int>>& array, vector< vector<int> > & dp, int row, int col )
    {
        if( dp[row][col] )
            return dp[row][col];
        int ret = 1;
        int rows = array.size();
        int cols = array[0].size();
        for( int i=0; i<4; ++i )
        {
            int nr = row+dr[i];
            int nc = col+dc[i];
            if( nr>=0 && nr<rows && nc>=0 && nc<cols && array[nr][nc] > array[row][col] )
                ret = max( ret, 1+process(array, dp, nr, nc));
        }
        dp[row][col] = ret;
        return ret;
    }
};
int main()
{
    vector<vector<int>> test{
        {9,9,4},
        {6,6,8},
        {2,1,1}
    };
    vector<vector<int>>  test2{
        {3,4,5},
        {3,2,6},
        {2,2,1}
    };
    cout<<Solution().longestIncreasingPath(test)<<"\n";
    cout<<Solution().longestIncreasingPath(test2)<<"\n";
}
