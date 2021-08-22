/********************************************************************************
step:
*       This file is part of stepmotor - RaspberryPi stepper motor 
*       control library using A4988 controller
*       Copyright (C) 2021  Boguslaw Kempny kempny@stanpol.com.pl
*
*********************************************************************************
*    stepmotor is free software: you can redistribute it and/or modify
*    it under the terms of the GNU Lesser General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    stepmotor is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU Lesser General Public License for more details.
*
*    You should have received a copy of the GNU Lesser General Public License
*    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
*
*********************************************************************************
**   demo program                                                              ** 
**   compile with:                                                             **
**     cc step.c delay.c steplib.c -o step -lwiringPi -lpthread                **
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

/*********************************************************************/
int main (void)
{
  
       if (wiringPiSetup() == -1)
        {
         printf("wiringPi-Error\n");
         exit(1);
        }
  
       smhandle = sminit( 27, 24, 25, 29, 28, 99, 99, 99, 20);

       smprec(smhandle,0);
       smspeed(smhandle,60);
      smdir(smhandle, 1);

   printf("Move until stop\n");
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
       sleep(2);

   printf ("3 seconds with quarter step\n");
       smprec(smhandle,2);
       smrun(smhandle);
       sleep(3);
       smstop(smhandle);
       sleep(2);

   printf("Move counterclockwise\n");

       smdir(smhandle, 1);
       smrun(smhandle);
       sleep(2);
       smstop(smhandle);
       sleep(2);

   printf("Move clockwise\n");

       smdir(smhandle, 0);
       smrun(smhandle);
       sleep(2);
       smstop(smhandle);
       sleep(2);

       smdir(smhandle, 1);
   printf("20 steps at full step\n");
       smprec(smhandle,0);
       smstep(smhandle, 20);
       sleep(2);

   printf(0);("20 steps at half step\n");
       smprec(smhandle, 1);
       smstep(smhandle, 20);
       sleep(2);

   printf("20 steps at quarter step\n");
       smprec(smhandle, 2);
       smstep(smhandle, 20);
       sleep(2);

   printf("20 steps at eighth step\n");
       smprec(smhandle, 3);
       smstep(smhandle, 20);
       sleep(2);

   printf("20 steps at sixteenth step\n");
       smprec(smhandle, 4);
       smstep(smhandle, 20);
       sleep(2);

   printf("45 degree angle\n");
       smprec(smhandle, 2);
       smangle(smhandle, 0, 45);
       sleep(2);

   printf("180 degree angle\n");
       smangle(smhandle, 0, 180);
       sleep(2);

   printf("2 full evolutions and 90 degree\n");
       smangle(smhandle, 2, 90);
       sleep(2);


   printf("Clock\n");
   smprec(smhandle, 0);
   for(i=0;i<20;i++)
   {
       smstep(smhandle, 1);
       sleep(1);
   }

   printf("1 step\n");
       smstep(smhandle, 1);
       sleep(2);

   printf("10 steps\n");
       smstep(smhandle, 10);
       sleep(2);

   printf("100 steps\n");
       smstep(smhandle, 100);
       sleep(2);

   printf("move with speed varying\n");
   printf("Start engine\n");
       int newspeed;
       smspeed(smhandle,60);
       smprec(smhandle, 0);
       smrun(smhandle);
       sleep(3);

   printf("Accelerate\n");
       j = smgetspeed(smhandle);
       for(i=0;i<1000; i++)
        {
          newspeed = i + j; 
          smspeed (smhandle, newspeed);
          Delay_mls(20);
        }
   printf("Constant speed\n");
       sleep(3);
   printf("Decelerate\n");
       for(i=1000;i>0; i--)
        {
          newspeed = i + j; 
          smspeed (smhandle, newspeed);
          Delay_mls(20);
        }
   printf("Constant speed\n");
       sleep(3);

   printf("Stop engine\n");
       smstop(smhandle);
}
