/*************************************************************************
	> File Name: 12.cpp
	> Author: zj
	> Describe: 查找字符串矩阵中是否存在某个路径，深度优先搜索
	> Created Time: Tue 09 Oct 2018 02:51:59 PM CST
 ************************************************************************/

#include <iostream>
#include <cstring>
using namespace std;

class Solution {
public:
    bool hasFind(char** matrix, bool** flags, int rows, int cols, char* str, int len, int x, int y)
    {
        const static int offset[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0,1} };
        if( len == strlen(str) )
            return true;
        if( x<0 || y<0 || x==rows || y==cols )
            return false;
        if( flags[x][y] || matrix[x][y] != str[len] )
            return false;
        flags[x][y]=1;
        for( int i=0; i<4; ++i )
        {
            int nx = x+offset[i][0];
            int ny = y+offset[i][1];
            if( hasFind(matrix, flags, rows, cols, str, len+1, nx, ny ) )
                return true;
        }
        flags[x][y]=0;
        return false;
    }

    bool hasPath(char* matrix, int rows, int cols, char* str)
    {
        if( rows==0 || cols==0 )
            return false;
        int len = strlen(str);
        bool ** flags = new bool*[rows];
        char ** mat = new char*[rows];
        for( int i=0; i<rows; ++i )
        {
            flags[i] = new bool[cols];
            memset( flags[i], 0, sizeof(bool)*cols );
            mat[i] = new char[cols];
            for( int j=0; j<cols; ++j )
            {
                mat[i][j] = matrix[ i*cols+j ];
            }
        }

        for( int i=0; i<rows; ++i )
        {
            for( int j=0; j<cols; ++j )
            {
                if( hasFind( mat, flags, rows, cols, str, 0, i, j) )
                    return true;
            }
        }
        return false;
    }
};
