/*************************************************************************
	> File Name: B77.cpp
	> Author: zj
	> Describe: 两个字符串相加是否是回文串
                找出所有的回文对
                1. 字符串逆序，找是否存在
                2. 字符串前面的回文去掉，找是否存在剩下的回文
                3. 字符串后面的回文去掉，是否存在剩下的回文
                使用 Manacher 算法找回文对
                https://leetcode.com/problems/palindrome-pairs/
	> Created Time: Wed 31 Oct 2018 03:16:56 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words)
    {
        vector<vector<int>> ret;
        unordered_map<string, int> hashs;
        for( int i=0; i<words.size(); ++i )
            hashs[ words[i] ] = i;
        for( int i=0; i<words.size(); ++i )
        {
            string & str = words[i];
            string reverse( str.rbegin(), str.rend() );
            unordered_map<string, int>::iterator iter;
            if( str.size()!=1 && (iter=hashs.find(reverse)) != hashs.end() )
                ret.push_back( vector<int>{i, iter->second} );

            char first = reverse[0];
            while( reverse[0] == first )
            {
                reverse = string(reverse.begin()+1, reverse.end());
                if( (iter=hashs.find(reverse)) != hashs.end() )
                    ret.push_back( vector<int>{i, iter->second} );
            }
        }
        return ret;
    }
};


