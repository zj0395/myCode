/*************************************************************************
	> File Name: B74.cpp
	> Author: zj
	> Describe: beginword 转换到 endword
                题目: https://leetcode.com/problems/word-ladder
                每个获取单词获取邻居需要 26*len 的时间
                广度优先搜索用队列
                深度优先搜索用栈
	> Created Time: Thu 25 Oct 2018 09:18:34 PM CST
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList)
    {
        multimap<string, string> maps;
        wordList.push_back( beginWord );
        set<string> sets( wordList.begin(), wordList.end() );
        map<string, int> lengthMap;

        // build map
        for( string& str : wordList )
        {
            for( int i=0; i<str.size(); ++i )
            {
                string tmp = str;
                for( int t='a'; t<='z'; ++t )
                {
                    if( t != str[i]  )
                    {
                        tmp[i] = t;
                        if( sets.find(tmp) != sets.end() )
                            maps.insert( make_pair(str, tmp) );
                    }
                }
            }
        }

        // breadth first set legnth
        map<string, bool> isVisited;
        lengthMap[ beginWord ] = 1;
        queue<string> queues;
        queues.push( beginWord );
        while( ! queues.empty() )
        {
            string str = queues.front();
            queues.pop();
            typedef multimap<string, string>::iterator Iter;
            Iter b = maps.lower_bound(str);
            Iter e = maps.upper_bound(str);
            for( ; b!=e; ++b )
            {
                string & neighbor = b->second;
                if( ! isVisited[neighbor] )
                {
                    lengthMap[neighbor] = lengthMap[str] + 1;
                    cout<<neighbor<<" "<<lengthMap[neighbor]<<"\n";
                    isVisited[neighbor] = true;
                    queues.push(neighbor);
                }
            }
        }

        return lengthMap[endWord];
    }
};
