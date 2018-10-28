/*************************************************************************
	> File Name: 11.cpp
	> Author: zj
	> Describe: 旋转数组的最小数字，二分法改动
	> Created Time: Tue 09 Oct 2018 02:32:32 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        if( rotateArray.size() == 0 )
            return 0;
        int b=0, e=rotateArray.size()-1;
        while( b != e )
        {
            int m = (b+e)/2;
            if( rotateArray[m] <= rotateArray[e] )
                e = m;
            else
                b = m+1;
        }
        return rotateArray[b];
    }
};

int main()
{
    vector<int> a{3, 4, 5, 1, 2};
    Solution f;
    cout<<f.minNumberInRotateArray(a)<<"\n";
}
