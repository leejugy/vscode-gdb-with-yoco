#include "thread.h"

static void thread1(void *arg)
{
    (void)arg;
    int a = 0;
    printg("thread1");
    while (1)
    {
        printb("hellow i am thread1 : %d", a++);
        sleep(1);
    }
}

static void thread2(void *arg)
{
    (void)arg;
    int a = 0;
    printg("thread2");
    while (1)
    {
        printb("hellow i am thread2 : %d", a++);
        sleep(1);
    }
}

static void thread3(void *arg)
{
    (void)arg;
    int a = 0;
    printg("thread3");
    while (1)
    {
        printb("hellow i am thread3 : %d", a++);
        sleep(1);
    }
}

void start_thread()
{
    pthread_t tid[THREAD_NUM] = {0, };
    void *function[THREAD_NUM] = {&thread1, &thread2, &thread3};
    int i = 0;

    for(i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_create(&tid[i], NULL, (void *)function[i], NULL) < 0)
        {
            printr("fail to detach : %s", strerror(errno));
        }

        if (pthread_detach(tid[i]) < 0)
        {
            printr("fail to create : %s", strerror(errno));
        }
    }
}