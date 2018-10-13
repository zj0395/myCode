/*************************************************************************
	> File Name: 3.cpp
	> Author: zj
	> Describe: 对数组两个元素求和，并替换掉这两个元素
                求多少次求和后，数组能变成对称数组
                获取多少次求和后，数组为对称数组
                [1,2,1], [3,4,5,4,3]为对称数组
	> Created Time: Sat 13 Oct 2018 07:58:06 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;

class Solution
{
public:
    int getMinTimes(int * array, int len)
    {
        int lenValid = judgeLen(array, len);
        if( lenValid != -1 )
            return lenValid;

        int retVal;
        if( array[0] != array[len-1] )
        {
            int left = addLeft( array, len );
            int right = addRight( array, len );
            retVal = min(left, right);
        }
        else
        {
            retVal = getMinTimes( array+1, len-2 );
        }
        return retVal;
    }
private:
    void printArray(int*array, int len)
    {
        cout<<"Print: ";
        for( int i=0; i<len; ++i )
            cout<<array[i]<<" ";
        cout<<"\n";
    }
    int judgeLen( int* array, int len )
    {
        if( len <= 1 )
            return 0;
        if( len == 2 )
        {
            if( array[0] == array[1] )
                return 0;
            else
                return 1;
        }
        return -1;
    }
    int addLeft( int*array, int len )
    {
        int lenValid = judgeLen(array, len);
        if( lenValid != -1 )
            return lenValid;

        int tmp = array[1];
        array[1] += array[0];
        int retVal = getMinTimes( array+1, len-1 ) + 1;
        array[1] = tmp;
        return retVal;
    }
    int addRight( int*array, int len )
    {
        int lenValid = judgeLen(array, len);
        if( lenValid != -1 )
            return lenValid;

        int tmp = array[len-2];
        array[len-2] += array[len-1];
        int retVal = getMinTimes( array, len-1 ) + 1;
        array[len-2] = tmp;
        return retVal;
    }
};

int main()
{
    int n;
    cin>>n;
    int items[50];
    for( int i=0; i<n; ++i )
        cin>>items[i];
    Solution s;
    cout<<s.getMinTimes(items, n)<<"\n";
}
