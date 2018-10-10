/*************************************************************************
	> File Name: file.cpp
	> Author: zj
	> Mail: zhangjian0395@163.com
	> Created Time: Sun 11 Jun 2017 10:08:25 PM CST
 ************************************************************************/

#include<iostream>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<cstdio>
#include<cstdlib>
using namespace std;
int main()
{
    creat("s.txt",0777);
    return 0;
}

