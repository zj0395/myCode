/*************************************************************************
	> File Name: 2.cpp
	> Author: zj
	> Describe: 找到数组中重复数字，复杂度O(N)+O(1)
	> Created Time: Tue 09 Oct 2018 08:59:36 AM CST
 ************************************************************************/

#include <iostream>
using namespace std;

// 要求数字范围在 0到n-1 的范围内
// 将数字为 i 的元素移动到第 i 个位置上
// 找到的数字并不一定是第一个重复出现的数字
bool getRepeat(int* array, int len, int& ret)
{
    if( array == nullptr || len <=0 )
        return false;
    for( int i=0; i<len; ++i )
    {
        while( i != array[i] )
        {
            if( array[ array[i] ] == array[i] )
            {
                ret = array[i];
                return true;
            }
            swap( array[i], array[ array[i] ] );
        }
    }
    return false;
}

int main()
{
    const int len = 5;
    int testNum[5] = {1,3,3,2,0};
    int ret = 0;
    if( getRepeat(testNum, len, ret ) )
    {
        cout<<"Repeat: "<<ret<<"\n";
    }
    else
    {
        cout<<"No Repeat Number.\n";
    }
}

