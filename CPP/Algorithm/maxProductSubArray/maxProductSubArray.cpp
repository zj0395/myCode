/*************************************************************************
	> File Name: maxSubArray.cpp
	> Author: zj
	> Mail: zhangjian0395@163.com
	> Created Time: Thu 27 Jul 2017 09:45:42 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
inline int MAX( int a, int b )
{
    return a>b ? a:b;
}
int getMax(int* array, int index, int length)
{
    int left = array[0];
    for( int i=1; i<index; ++i )
    {
        left *= array[i];
    }
    if( index >= length-1 )
        return left;
    int right = array[index+1];
    for( int i=index+2; i<length; ++i)
    {
        right *= array[i];
    }
    return left>right ? left:right;
}
/*
 * Return : a array of 3, being, end, and number
 */
int maxSubArray( int* array, int length)
{
    int* indexS = new int[length];
    int numbers = 0;
    for( int i=0; i<length; ++i )
    {
        if( array[i] < 0 )
        {
            indexS[numbers++] = i;
        }
    }
    int result;
    if( numbers%2 )
    {
        result = getMax( array, indexS[0], length );
        for( int i=1; i<numbers; ++i )
        {
            cout<<"index: "<<indexS[i]<<endl;
            result = MAX( result, getMax(array, indexS[i], length) );
        }
    }
    else
    {
        result = getMax( array, length, length );
    }
    return result;
}

int main()
{
    const int num = 6;
    int a[num] = {3,-1,-2,-3,-3,4};
    int result = maxSubArray(a, num);
    cout<<result<<endl;
    return 0;
}
