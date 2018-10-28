/*************************************************************************
	> File Name: 51.cpp
	> Author: zj
	> Describe: 数组中逆序对，改编归并排序
                获取逆序对的个数，前一个数字大于后一个数字，则组成一个逆序对
                保证不存在重复
	> Created Time: Thu 11 Oct 2018 03:15:36 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int InversePairs(vector<int> data) {
        cnt = 0;
        tmp.resize( data.size() );
        MergeSort( data, 0, data.size()-1 );
        return cnt;
    }
private:
    void MergeSort(vector<int>& data, int b, int e)
    {
        if( e - b < 1 )
            return;
        int m = b + (e-b) / 2;
        MergeSort( data, b, m );
        MergeSort( data, m+1, e );
        Merge( data, b, m, e );
    }
    void Merge(vector<int>&data, int b, int m, int e)
    {
        int i=b, j=m+1, k=b;
        while( i<=m || j<=e )
        {
            if( i>m )
                tmp[k] = data[j++];
            else if( j>e )
                tmp[k] = data[i++];
            else if( data[i] < data[j] )
                tmp[k] = data[i++];
            else
            {
                tmp[k] = data[j++];
                cnt += m-i+1;
                cnt %= 1000000007;
            }
            ++k;
        }
        for( k=b; k<=e; ++k  )
            data[k] = tmp[k];
    }
    vector<int> tmp;
    int cnt;
};
