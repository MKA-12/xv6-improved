#include "types.h"
#include "stat.h"
#include "user.h"
#include "proc_stat.h"
void foo()
{
    int i;
    for (i = 0; i < 100; i++)
        printf(2, "wait test %d\n", i);
    sleep(20);
    for (i = 0; i < 100; i++)
        printf(2, "wait test %d\n", i);
}
void koushik();
void timewaste(int);
void waittest(void)
{
    int wtime;
    int rtime;
    int pid;
    printf(1, "wait test\n");

    pid = fork();
    if (pid == 0)
    {
        foo();
        exit();
    }
    waitx(&wtime, &rtime);
    printf(1, "hi \n");
    printf(1, "wTime: %d rTime: %d \n", wtime, rtime);
}
void func()
{
    printf(1, "Hello World\n");
    int k = fork();
    if (k > 0)
    {
        printf(1, "Parent Started ----\n");
        printf(1, "Child ain't dead\n");
        int *wtime = malloc(sizeof(int));
        int *rtime = malloc(sizeof(int));
        *wtime = 0;
        *rtime = 0;
        waitx(wtime, rtime);
        // wait();
        printf(1, "In parent process : wait and run times are %d %d\n", *wtime, *rtime);
        printf(1, "Child dead lmao\n");
        printf(1, "Parent Exited ----\n");
    }
    else
    {
        printf(1, "Child Started ---- \n");
        sleep(300);
        printf(1, "Child Exited ----\n");
        for (int i = 0; i < 100000; i++)
        {
        }
        exit();
    }
}
void test()
{
    for (int i = 0; i < 10; i++)
    {
        int p = fork();
        if (p == 0)
        {
            // int num;
            // if(i < 10){
            //     num =300;
            // }
            // else {
            //     num = 5;
            // }
            // sleep(num);
            sleep(10);
            for (int i = 0; i < 100; i++)
            {
                printf(1, "%d\n", i);
            }
            exit();
        }
        else
        {
            int wtime, rtime, pid;
            pid = waitx(&wtime, &rtime);
            printf(1, "wtime = %d\nrtime = %d\npid = %d\n", wtime, rtime, pid);
        }
    }
}
void test2()
{
    int w, r, ret;
    if (fork() == 0)
    {
        for (int i = 0; i < 4; i++)
        {
            int p = fork();
            if (p == 0)
            {
                printf(1, "proc %d.... \n", i);
                for (int i = 0; i <= 10000000; i++)
                    printf(1, "");
                // exec(argv[1],argv);
                exit();
            }
        }
        for (int i = 0; i < 4; i++)
        {
            ret = waitx(&w, &r);
            printf(1, "pid-%d rtime-%d wtime-%d\n", ret, r, w);
        }
        exit();
    }
    ret = waitx(&w, &r);
    printf(1, "parent proc:- pid-%d rtime-%d wtime-%d\n", ret, w, r);
}
void test3()
{
    int w, r, ret, p[10];
    if (fork() == 0)
    {
        for (int i = 0; i < 10; i++)
        {
            p[i] = fork();
            if (p[i] == 0)
            {
                for (int i = 0; i <= 100000000; i++)
                    printf(1, "");
                // sleep(1000);
                // exec(argv[1],argv);
                exit();
            }
        }
        for (int i = 0; i < 10; i++)
        {
            printf(1, "proc %d.... pid %d \n", i, p[i]);
            set_priority(64 - i, p[i]);
        }
        for (int i = 0; i < 10; i++)
        {
            struct proc_stat *process = malloc(sizeof(struct proc_stat));
            getpinfo(process, i + 4);
            printf(1, "pid - %d\nruntime - %d\ncurrent queue - %d\n", process->pid, process->runtime, process->current_queue);
            for (int i = 0; i < 5; i++)
            {
                printf(1, "ticks[%d] - %d\n", i, process->ticks[i]);
            }
            ret = waitx(&w, &r);
            printf(1, "pid-%d rtime-%d wtime-%d\n", ret, r, w);
        }
    }
    else
    {
        int w, r;
        waitx(&w, &r);
        printf(1,"rtime %d wtime %d\n", r, w);
        exit();
    }
}
void t(int l)
{
    int x = 0;
    for (int i = 0; i < l * 10000000; i++)
    {
        x++;
        x--;
        printf(1, "");
    }
}
void sachin()
{
    for (int i = 0; i < 5; i++)
    {
        int pid = fork();
        if (pid == 0)
        {
            switch (i)
            {
            case 1:
                t(3);
                break;
            case 2:
                t(4);
                break;
            case 3:
                t(5);
                break;
            case 4:
                t(6);
                break;
            default:
                t(7);
                break;
            }
            exit();
        }
    }
    for (int i = 0; i < 5; i++)
    {
        int wtime, rtime;
        waitx(&wtime, &rtime);
    }
    exit();
}
void bench_func()
{
    int p[20];
    for (int i = 0; i < 10; i++)
    {
        p[i] = fork();
        if (p[i] == 0)
        {
            for (int j = 0; j < 900000000; j++)
            {
            }
            struct proc_stat *process = malloc(sizeof(struct proc_stat));
            getpinfo(process, i + 4);
            printf(1, "pid - %d\nruntime - %d\ncurrent queue - %d\n", process->pid, process->runtime, process->current_queue);
            for (int i = 0; i < 5; i++)
            {
                printf(1, "ticks[%d] - %d\n", i, process->ticks[i]);
            }
            exit();
        }
        else
        {
            int w;
            int r;
            waitx(&w, &r);
            printf(1, "pid - %d  wtime - %d  rtime - %d\n", p[i], w, r);
        }
    }
    for (int i = 0; i < 10; i++)
    {

        // waitx();

        exit();
    }
}
void wait_func()
{
    for (int i = 0; i < 10; i++)
    {
        int p = fork();
        if (p == 0)
        {
            for (int i = 0; i < 5 * 1e8; i++)
            {
            }
            exit();
        }
    }
    for (int i = 0; i < 10; i++)
    {
        int w;
        int r;
        waitx(&w, &r);
        printf(1, "wtime - %d  rtime - %d\n", w, r);
        exit();
    }
}
int main(void)
{

#if FCFS
    printf(1, "FCFS\n");
#else
#if DEFAULT
    printf(1, "DEFAULT\n");
#else
#if PBS
    printf(1, "PBS\n");
#else
#if MLFQ
    printf(1, "MLFQ\n");
#endif
#endif
#endif
#endif
    // getpinfo()
    test3();
    // bench_func();
    // sachin();
    // koushik();

    exit();
}

void timewaste(int n)
{
    int x = 0;
    for (int i = 0; i < n * 10000000; i++)
    {
        x++;
        x--;
        printf(1, "");
    }
}
void koushik()
{
#if FCFS
    printf(1, "FCFS\n");
#else
#if DEFAULT
    printf(1, "DEFAULT\n");
#else
#if PBS
    printf(1, "PBS\n");
#else
#if MLFQ
    printf(1, "MLFQ\n");
#endif
#endif
#endif
#endif
    for (int i = 0; i < 4; i++)
    {
        int pid = fork();
        if (pid == 0)
        {
            switch (i)
            {
            case 1:
                timewaste(4);
                set_priority(getpid(), 100);
                break;
            case 2:
                timewaste(3);
                set_priority(getpid(), 90);
                break;
            case 3:
                timewaste(5);
                set_priority(getpid(), 80);
                break;
            default:
                set_priority(getpid(), 70);
                timewaste(3);
                break;
            }
            exit();
        }
    }
    for (int i = 0; i < 4; i++)
    {
        int a, b;
        waitx(&a, &b);
    }
    exit();
}