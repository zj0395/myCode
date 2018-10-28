/*************************************************************************
	> File Name: 21.cpp
	> Author: zj
	> Describe: 调整数组，使奇数位于偶数前面，且不改变原来的相对位置
	> Created Time: Tue 09 Oct 2018 11:23:42 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void reOrderArray(vector<int> &array) {
        int len = array.size();
        int oldCount = 0;
        for( int i=0; i<len; ++i )
            if( array[i] % 2 )
                ++oldCount;

        int i=0, j=oldCount;
        vector<int> tmp = array;
        for( int a=0; a<len; ++a )
            if( tmp[a]%2 )
                array[i++] = tmp[a];
            else
                array[j++] = tmp[a];
    }
};
