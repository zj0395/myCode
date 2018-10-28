/*************************************************************************
	> File Name: 38.cpp
	> Author: zj
	> Describe: 字符串的排列
	> Created Time: Wed 10 Oct 2018 03:42:53 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> Permutation(string str) {
        ret.clear();
        std::sort( str.begin(), str.end() );

        vector<bool> marker(str.size(), 0);
        string s;

        dfs( str, marker, s );
        return ret;
    }
    void dfs( string & str, vector<bool>& marker, string & s )
    {
        if( s.size() == str.size() )
        {
            if( ! s.empty() )
                ret.push_back(s);
            return;
        }
        for( int i=0; i<str.size(); ++i )
        {
            if( marker[i] )
                continue;
            if( i!=0 && str[i] == str[i-1] && !marker[i-1] )
                continue;
            marker[i] = true;
            s.push_back( str[i] );
            dfs( str, marker, s );
            s.resize( s.size()-1 );
            marker[i] = false;
        }
    }
private:
    vector<string> ret;
};

int main()
{
    string s = "ab";
    vector<string> f = Solution().Permutation(s);
    cout<<f[0]<<" "<<f[1]<<"\n";
}
