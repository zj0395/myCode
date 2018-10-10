/*************************************************************************
	> File Name: 41-1.cpp
	> Author: zj
	> Describe: 数据流中的中位数
                使用两个优先队列
	> Created Time: Wed 10 Oct 2018 04:59:42 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    void Insert(int num)
    {
        if( idx++ % 2 == 0 ) // insert to right
        {
            left.push(num);
            right.push(left.top());
            left.pop();
        }
        else // insert to left
        {
            right.push(num);
            left.push(right.top());
            right.pop();
        }
    }

    double GetMedian()
    {
        if( idx %2 == 1  )
            return right.top();
        else
            return (left.top() + right.top())/2.0;
    }
private:
    // left < right
    priority_queue< int, vector<int>, greater<int> >left;
    priority_queue< int, vector<int>, less<int> >right;
    int idx;
};

int main()
{
    Solution s;
    vector<int> a {5,2,3,4,1,6,7,0,8};
    for( int f:a )
    {
        s.Insert(f);
        cout<<s.GetMedian()<<" ";
    }
}
