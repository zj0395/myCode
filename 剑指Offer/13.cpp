/*************************************************************************
	> File Name: 13.cpp
	> Author: zj
	> Describe: 机器人的运行范围，限制了某些格子，深度优先搜索
	> Created Time: Tue 09 Oct 2018 03:25:12 PM CST
 ************************************************************************/

#include <iostream>
#include <cstring>
using namespace std;

class Solution {
public:
    bool isValid(int x, int y, int threshold)
    {
        int count = 0;
        while( x )
        {
            count += x%10;
            x/=10;
        }
        while( y )
        {
            count += y%10;
            y/=10;
        }
        if( count > threshold )
            return false;
        return true;
    }
    void dfs(int** marker, int threshold, int x, int y, int rows, int cols, int&count)
    {
        if( x<0 || y<0 || x==rows || y==cols )
            return;
        if( marker[x][y] == 1 ) // already count
            return;
        if( marker[x][y] == 0 ) // first arrive this
        {
            if( isValid(x, y, threshold) )
            {
                marker[x][y] = 1;
                ++count;
            }
            else
                marker[x][y] = -1;
        }
        if( marker[x][y] == -1 )
        {
            return;
        }
        const static int offset[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0,1} };
        for( int i=0; i<4; ++i )
        {
            dfs( marker, threshold, x+offset[i][0], y+offset[i][1], rows, cols, count );
        }
    }
    int movingCount(int threshold, int rows, int cols)
    {
        // marker, 0:unknown, 1:valid, -1:invalid
        int ** marker = new int* [rows];
        for( int i=0; i<rows; ++i )
        {
            marker[i] = new int[cols];
            memset( marker[i], 0, sizeof(int)*cols );
        }
        int count = 0;
        dfs( marker, threshold, 0, 0, rows, cols, count );
        return count;
    }
};
