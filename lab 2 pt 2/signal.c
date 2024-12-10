/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t signal_recieve=0;
void handler(int signum)
{ //signal handler
  printf("Hello World!\n");
  signal_recieve = 1;
  alarm(5);
  //exit(1); //exit after printing
}

int main(int argc, char * argv[])
{
  signal(SIGALRM,handler); //register handler to handle SIGALRM
  alarm(5); //Schedule a SIGALRM for 5 seconds
  while(1){
    if(signal_recieve){
      printf("turing was right! \n");
      signal_recieve=0;
    }
    usleep(100000);
  };
   //busy wait for signal to be delivered
  return 0; //never reached
}