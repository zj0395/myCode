/*************************************************************************
	> File Name: 2.cpp
	> Author: zj
	> Describe: 获取10*10矩阵中最大联通的坐标点个数
	> Created Time: Sat 13 Oct 2018 07:35:53 PM CST
 ************************************************************************/

#include <iostream>
#include <cstring>
using namespace std;

class Solution
{
public:
    int getMaxArea( int * array[] )
    {
        int ** marker = new int* [10];
        for( int i=0; i<10; ++i )
        {
            marker[i] = new int[10];
            memset(marker[i], 0, sizeof(int)*10);
        }
        int areaIdx = 1;
        for( int i=0; i<10; ++i )
        {
            marker[i][0] = array[i][0]==1 ? areaIdx++ : 0;
            for( int j=1; j<10; ++j )
                if( array[i][j] )
                {
                    if ( array[i][j-1] )
                    {
                        marker[i][j] = marker[i][j-1];
                    }
                    else
                    {
                        marker[i][j] = areaIdx++;
                    }
                }
        }

        for( int i=1; i<10; ++i )
        {
            for( int j=0; j<10; ++j )
            {
                if( array[i][j] && array[i-1][j] )
                    moveValue(marker, marker[i][j], marker[i-1][j] );
            }
        }

        // compress
        int areaCount[102] = {0};
        for( int i=0; i<10; ++i )
            for( int j=0; j<10; ++j )
                if( marker[i][j] )
                    areaCount[ marker[i][j] ]++;

        int count = 0;
        for( int i=0; i<102; ++i )
            count = max(count, areaCount[i]);
        return count;

    }
    void moveValue(int** marker, int src, int dst)
    {
        for( int i=0; i<10; ++i )
            for( int j=0; j<10; ++j )
                if( marker[i][j] == src )
                    marker[i][j] = dst;
    }
};

int main()
{
    int ** marker = new int* [10];
    for( int i=0; i<10; ++i )
    {
        marker[i] = new int[10];
        memset(marker[i], 0, sizeof(int)*10);
        for( int j=0; j<10; ++j )
            cin>>marker[i][j];
    }
    cout<<Solution().getMaxArea(marker)<<"\n";
}

