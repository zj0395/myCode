#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t mutex;
pthread_cond_t cond;
int change_flag = 0;
void* child1(void*arg)
{
while (1)
{
    pthread_mutex_lock(&mutex);
printf("thread 1 lock it\n");
    while(change_flag != 1)
    {
    printf("thread 1 waitting\n");
    pthread_cond_wait (&cond, &mutex);
    }
    printf("thread 1 Go\n");
    pthread_mutex_unlock(&mutex);
    sleep(1);
}
}

void* child2(void*arg)
{
    while (1)
    {
    pthread_mutex_lock(&mutex);
printf("thread 2 lock it\n");
    while(change_flag != 2)
    {
     printf("thread 2 waitting\n");
    pthread_cond_wait (&cond, &mutex);
    }
    printf("thread 2 Go\n");
    pthread_mutex_unlock(&mutex);
    sleep(1);
    }
}


int main()
{
pthread_t tid1,tid2;
pthread_mutex_init(&mutex, NULL);
pthread_cond_init(&cond,NULL);

pthread_create(&tid1,NULL,  child1 ,NULL);
pthread_create(&tid2,NULL, child2, NULL);

do
{
pthread_mutex_lock(&mutex);
printf("main lock it\n");
if(change_flag == 2)
change_flag = 0;
else 
change_flag++;

printf("change_flag = %d.\n", change_flag);
pthread_mutex_unlock(&mutex);
pthread_cond_signal(&cond);
sleep(1);
}while(1);
pthread_exit(0);
}
