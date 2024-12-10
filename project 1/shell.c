#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128

char prompt[] = "> ";
char delimiters[] = " \t\r\n";
extern char **environ;

void sigint_handler(int s)
{ 
  printf("caught SIGINT. Use 'exit' to quit the shell.\n");

}
void sigalarm_handler(int s)
{
  printf("process terminated due to timeout.\n");
}


int main() {
    // Stores the string typed into the command line.
    char command_line[MAX_COMMAND_LINE_LEN];
    char cmd_bak[MAX_COMMAND_LINE_LEN];
  
    // Stores the tokenized command line input.
    char *arguments[MAX_COMMAND_LINE_ARGS];

    signal(SIGINT, sigint_handler);
    signal(SIGALRM, sigalarm_handler);
    	
   while (true) {
        // Print the shell prompt with the current working directory
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s> ", cwd);
        } else {
            perror("getcwd() error");
        }
        fflush(stdout);

        // Read input from the user
        if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
            fprintf(stderr, "fgets error");
            exit(0);
        }

        // Handle empty input (just pressing Enter)
        if (command_line[0] == 0x0A) {
            continue;
        }

        // Remove the newline character from the input
        command_line[strlen(command_line) - 1] = '\0';

        // Handle EOF (Ctrl+D)
        if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            fflush(stderr);
            return 0;
        }

        // Tokenize the command line input
        int argc = 0;
        arguments[argc] = strtok(command_line, delimiters);
        while (arguments[argc] != NULL) {
            argc++;
            arguments[argc] = strtok(NULL, delimiters);
        }

        // Handle built-in commands
        if (strcmp(arguments[0], "cd") == 0) {
            if (chdir(arguments[1]) != 0) {
                perror("cd failed");
            }
            continue;
        } else if (strcmp(arguments[0], "echo") == 0) {
            int i;  // Declare variable outside the loop
            for (i = 1; i < argc; i++) {
                printf("%s ", arguments[i]);
            }
            printf("\n");
            continue;
        } else if (strcmp(arguments[0], "exit") == 0) {
            printf("Exiting shell...\n");
            exit(0);
        } else if (strcmp(arguments[0], "env") == 0) {
            char **env;  // Declare variable outside the loop
            for (env = environ; *env != NULL; env++) {
                printf("%s\n", *env);
            }
            continue;
        } else if (strcmp(arguments[0], "setenv") == 0) {
            if (setenv(arguments[1], arguments[2]) != 0) {
                perror("setenv failed");
            }
            continue;
        }

        // Handle background processes
        int background = 0;
        if (strcmp(arguments[argc - 1], "&") == 0) {
            background = 1;
            arguments[argc - 1] = NULL; // Remove '&' from arguments
        }

        // Fork a child process to execute the command
        pid_t pid = fork();
        if (pid == 0) {
            // In child process: Execute the command
            if (execvp(arguments[0], arguments) == -1) {
                perror("execvp failed");
            }
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            // Forking failed
            perror("fork failed");
        } else {
            // In parent process: Wait for child unless it's a background process
            if (!background) {
                wait(NULL);
            }
        }
    }

    return 0; // This point will never be reached
}
