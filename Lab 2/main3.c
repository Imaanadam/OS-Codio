#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ITERATIONS 30
#define MAX_SLEEP_TIME 10

void child_process();
void parent_process(pid_t, pid_t);

int main(void){
  pid_t pid1, pid2;
  // random number generator
  srandom(time(NULL));

  //first child proccess
  pid1 = fork();
  if (pid1 <0){
    perror("Failure to fork first child");
    exit(1);
  } 
    else if (pid1 ==0){
      child_process();
      exit(0);

    }

    // creating second child process
    pid2=fork();
    if (pid2<0){
      perror("Failed to fork second child");
      exit(1);
    }
    else if (pid2 == 0){
      child_process();
      exit(0);

    }
    parent_process(pid1,pid2)
    return 0;

}

void child_process(){
  pid_t pid = getpid();
  pid_t ppid = getppid();

  // random number of iterations  

  int iterations = (random() % MAX_ITERATIONS) +1;

  for (int i = 0; i < iterations; i++){
    printf("Child Pid: %d is going to sleep!\n", pid);

    // sleep for random time 1-10
    int sleep_time = (random() %MAX_SLEEP_TIME)+1;
    sleep(sleep_time);
    printf("Child Pid: %d is awake!\nWhere is my Parent: %d\n", pid,ppid);

  }
}

void parent_process(pid_t pid1, pid_t pid 2){
  int status;
  pid_t child_pid;
  // first child terminate
  child_pid = wait(&status);
  printf("Child Pid: %d has completed\n", child_pid);

  // second child terminate
  child_pid = wait(&status);
  printf("Child Pid: %d has completed\n", child_pid);


}