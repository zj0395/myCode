/*************************************************************************
	> File Name: B72.cpp
	> Author: zj
	> Describe: 荷兰国旗问题，只有 0、1、2 的数组
                进行排序 0最前，2最后
	> Created Time: Tue 16 Oct 2018 09:26:41 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    void Sort( vector<int> & array )
    {
        int b=0, e=array.size()-1; // begin, end
        int idx = 0;
        while( idx <= e )
        {
            switch(array[idx])
            {
            case 0:
                swap( array[b++], array[idx++] );
                break;
            case 1:
                ++idx;
                break;
            case 2:
                swap( array[e--], array[idx--] );
                break;
            default:
                break;
            }
        }
    }
};

int main()
{
    vector<int> array = {0, 1, 2, 1, 2, 0, 0, 0, 1, 2, 2, 1};
    Solution().Sort( array );
    for( int i:array )
        cout<<i<<" ";
    cout<<"\n";
    return 0;
}
