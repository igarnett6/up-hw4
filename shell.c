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
#include <fcntl.h> //O_RDONLY


int main()
{
    while(true) {
        char *sourceFile;
        char pwd[4096];
        realpath(".", pwd);
        printf("╭─%s -> [PID: %d]\n", pwd, getpid());
        printf("╰─(╯°益°)╯彡┻━┻ ");
        char *command = calloc(1, 4096);
        fgets(command, 4096, stdin);
        int len = strlen(command);
        if (command[len-1] == '\n') command[len-1] = '\0';
        if((sourceFile = strstr(command, " < ")) != NULL){
          sourceFile = sourceFile+3; //this only works @end, change to strtok
          close(0);
          int fd = open(sourceFile, O_RDONLY);
          if(fd == -1){
            perror("Failed to open \"sourceFile\"");
            exit(1);
          }
          printf("\nfd:\t%d\n", fd);
          if((command = fgets(command, 4096, stdin)) == NULL){
            perror("fgets returned NULL from stdin");
          }
          if (command[len-1] == '\n') command[len-1] = '\0';
          close(fd);
        }
        // printf("command:\t%s\n", command);
        if((strncmp(command, "exit", 4)) == 0){
          exit(0);
        }
        int changeDir = 0; //bool for if cd in stdin
        if((strncmp(command, "cd", 2)) == 0){
          changeDir = 1;
        }
        if(changeDir == 1){
          strtok(command, " ");
          char *newDir = strtok(NULL, " ");
          chdir(newDir);
          continue;
        }
        if(fork() == 0){
          char *token = calloc(1, 4096);
          token = strtok(command, " ");
          char *args[4096];
          args[0] = token;
          int i = 1;
          while((token = strtok(NULL, " ")) != NULL){
            args[i] = token;
            int argLen = strlen(args[i]);
            if (args[i][argLen-1] == '\n') args[i][argLen-1] = '\0';
            i++;
          }
          execvp(args[0], args);
          perror("Failed to exec");
          free(token);
          _exit(0);
        }
        else{
          if((wait(NULL)) == -1){
            perror("No children");
          }
        }
        free(command);
    }
}
