/*************************************************************************
	> File Name: ls.c
	> Author: zj
	> Describe: ls 命令的简单实现
	> Created Time: Fri 09 Nov 2018 02:58:39 PM CST
 ************************************************************************/

#include <stdio.h>
#include <dirent.h>

int main(int argc, char* argv[])
{
    DIR             *dp;
    struct dirent   *dirp;

    if( argc != 2 )
    {
        printf("%s\n", "usage: ls directory_name");
        return 1;
    }

    if( (dp = opendir(argv[1])) == NULL )
    {
        printf("can't open %s\n", argv[1]);
        return 1;
    }

    while( (dirp = readdir(dp)) != NULL )
        printf("%s\n", dirp->d_name);

    closedir(dp);
    return 0;
}
