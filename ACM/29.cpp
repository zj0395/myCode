/*************************************************************************
	> File Name: 29.cpp
	> Author: zj
	> Describe: 从左上角开始顺时针打印矩阵
	> Created Time: Wed 10 Oct 2018 10:03:45 AM CST
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> printMatrix(vector<vector<int> > matrix) {
        vector<int> ret;
        if( matrix.empty() || matrix[0].empty() )
            return ret;

        int r1=0, c1=0, r2=matrix.size()-1, c2=matrix[0].size()-1;
        while( r1<=r2 && c1<=c2 )
        {
            for( int i=c1; i<=c2; ++i )
                ret.push_back(matrix[r1][i]);
            for( int i=r1+1; i<=r2; ++i )
                ret.push_back(matrix[i][c2]);
            if( r1 != r2 )
                for( int i=c2-1; i>=c1; --i )
                    ret.push_back(matrix[r2][i]);
            if( c1 != c2 )
                for( int i=r2-1; i>r1; --i )
                    ret.push_back(matrix[i][c1]);
            ++r1, --r2, ++c1, --c2;
        }
        return ret;
    }
};
