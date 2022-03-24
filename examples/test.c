*********************************************************************************
**   demo program two engines                                                  ** 
**   compile with:                                                             **
**     cc test.c steplib.c -o test -lwiringPi                                  **
**   run:                                                                      **
**     ./step                                                                  ** 
********************************************************************************/

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <steplib.h>


#define MAXENG 10


int i, j;
int smhandle;
int smhandle1;

/*********************************************************************/
int main (void)
{
  
       if (wiringPiSetup() == -1)
        {
         printf("wiringPi-Error\n");
         exit(1);
        }
  
       smhandle = sminit( 27, 24, 25, 29, 28, 99, 99, 99, 48);
printf("1: %d\n",smhandle);
       smhandle1 = sminit( 99, 99, 99, 22, 21, 99, 99, 99, 48);
printf("2: %d\n",smhandle1);

       smprec(smhandle,0);
       smspeed(smhandle,60);
       smdir(smhandle, 1);

       smprec(smhandle1,0);
       smspeed(smhandle1,60);
       smdir(smhandle1, 1);

printf("engine1\n");

   printf("Move until stop\n");
   printf("Start engine\n");
       smrun(smhandle);
       sleep(2);

       sleep(3);

   printf("Stop engine\n");
       smstop(smhandle);
       sleep(2);


       smdir(smhandle, 0);
       smrun(smhandle);
       sleep(5);
       smstop(smhandle);
       sleep(2);

printf("engine2\n");
   printf("Start engine\n");
       smrun(smhandle1);
       sleep(2);

       sleep(3);

   printf("Stop engine\n");
       smstop(smhandle1);
       sleep(2);


       smdir(smhandle1, 0);
       smrun(smhandle1);
       sleep(5);
       smstop(smhandle1);
       sleep(2);

printf("both engines\n");
       smdir(smhandle, 1);
       smdir(smhandle1, 1);
       smrun(smhandle);
       smrun(smhandle1);
       sleep(2);
       smstop(smhandle);
       smstop(smhandle1);
       sleep(1);
       smdir(smhandle, 0);
       smdir(smhandle1, 0);
       smrun(smhandle);
       smrun(smhandle1);
       sleep(2);
       smstop(smhandle);
       smstop(smhandle1);
}
