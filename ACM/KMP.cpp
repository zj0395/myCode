/*************************************************************************
	> File Name: KMP.cpp
	> Author: zj
	> Describe: KMP算法
                O(m+n) 查找是否存在子串
                https://www.cnblogs.com/yjiyjige/p/3263858.html
	> Created Time: Wed 31 Oct 2018 04:16:20 PM CST
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    int getFirstEqualIdx( const string & src, const string& dst  )
    {
        vector<int> next = getNext(dst);
        int j = 0;
        for( int i=0; i<src.size(); ++i )
        {
            if( src[i] != dst[j] )
            {
                if( next[j] != -1 )
                    j = next[j];
            }
            else
            {
                ++j;
                if( j == dst.size() )
                    return i-j+1;
            }
        }
        return -1;
    }
private:
    // 核心算法
    vector<int> getNext(const string& str)
    {
        int len = str.size();
        vector<int> next( len, 0 );
        int k = -1;
        next[0] = -1;
        int j = 0;
        while( j<len-1 )
        {
            if( k == -1 || str[j] == str[k] )
            {
                ++j;
                ++k;
                // 已经和该值比较过了
                // 没必要再跳过来和同样的值比较一次
                // 直接跳到更前面
                if( str[j] == str[k] )
                    next[j] = next[k];
                else
                    next[j] = k;
            }
            else
                k = next[k];
        }
        return next;
    }
};

int main()
{
    string src = "abcdabcefghi";
    string dst = "abce";
    cout<<Solution().getFirstEqualIdx(src, dst)<<"\n";
}
