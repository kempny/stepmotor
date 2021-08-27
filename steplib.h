int sminit (int ms1, int ms2, int ms3, int stepdir, int step, int reset, int sleep, int enable, int stepprev);
void smprec(int moth, int div);
void smspeed(int moth, int rpm);
int smgetspeed(int moth);
void smrun(int moth);
void smstop(int moth);
void smreset(int moth);
void smssleep(int moth, int state);
void smsenable(int moth, int state);
void smdir(int moth, int dir);
void smstep(int moth, int count);
void smangle(int moth, int full, int fract);
void *run(void *ptr);
void Delay_mcs(int microsec);
void Delay_mls(int milisec);



struct  conndef
{
  int ms1pin;
  int ms2pin;
  int ms3pin;
  int dirpin;
  int steppin;
  int resetpin;
  int sleeppin;
  int enablepin;
  int stepprev;    //steps per revolution
  int move;        //current state of movement
  int speed;       //current rotation speed, step duration / 2
  int speedrpm;       //current rotation speed, rotations per minute
  int prec;         //current step precision, 0 - 4
};

