#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>



#define LOOP_COUNT 25
void ParentProcess(int *BankAccount, int *Turn);
void ChildProcess(int *BankAccount, int *Turn);

int  main()
{
     int ShmID;
     int    *ShmPTR;
     pid_t  pid;
     int    status;


     ShmID = shmget(IPC_PRIVATE, 2*sizeof(int), IPC_CREAT | 0666);
     if (ShmID < 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }
     //printf("Server has received a shared memory of four integers...\n");

     ShmPTR = (int *) shmat(ShmID, NULL, 0);
     if (*ShmPTR == -1) {
          printf("*** shmat error (server) ***\n");
          exit(1);
     }
     //printf("Server has attached the shared memory...\n");

     //ShmPTR[0] = atoi(argv[1]);
    // ShmPTR[1] = atoi(argv[2]);
     //ShmPTR[2] = atoi(argv[3]);
     //ShmPTR[3] = atoi(argv[4]);
     //printf("Server has filled %d %d %d %d in shared memory...\n",
            //ShmPTR[0], ShmPTR[1], ShmPTR[2], ShmPTR[3]);
      ShmPTR[0] = 0;
      ShmPTR[1] = 0;
      printf("Shared memory created and initialized...\n");


     //printf("Server is about to fork a child process...\n");
     pid = fork();
     if (pid < 0) {
          printf("*** fork error (server) ***\n");
          exit(1);
     }
     else if (pid == 0) {
          ChildProcess(&ShmPTR[0], &ShmPTR[1]);
          exit(0);
     }else{
      ParentProcess(&ShmPTR[0], &ShmPTR[1]);
     }

     wait(&status);
    printf("Server has detected the completion of its child...\n");
     shmdt((void *) ShmPTR);
     printf("Server has detached its shared memory...\n");
     shmctl(ShmID, IPC_RMID, NULL);
     printf("Server has removed its shared memory...\n");
     printf("Server exits...\n");
     exit(0);
}



void ParentProcess(int *BankAccount, int *Turn){
  srand(time(NULL));
  for(int i = 0; i<LOOP_COUNT; i++){
    sleep(rand()%6);
    int account = *BankAccount;
    while(*Turn != 0);

    if (account <= 100){
      int balance = rand()% 101;
      if (balance % 2 ==0){
        account+=balance;
        printf("Dear old Dad: Deposits $%d / Balance = $%d\n", balance, account);
      }else{
        printf("Dear old Dad: Doesn't have any money to give\n");
      }
      *BankAccount= account;
      *Turn= 1; 

    }
  }
}

void ChildProcess(int *BankAccount, int *Turn) {
    srand(time(NULL) + 1);  
    for (int i = 0; i < LOOP_COUNT; i++) {
        sleep(rand() % 6); 

        int account = *BankAccount; 
        while (*Turn != 1); 

        int balance = rand() % 51; 
        printf("Poor Student needs $%d\n", balance);

        if (balance <= account) {
            account -= balance;
            printf("Poor Student: Withdraws $%d / Balance = $%d\n", balance, account);
        } else {
            printf("Poor Student: Not Enough Cash ($%d)\n", account);
        }

        *BankAccount = account;  
        *Turn = 0; 
    }
}