/*************************************************************************
	> File Name: maxSubArray.cpp
	> Author: zj
	> Mail: zhangjian0395@163.com
	> Created Time: Thu 27 Jul 2017 09:45:42 PM CST
 ************************************************************************/

inline int ABS( int a )
{
    return a<0?-a:a;
}
/*
 * Return : a array of 3, being, end, and number
 */
int *maxSubArray( int* array, int length)
{
    int boundry = array[0];
    int maxArray = array[0];
    int maxEndIndex = 0;
    int maxBeginIndex = 0;
    int tmpBeginIndex = 0;
    for( int i=1; i<length; ++i )
    {
        if( boundry+array[i] >= array[i] )
        {
            boundry += array[i];
        }
        else
        {
            boundry = array[i];
            tmpBeginIndex = i;
        }
        if( maxArray < boundry )
        {
            maxArray = boundry;
            maxEndIndex = i;
            maxBeginIndex = tmpBeginIndex;
        }
    }
    int *result = new int[3];
    result[0] = maxBeginIndex;
    result[1] = maxEndIndex;
    result[2] = maxArray;
    return result;
}

#include<iostream>
using namespace std;
int main()
{
    int a[] = {1,-2,3,10,-4,7,2,-48};
    int num = sizeof(a)/sizeof(a[0]);
    int* result = maxSubArray(a, num);
    cout<<"Begin:"<<result[0]<<"  End:"<<result[1]<<"  Num:"<<result[2]<<endl;
    int b[] = {3,-1,5,-1,9,-20,21,-20,20,21};
    num = sizeof(b)/sizeof(b[0]);
    result = maxSubArray(b, num);
    cout<<"Begin:"<<result[0]<<"  End:"<<result[1]<<"  Num:"<<result[2]<<endl;
    return 0;
}
