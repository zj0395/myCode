/*************************************************************************
	> File Name: 5.cpp
	> Author: zj
	> Describe: 将一个字符串中的某个字符替换为某个字符串
	> Created Time: Tue 09 Oct 2018 09:43:30 AM CST
 ************************************************************************/

#include <cstring>

const char C = ' ';
const char* D = "\%200";

// 遍历两遍
// 第一遍确定替换后的长度
// 第二遍从尾到头，进行替换
char* getResult(const char* src, const int len, char* buff )
{
    if( src == nullptr || len <=0 )
        return nullptr;
    int dstLen = len;
    for( int i=0; i<len; ++i )
    {
        if( src[i] == C )
            dstLen += strlen(D) - 1;
    }
    char* ret;
    if( buff != nullptr )
        ret = buff;
    else
        ret = new char[dstLen+1];
    ret[dstLen] = '\0';
    int idx = dstLen - 1;
    for( int i=len-1; i>=0; --i )
    {
        if( src[i] == C )
        {
            for( int j=strlen(D)-1; j>=0; --j )
                ret[ idx-- ] = D[j];
        }
        else
            ret[ idx-- ] = src[i];
    }
    return ret;
}

#include <iostream>
#include <string>
using namespace std;
int main()
{
    const int len = 5;
    string ss[len] = { "Ni Hao", "Shi De", "Hello World", "G D", "F c" };
    char buff[50];
    for( int i=0; i<len; ++i )
        cout<<getResult( ss[i].c_str(), ss[i].size(), buff )<<"\n";
}
