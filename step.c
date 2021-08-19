/***************************************************************************
**   demo program                                                         **
**   compile with:                                                        **
**     cc step.c delay.c steplib.c -o step -lwiringPi -lpthread           **
**   run:                                                                 **
**     ./step                                                             **      
***************************************************************************/
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "steplib.h"


#define MS1 27
#define MS2 24
#define MS3 25
#define STEPDIR 29
#define STEP 28
#define MAXENG 10


int i, j;
int smhandle;

/*********************************************************************/
int main (void)
{
  
  // check wiringPi setup
  if (wiringPiSetup() == -1)
  {
	printf("wiringPi-Error\n");
    exit(1);
  }
  
       smhandle = sminit( 27, 24, 25, 29, 28, 99, 99, 99, 20);

       smprec(smhandle,0);
       smspeed(smhandle,60);

printf("Move until stop\n");
//goto aaa;
printf("Start engine\n");
smrun(smhandle);
sleep(2);
printf("The engine turns\n");
sleep(3);
printf("Stop engine\n");
smstop(smhandle);
sleep(2);
  
printf ("3 seconds with half step\n");
smprec(smhandle,1);
smrun(smhandle);
sleep(3);
smstop(smhandle);
sleep(1);

printf ("3 seconds with quarter step\n");
smprec(smhandle,2);
smrun(smhandle);
sleep(3);
smstop(smhandle);
sleep(1);

printf("Move counterclockwise\n");

smdir(smhandle, 1);
//piThreadCreate(run);
smrun(smhandle);
sleep(2);
smstop(smhandle);
sleep(1);

printf("Move clockwise\n");

smdir(smhandle, 0);
//piThreadCreate(run);
smrun(smhandle);
sleep(2);
smstop(smhandle);
sleep(1);

printf("20 steps at full step\n");
       for(i=0;i<20;i++)   
         {  
          digitalWrite(STEP,1);
          Delay_mcs(10);;
          digitalWrite(STEP, 0);
          Delay_mcs(10000);
         }
	sleep(1);
printf("20 steps at half step\n");
       smprec(smhandle, 1);
       for(i=0;i<20;i++)   
         {  
          digitalWrite(STEP,1);
          Delay_mcs(10);;
          digitalWrite(STEP, 0);
          Delay_mcs(10000);;
         }

sleep(1);
printf("20 steps at quarter step\n");
       smprec(smhandle, 2);
       for(i=0;i<20;i++)   

         {  
          digitalWrite(STEP,1);
          Delay_mcs(10);;
          digitalWrite(STEP, 0);
          Delay_mcs(10000);;
         }
sleep(1);
printf("20 steps at eighth step\n");
       smprec(smhandle, 3);
       for(i=0;i<20;i++)   
         {  
          digitalWrite(STEP,1);
          Delay_mcs(10);;
          digitalWrite(STEP, 0);
          Delay_mcs(10000);;
         }

sleep(1);
printf("20 steps at sixteenth step\n");
       smprec(smhandle, 4);
       for(i=0;i<20;i++)   
         {  
          digitalWrite(STEP,1);
          Delay_mcs(10);;
          digitalWrite(STEP, 0);
          Delay_mcs(10000);;
         }
aaa:
printf("45 degree angle\n");
smangle(smhandle, 0, 45);
sleep(1);
printf("180 degree angle\n");
smangle(smhandle, 0, 180);
sleep(1);
printf("2 full evolutions and 90 degree\n");
smangle(smhandle, 2, 90);
sleep(1);

printf("1 step\n");
smstep(smhandle, 1);
sleep(1);
printf("10 steps\n");
smstep(smhandle, 10);
sleep(1);
printf("100 steps\n");
smstep(smhandle, 100);
sleep(1);

printf("move with speed varying\n");
printf("Start engine\n");
       int newspeed;
       smspeed(smhandle,60);
       smprec(smhandle, 0);
       smrun(smhandle);
       sleep(2);

printf("Accelerate\n");
       j = smgetspeed(smhandle);
       for(i=0;i<1000; i++)
        {
          newspeed = i + j; 
          smspeed (smhandle, newspeed);
          Delay_mls(20);
        }
printf("Constant speed\n");
       sleep(2);
printf("Decelerate\n");
       for(i=1000;i>0; i--)
        {
          newspeed = i + j; 
          smspeed (smhandle, newspeed);
          Delay_mls(20);
        }
printf("Constant speed\n");
       sleep(2);

printf("Stop engine\n");
smstop(smhandle);

}
