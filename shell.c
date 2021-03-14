/*
  Minimal Shell
  "Looping":
     Displays a prompt
     Takes in a command
     Executes the command
  Since it execs without forking, it can only run a single command.
  Also doesn't tokenize the input...
 */

#include <stdio.h>   // printf, fgets
#include <string.h>  // strlen
#include <unistd.h>  // execlp
#include <stdbool.h> // true
#include <sys/wait.h> //wait
#include <stdlib.h> //?

int main()
{
    while(true) {
        printf("[PID: %d]", getpid());
        printf("(╯°益°)╯彡┻━┻ ");
        char command[4096];
        fgets(command, 4096, stdin);
        int len = strlen(command);
        if (command[len-1] == '\n') command[len-1] = '\0';
        if(fork() == 0){
          char *token = strtok(command, " ");
          char *util = token;
          char *args[4096];
          args[0] = token;
          int i = 1;
          while((token = strtok(NULL, " ")) != NULL){

            args[i] = token;
            // write(1, "New arg added: ", 16);
          }
          // write(1, args[0], 4096);
          // write(1, "\n", 1);
          // write(1, args[1], 4096);
          // write(1, "\n", 1);
          // write(1, args[2], 4096);
          // write(1, "\n", 1);
          // execlp(util, args[1], NULL);
          execvp(args[0], args);
          perror("Failed to exec");
          _exit(0);
        }
        else{
          pid_t cpid = wait(NULL);
        }
    }
}
