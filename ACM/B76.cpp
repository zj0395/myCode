/*************************************************************************
	> File Name: B76.cpp
	> Author: zj
	> Describe: 查看自身的路线是否相交
                比较复杂的边界检查
                https://leetcode.com/problems/self-crossing/description/
	> Created Time: Tue 30 Oct 2018 09:30:54 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    bool isSelfCrossing(vector<int>& array)
    {
        int len = array.size();
        if( (len > 3 && array[2]<=array[0] && array[3]>=array[1]) ||
            (len > 4 && array[3]==array[1] && array[4]+array[2]>=array[0])
          )
            return true;
        for( int i=5; i<array.size(); ++i )
        {
            if( array[i-1]<=array[i-3] &&
                    (
                        (array[i]>=array[i-2]) ||
                        (array[i-4]<=array[i-2]
                            && array[i]+array[i-4]>=array[i-2]
                            && array[i-5]+array[i-1]>=array[i-3]
                        )
                    )
              )
            {
                return true;
            }
        }
        return false;
    }
};

int main()
{
    vector<int> t1 {2,1,1,2}; // true
    vector<int> t2 {3,3,3,2,1,1}; // false
    cout<<Solution().isSelfCrossing(t1)<<"\n";
    cout<<Solution().isSelfCrossing(t2)<<"\n";
}
