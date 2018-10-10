/*************************************************************************
	> File Name: pape.cpp
	> Author: zj
	> Mail: zhangjian0395@163.com
	> Created Time: Fri 09 Jun 2017 04:53:00 PM CST
 ************************************************************************/

#include<iostream>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<cstring>
using namespace std;
int main()
{
    int fd[2];
    pid_t pid;
    char buf[64]="I'm parent process!\n";
    char line[64];

    if(0!=pipe(fd) )
    {
        cerr<<"Fail to create Pipe\n";
        return 0;
    }

    pid=fork();
    if(pid<0)
    {
        cerr<<"Faik to create Process!\n";
        return 0;
    }
    else if( 0<pid )
    {
        cout<<"Child Process is "<<pid<<"\n";
        close(fd[0]);
        write(fd[1],buf,strlen(buf));
        close(fd[1]);
    }
    else
    {
        cout<<"child run\n";
        close(fd[1]);
        read(fd[0],line,64);
        cout<<"Data from parent: "<<line;
        close(fd[0]);
    }
    return 0;
}

