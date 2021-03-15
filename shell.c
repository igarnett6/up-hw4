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
#include <stdlib.h> //?malloc
#include <limits.h> //realpath

int main()
{
    while(true) {
        char pwd[4096];
        realpath(".", pwd);
        printf("╭─%s -> [PID: %d]\n", pwd, getpid());
        printf("╰─(╯°益°)╯彡┻━┻ ");
        char command[4096];
        fgets(command, 4096, stdin);
        int len = strlen(command);
        int changeDir = 0;
        if((strncmp(command, "exit", 4)) == 0){
          exit(0);
        }
        if((strncmp(command, "cd", 2)) == 0){
          changeDir = 1;
        }
        if (command[len-1] == '\n') command[len-1] = '\0';
        if(changeDir == 1){
          char *cdCmd = strtok(command, " ");
          char *newDir = strtok(NULL, " ");
          chdir(newDir);
        }
        else if(fork() == 0){
          char *token = strtok(command, " ");
          char *util = token;
          char *args[4096];
          args[0] = token;
          int i = 1;
          while((token = strtok(NULL, " ")) != NULL){
            args[i] = token;
            i++;
          }
          execvp(args[0], args);
          perror("Failed to exec");
          _exit(0);
        }
        else{
          pid_t cpid = wait(NULL);
        }
    }
}
