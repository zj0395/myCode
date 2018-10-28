/*************************************************************************
	> File Name: 4.cpp
	> Author: zj
	> Describe: 二维有序数组中查找，复杂度 O(M+N)+O(1)
	> Created Time: Tue 09 Oct 2018 09:23:29 AM CST
 ************************************************************************/

// 要求每一行从左到右递增，每一列从上到下递增
// 从右上角开始找，左边的都小于，下边的都大于
int isContain(int** array, int rows, int cols, int dest)
{
    int r = rows-1, c = 0;
    while( r>=0 && c<cols )
    {
        if( dest == array[r][c] )
            return true;
        if( dest < array[r][c] )
            --r;
        if( dest > array[r][c] )
            ++c;
    }
    return false;
}

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> VInt;
typedef vector<VInt> VVInt;

int main()
{
    const int rows = 4;
    const int cols = 5;
    int * nums[rows];
    VVInt numsTmp{
        {1, 4, 7, 11, 15},
        {2, 5, 8, 12, 19},
        {3, 6, 9, 16, 22},
        {10, 13, 14, 17, 24}
    };
    for( int i=0; i<rows; ++i )
    {
        nums[i] = new int[cols];
        for( int j=0; j<cols; ++j )
            nums[i][j] = numsTmp[i][j];
    }

    VInt testNum{ 15, 17, 18, 12, 11, 3, 4 };
    for_each( testNum.begin(), testNum.end(),
            [&](int n)
            {
                cout<<isContain( nums, rows, cols, n )<<"\n";
            }
    );
}
