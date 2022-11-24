#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <pthread.h>
#include <ctype.h>

int scheduling_priority_other=0,scheduling_priority_rr=3,scheduling_priority_fifo=3;
struct timespec start1,start2,start3,end1,end2,end3;

void* countA()
{
    struct sched_param param;
    
    clock_gettime(CLOCK_REALTIME,&start1);
    param.sched_priority=scheduling_priority_other;
    pthread_setschedparam(pthread_self(),SCHED_OTHER,&param);

    long long int counter=INT32_MIN;
    while(counter!=INT32_MAX)
    {
        counter++;
    }
    clock_gettime(CLOCK_REALTIME,&end1);
    return NULL;
}

void Change_priority_rr()
{
    scheduling_priority_rr++;
}

void Change_priority_fifo()
{
    scheduling_priority_fifo++;
}

void* countB()
{
    struct sched_param param1;
    
    clock_gettime(CLOCK_REALTIME,&start2);
    param1.sched_priority=scheduling_priority_rr;
    pthread_setschedparam(pthread_self(),SCHED_RR,&param1);
    
    long long int counter=INT32_MIN;
    while(counter!=INT32_MAX)
    {
        counter++;
    }
    clock_gettime(CLOCK_REALTIME,&end2);
    return NULL;
}

void* countC()
{
    struct sched_param param2;
    
    clock_gettime(CLOCK_REALTIME,&start3);
    param2.sched_priority=scheduling_priority_fifo;
    pthread_setschedparam(pthread_self(),SCHED_FIFO,&param2);
    
    long long int counter=INT32_MIN;
    while(counter!=INT32_MAX)
    {
        counter++;
    }
    clock_gettime(CLOCK_REALTIME,&end3);
    return NULL;
}

void Print_da_Graph(int num)
{
    char c='|';
    for(int i=0; i<num; i++)
    {
        printf("%c",c);
    }
}

int main()
{
    for(int k=4;k<10;k++)
    {
        int count1,count2,count3;

        pthread_t Thread_A,Thread_B,Thread_C;

        Change_priority_rr();
        Change_priority_fifo();
        
        pthread_create(&Thread_A,NULL,countA,NULL);
        pthread_create(&Thread_B,NULL,countB,NULL);
        pthread_create(&Thread_C,NULL,countC,NULL);
        

        pthread_join(Thread_A,NULL);
        pthread_join(Thread_B,NULL);
        pthread_join(Thread_C,NULL);

        double time1=((end1.tv_sec-start1.tv_sec)+((double)(end1.tv_nsec-start1.tv_nsec))/(double)1000000000L);

        double time2=((end2.tv_sec-start2.tv_sec)+((double)(end2.tv_nsec-start2.tv_nsec))/(double)1000000000L);

        double time3=((end3.tv_sec-start3.tv_sec)+((double)(end3.tv_nsec-start3.tv_nsec))/(double)1000000000L);
        
       if(time1<time2 && time1<time3)
       {
           count1=10;
           if(time2<time3)
           {
               count2=20;
               count3=30;
           }
           else
           {
               count3=20;
               count2=30;
           }
       }
        if(time2<time1 && time2<time3)
       {
           count2=10;
           if(time1<time3)
           {
               count1=20;
               count3=30;
           }
           else
           {
               count3=20;
               count1=30;
           }
       }
       if(time3<time1 && time3<time2)
       {
           count3=10;
           if(time1<time2)
           {
               count1=20;
               count2=30;
           }
           else
           {
               count2=20;
               count1=30;
           }
       }
        
        printf("----------------------------------SCHED_OTHER SCHEDULING POLICY----------------------------------\n");
        printf("Scheduling Priority: %d\n", scheduling_priority_other);
        printf("Time taken by Thread A to execute >>>> %lf\n",time1);
        printf("\n");
        
        printf("----------------------------------SCHED_RR SCHEDULING POLICY-------------------------------------\n");
        printf("Scheduling Priority: %d\n", scheduling_priority_rr);
        printf("Time taken by Thread B to execute >>>> %lf\n",time2);
        printf("\n");
        
        printf("----------------------------------SCHED_FIFO SCHEDULING POLICY-----------------------------------\n");
        printf("Scheduling Priority: %d\n", scheduling_priority_fifo);
        printf("Time taken by Thread C to execute >>>> %lf\n",time3);


        printf("\n\n<<<<<<<<<<<<<<HISTOGRAM>>>>>>>>>>>>>>>>>\n");
        printf("SCHED_OTHER[%d]  ", scheduling_priority_other);
        Print_da_Graph(count1);
        printf("%lf\n",time1);
        printf("SCHED_RR   [%d]  ", scheduling_priority_rr);
        Print_da_Graph(count2);
        printf("%lf\n",time2);
        printf("SCHED_FIFO [%d]  ", scheduling_priority_fifo);
        Print_da_Graph(count3);
        printf("%lf\n",time3);
        printf("\n\n\n");
    }
    return 0;
}