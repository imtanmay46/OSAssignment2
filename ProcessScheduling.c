#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <limits.h>
#include <pthread.h>
#include <ctype.h>
#include <sched.h>

struct timespec start1,start2,start3,end1,end2,end3;
struct sched_param param,param1,param2;

int main()
{
    pid_t pid=fork();

    clock_gettime(CLOCK_REALTIME,&start1);
    // param.sched_priority=SCHED_OTHER;
    // sched_setscheduler(pid,SCHED_OTHER,param);
    if(pid==0)
    {
        execl("/Users/varul18/Desktop/Assignment-2_OS/count",NULL);
    }
    else if(pid>0)
    {
        pid_t pid1=fork();
        clock_gettime(CLOCK_REALTIME,&start2);
        // param1.sched_priority=SCHED_RR;
        // sched_setscheduler(pid1,SCHED_RR,param1);
        if(pid1==0)
        {
            execl("/Users/varul18/Desktop/Assignment-2_OS/count",NULL);
        }
        else if(pid1>0)
        {
            pid_t pid2=fork();
            clock_gettime(CLOCK_REALTIME,&start3);
            // param2.sched_priority=SCHED_FIFO;
            // sched_setscheduler(pid2,SCHED_FIFO,param2);
            if(pid2==0)
            {
                execl("/Users/varul18/Desktop/Assignment-2_OS/count",NULL);
            }
            else if(pid2>0)
            {
                pid_t check_wait=wait(NULL);
                if(check_wait==pid)
                {
                    clock_gettime(CLOCK_REALTIME,&end1);
                    
                    check_wait=wait(NULL);
                    if(check_wait==pid1)
                    {
                        clock_gettime(CLOCK_REALTIME,&end2);

                        check_wait=wait(NULL);
                        if(check_wait==pid2)
                        {
                            clock_gettime(CLOCK_REALTIME,&end3);
                        }
                    }
                    else if(check_wait==pid2)
                    {
                        clock_gettime(CLOCK_REALTIME,&end3);

                        check_wait=wait(NULL);
                        if(check_wait==pid1)
                        {
                            clock_gettime(CLOCK_REALTIME,&end2);
                        }
                    }

                }
                else if(check_wait==pid1)
                {
                    clock_gettime(CLOCK_REALTIME,&end2);

                    check_wait=wait(NULL);
                    if(check_wait==pid)
                    {
                        clock_gettime(CLOCK_REALTIME,&end1);

                        check_wait=wait(NULL);
                        if(check_wait==pid2)
                        {
                            clock_gettime(CLOCK_REALTIME,&end3);
                        }
                    }
                    else if(check_wait==pid2)
                    {
                        clock_gettime(CLOCK_REALTIME,&end3);

                        check_wait=wait(NULL);
                        if(check_wait==pid)
                        {
                            clock_gettime(CLOCK_REALTIME,&end1);
                        }
                    }
                }
                else if(check_wait==pid2)
                {
                    clock_gettime(CLOCK_REALTIME,&end3);
                    check_wait=wait(NULL);
                    if(check_wait==pid)
                    {
                        clock_gettime(CLOCK_REALTIME,&end1);

                        check_wait=wait(NULL);
                        if(check_wait==pid1)
                        {
                            clock_gettime(CLOCK_REALTIME,&end2);
                        }
                    }
                    else if(check_wait==pid1)
                    {
                        clock_gettime(CLOCK_REALTIME,&end2);

                        check_wait=wait(NULL);
                        if(check_wait==pid)
                        {
                            clock_gettime(CLOCK_REALTIME,&end1);
                        }
                    }
                }
            }
        }
    }

    double time1=((end1.tv_sec-start1.tv_sec)+((double)(end1.tv_nsec-start1.tv_nsec))/(double)1000000000L);
    printf("%lf\n",time1);

    double time2=((end2.tv_sec-start2.tv_sec)+((double)(end2.tv_nsec-start2.tv_nsec))/(double)1000000000L);
    printf("%lf\n",time2);

    double time3=((end3.tv_sec-start3.tv_sec)+((double)(end3.tv_nsec-start3.tv_nsec))/(double)1000000000L);
    printf("%lf\n",time3);

    return 0;
}