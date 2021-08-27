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
  if (reset != 99)  
    {
      pinMode (reset, OUTPUT);
      digitalWrite(reset, 1);
    }
  if (sleep != 99) 
    {
      pinMode (sleep, OUTPUT);
      digitalWrite(sleep, 1);
    }
  if (enable != 99) 
    {
      pinMode (enable, OUTPUT);
      digitalWrite(enable, 1);
    }

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

       if (parm[moth].ms1pin != 99)
         digitalWrite (parm[moth].ms1pin, trms[div][0]);
       if (parm[moth].ms2pin != 99)
         digitalWrite (parm[moth].ms2pin, trms[div][1]);
       if (parm[moth].ms3pin != 99)
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
}  

/***********************************************************************/
int smgetspeed(int moth) // motor handle
{
      return(parm[moth].speedrpm);
}  

/**********************************************************/

void smstep(int moth, int count)
{
   if (parm[moth].steppin == 99) return;

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
   smstep(moth, full * parm[moth].stepprev * parm[moth].prec + parm[moth].stepprev * parm[moth].prec * fract / 360);
}

/**********************************************************/
void *run(void *ptr)
{

int moth;
moth =  (int)ptr;

  if (parm[moth].steppin == 99) return(0);

  parm[moth].move = 1;
  while(parm[moth].move)
     {
       digitalWrite (parm[moth].steppin, 1);
       Delay_mcs(parm[moth].speed);
       digitalWrite (parm[moth].steppin, 0);
       Delay_mcs(parm[moth].speed);
     }
  return(0);
}

/**********************************************************/
void smrun(int moth)
{
    pthread_t thread_id;
    pthread_create (&thread_id, NULL, run, (void *)moth);

}

/**********************************************************/
void smstop(int moth)
{
  parm[moth].move = 0;
  Delay_mcs(parm[moth].speed * 3); // to be sure that the step cycle will be finished


}

/**********************************************************/
void smdir(int moth, int dir) 
{ 
    if (parm[moth].dirpin == 99) return;

    digitalWrite (parm[moth].dirpin, dir);
}
 
/**********************************************************/
void smreset(int moth)
{
    digitalWrite (parm[moth].resetpin, 1);
    Delay_mls(1);
    digitalWrite (parm[moth].resetpin, 1);
}

/**********************************************************/
void smssleep(int moth, int state) // state: 0- sleep, 1 - no sleep
{

    digitalWrite (parm[moth].sleeppin, state); 
    Delay_mls(1);
}

/**********************************************************/
void smsenable(int moth, int state) // state: 0- enable, 1 - disable
{
    digitalWrite (parm[moth].enablepin, state); 
}
