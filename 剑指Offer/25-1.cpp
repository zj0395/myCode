/*************************************************************************
	> File Name: 25-1.cpp
	> Author: zj
	> Describe: 合并两个排序后的数组，数组中有重复数字
	> Created Time: Tue 16 Oct 2018 09:04:30 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> VInt;

class Solution
{
public:
    VInt mergeArray( VInt a, VInt b )
    {
        int l=0, r=0, k=0; // left, right, result
        VInt ret;
        while( l<a.size() && r<b.size() )
        {
            if( ! ret.empty() )
            {
                if( a[l] == ret.back() )
                {
                    ++l;
                    continue;
                }
                if( b[r] == ret.back() )
                {
                    ++r;
                    continue;
                }
            }
            ret.push_back( a[l]<b[r] ? a[l++] : b[r++] );
        }
        return ret;
    }
};

int main()
{
    VInt a = {1, 1, 4, 5, 5, 7, 9, 10};
    VInt b = {1, 2, 3, 4, 5, 10, 10, 10, 10};
    for( int f : Solution().mergeArray(a, b) )
        cout<<f<<" ";
    cout<<"\n";
}
