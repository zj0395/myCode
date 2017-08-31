#include<ctime>
#include<stdio.h>
#include<unistd.h>
int main()
{
    time_t times,time2;
    time2 = time(&times);
    printf("%12d,%12d",times,time2);
    sleep(2);
    printf("%12d",time(0));
    printf("%12.2f\n",difftime(time(0),times));
    return 0;
}
