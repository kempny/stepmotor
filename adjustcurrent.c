/********************************************************************************
*  adjustcurrent:
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
**   auxiliary program to adjust stepper motor max current                                                        ** 
**   compile with:                                                             **
**     cc adjustcurrent.c -o adjustcurrent -lwiringPi                          **
**   run:                                                                      **
**     ./step                                                                  ** 
********************************************************************************/

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define MS1 27
#define MS2 24
#define MS3 25
#define STEPDIR 29
#define STEP 28


int i,j;

void prec(int div) //precision, 0 (full step) - 4 (1/16 of step)
{
int trms[5][3] = {
       {0,0,0},  //full step
       {1,0,0},  //half step
       {0,1,0},  //quarter step
       {1,1,0},  //eighth step
       {1,1,1} //sixteenth step
                 };
       if (div > 4) 
          {printf("unknown precision\n"); exit(1);}

       digitalWrite (MS1, trms[div][0]);
       digitalWrite (MS2, trms[div][1]);
       digitalWrite (MS3, trms[div][2]);
}  

int main (void)
{
  
  // check wiringPi setup
  if (wiringPiSetup() == -1)
  {
	printf("wiringPi-Error\n");
    exit(1);
  }
       pinMode(STEPDIR, OUTPUT); // step motor direction
       pinMode(STEP, OUTPUT); // step moror pulse
       digitalWrite(STEPDIR, 1); // clockwise


       pinMode(MS1, OUTPUT);
       pinMode(MS2, OUTPUT);
       pinMode(MS3, OUTPUT);

       prec(0);
       digitalWrite(STEP,1);

printf("You can adjust the current limit, press ^C to finish\n");
       for(;;);
}
