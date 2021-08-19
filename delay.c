#include <time.h>
#include <unistd.h>


struct timespec tim;

void Delay_sec(int sec)
{
 tim.tv_sec = sec;
 tim.tv_nsec = 0;
     while(nanosleep(&tim,&tim)==-1)
          continue;
}

void Delay_mls(int milisec)
{
 tim.tv_sec = 0;
 tim.tv_nsec = milisec * 1000000;
     while(nanosleep(&tim,&tim)==-1)
          continue;
}

void Delay_mcs(int microsec)
{
 tim.tv_sec = 0;
 tim.tv_nsec = microsec * 1000;
     while(nanosleep(&tim,&tim)==-1)
          continue;
}

void Delay_ns(int nanosec)
{
 tim.tv_sec = 0;
 tim.tv_nsec = nanosec;
     while(nanosleep(&tim,&tim)==-1)
          continue;
}
