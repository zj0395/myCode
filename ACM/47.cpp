/*************************************************************************
	> File Name: 47.cpp
	> Author: zj
	> Describe: 挑选礼物的最大价值
                选定一条路径，求最大和
                动态规划，深度优先搜索复制度太高
	> Created Time: Thu 11 Oct 2018 10:58:57 AM CST
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Bonus {
public:
    int getMost(vector<vector<int> > board)
    {
        if( board.empty() || board[0].empty() )
            return 0;
        vector<int> values( board[0].size(), 0 );
        for( vector<int>& v : board )
        {
            values[0] += v[0];
            for( int i=1; i<v.size(); ++i )
                values[i] = max( values[i-1], values[i] ) + v[i];
        }
        return values.back();
    }
};
