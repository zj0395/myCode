/*************************************************************************
	> File Name: 39.cpp
	> Author: zj
	> Describe: 统计数字中出现次数超过一半的数字
                原理：超过一半，则必定有两个是相邻的
	> Created Time: Wed 10 Oct 2018 04:06:22 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        if( numbers.empty() )
            return 0;
        int majority = numbers[0];
        int cnt = 1;
        for( int i=1; i<numbers.size(); ++i )
        {
            cnt = majority == numbers[i] ? cnt+1 : cnt-1;
            if( cnt == 0 )
            {
                majority = numbers[i];
                cnt = 1;
            }
        }
        cnt = 0;
        for (int val : numbers)
            if (val == majority)
                cnt++;
        return cnt > numbers.size() / 2 ? majority : 0;
    }
};

int main()
{
    vector<int> f{1,2,3,2,4,2,5,2,3};
    cout<<Solution().MoreThanHalfNum_Solution(f)<<"\n";
}
