#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int i,j;
struct timespec tim;
void Delay(int microsec)
{

 tim.tv_sec = 0;
 tim.tv_nsec = microsec * 1000;
     while(nanosleep(&tim,&tim)==-1)
          continue;
}

  
int main (void)
{
  
  // check wiringPi setup
  if (wiringPiSetup() == -1)
  {
	printf("wiringPi-Error\n");
    exit(1);
  }
       pinMode(29, OUTPUT); // step motor direction
       pinMode(28, OUTPUT); // step moror pulse
       digitalWrite(29, 1); // clockwise
       for(i=0;i<100;i++)   
         {  
          digitalWrite(28,1);
          Delay(10);;
          digitalWrite(28, 0);
          Delay(100000);;
         }
       digitalWrite(29, 0); // counterclockwise
       for(i=0;i<100;i++)
         {  
          digitalWrite(28,1);
          Delay(10);;
          digitalWrite(28, 0);
          Delay(100000);;
         }

}
