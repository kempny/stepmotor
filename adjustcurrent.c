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
struct timespec tim;
void Delay(int microsec)
{

 tim.tv_sec = 0;
 tim.tv_nsec = microsec * 1000;
     while(nanosleep(&tim,&tim)==-1)
          continue;
}

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
