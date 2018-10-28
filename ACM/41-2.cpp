/*************************************************************************
	> File Name: 41-2.cpp
	> Author: zj
	> Describe: 字符流中第一个不重复的字符
	> Created Time: Wed 10 Oct 2018 09:11:45 PM CST
 ************************************************************************/

#include <iostream>
#include <queue>
using namespace std;

class Solution
{
public:
  //Insert one char from stringstream
    void Insert(char ch)
    {
        ++cnt[ ch ];
        cout<<ch<<" "<<cnt[ch]<<"\n";
        contianer.push( ch );
        while( ! contianer.empty() && cnt[contianer.front()] > 1 )
            contianer.pop();
    }
  //return the first appearence once char in current stringstream
    char FirstAppearingOnce()
    {
        return contianer.empty() ? '#' : contianer.front();
    }
private:
    int cnt[256];
    queue<char> contianer;
};

int main()
{
    Solution s;
    s.Insert('g');
    s.Insert('g');
    s.Insert('g');
    cout<<s.FirstAppearingOnce()<<"\n";
}
