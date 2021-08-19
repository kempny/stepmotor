#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "steplib.h"
#include "pthread.h"


#define MAXENG 10


struct conndef parm[MAXENG]; 
int motcount = 0;

/**********************************************************************/
int sminit (int ms1, int ms2, int ms3, int stepdir, int step, int reset, int sleep, int enable, int stepprev)
{
  if (motcount == (MAXENG -1))
      {printf("To many engines, only %d are supported\n", MAXENG); exit(1);}

  parm[motcount].ms1pin =  ms1;
  parm[motcount].ms2pin =  ms2;
  parm[motcount].ms3pin =  ms3;
  parm[motcount].dirpin =  stepdir;
  parm[motcount].steppin =  step;
  parm[motcount].resetpin =  reset;
  parm[motcount].sleeppin =  sleep;
  parm[motcount].enablepin =  enable;
  parm[motcount].stepprev =  stepprev;
  parm[motcount].speed =  25000;  // step 50 miliseconds, not too fast 

  if (ms1 != 99) pinMode (ms1, OUTPUT);
  if (ms2 != 99) pinMode (ms2, OUTPUT);
  if (ms3 != 99) pinMode (ms3, OUTPUT);
  if (stepdir != 99) pinMode (stepdir, OUTPUT);
  if (step != 99) pinMode (step, OUTPUT);
  if (reset != 99) pinMode (reset, OUTPUT);
  if (sleep != 99) pinMode (sleep, OUTPUT);
  if (enable != 99) pinMode (enable, OUTPUT);

  return(motcount); 
  motcount++;
}

/***********************************************************************/
void smprec(int moth, int div) // motor handle, precision: 0 (full step) - 4 (1/16 of step)
{
int olddiv, newdiv;
int trms[5][3] = {
       {0,0,0},  //full step
       {1,0,0},  //half step
       {0,1,0},  //quarter step
       {1,1,0},  //eighth step
       {1,1,1} //sixteenth step
                 };
       if (div > 4) 
          {printf("Unknown precision\n"); exit(1);}

       digitalWrite (parm[moth].ms1pin, trms[div][0]);
       digitalWrite (parm[moth].ms2pin, trms[div][1]);
       digitalWrite (parm[moth].ms3pin, trms[div][2]);

       olddiv = parm[moth].prec;
       newdiv = 1;
       while (div != 0)
         {
          newdiv *= 2;
          --div;
         }

       parm[moth].prec = newdiv;
// correct the speed of motor
       parm[moth].speed = parm[moth].speed * olddiv / newdiv;
//printf (" div speed  %d %d \n", div, parm[moth].speed);
}  

/***********************************************************************/
void smspeed(int moth, int rpm) // motor handle, rotations per minute
{
   int div;
   float speedf;
      div = parm[moth].prec;

      speedf=1000000/((float)rpm/60*parm[moth].stepprev*2*div);
      parm[moth].speed = speedf;
      parm[moth].speedrpm = rpm;
//printf (" div speed  %d %d \n", div, parm[moth].speed);
}  

/***********************************************************************/
int smgetspeed(int moth) // motor handle
{
      return(parm[moth].speedrpm);
}  

/**********************************************************/
void smstep(int moth, int count)
{
   int i;
   for(i=0;i<count;i++)
     { 
       digitalWrite (parm[moth].steppin, 1);
       Delay_mcs(parm[moth].speed);
       digitalWrite (parm[moth].steppin, 0);
       Delay_mcs(parm[moth].speed);
     }
}

/**********************************************************/
void smangle(int moth, int full, int fract)
{
   smstep(moth, full * parm[moth].stepprev + parm[moth].stepprev * fract / 360);
}
/**********************************************************/
void *run(void *ptr)
{
int moth;
moth =  (int)ptr;

  parm[moth].move = 1;
  while(parm[moth].move)
     {
       digitalWrite (parm[moth].steppin, 1);
       Delay_mcs(parm[moth].speed);
       digitalWrite (parm[moth].steppin, 0);
       Delay_mcs(parm[moth].speed);
     }
}




void smrun(int moth)
{
    pthread_t thread_id;
    pthread_create (&thread_id, NULL, run, (void *)moth);

}

/**********************************************************/
void smstop(int moth)
{
  parm[moth].move = 0;
}

/**********************************************************/
void smdir(int moth, int dir) 
{
    digitalWrite (parm[moth].dirpin, dir);
}
