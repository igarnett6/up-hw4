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
        int redirIO = 0;
        char *sourceFile;
        char pwd[4096];
        realpath(".", pwd);
        printf("╭─%s -> [PID: %d]\n", pwd, getpid());
        printf("╰─(╯°益°)╯彡┻━┻ ");
        char *command = calloc(1, 4096);
        fgets(command, 4096, stdin);
        if((sourceFile = strstr(command, " < ")) != NULL){
          redirIO = 1;
          sourceFile = sourceFile+3;
          close(0);
          int fd = open(sourceFile, "O_RDONLY");
          if(fd != 0){
            fprintf(stderr, "failed to open %s \0\n", sourceFile);
            printf("fd:\t%d\n", fd);
            exit(1);
          }
          printf("fd:\t%d\n", fd);
          fgets(command, 4096, stdin);
          printf("command: %s\n", command);
          continue;
        }
        int len = strlen(command);
        int changeDir = 0;
        if((strncmp(command, "exit", 4)) == 0){
          exit(0);
        }
        if((strncmp(command, "cd", 2)) == 0){
          changeDir = 1;
        }
        // printf("redirIO:\t%d\n", redirIO);
        // printf("sourceFile: %s\n", sourceFile);
        if (command[len-1] == '\n') command[len-1] = '\0';
        if(changeDir == 1){
          strtok(command, " ");
          char *newDir = strtok(NULL, " ");
          chdir(newDir);
          continue;
        }
        if(fork() == 0){
          char *token = calloc(1, 4096);
          token = strtok(command, " ");
          // else{
          // }
          char *args[4096];
          args[0] = token;
          int i = 1;
          while((token = strtok(NULL, " ")) != NULL){
            args[i] = token;
            i++;
          }
          execvp(args[0], args);
          perror("Failed to exec");
          free(token);
          // if(redirIO == 1){
          //   close(0);
          //   int fd = open(sourceFile, "O_RDONLY");
          //   if(fd != 0){
          //     _exit(1);
          //   }
            // fputs(command, stdin);
            // write(1, "\ncommand: ", 10);
            // write(1, command, 20);
            // write(1, "\n", 1);
          // }
          _exit(0);
        }
        else{
          wait(NULL);
          // perror("No children");
        }
        free(command);
    }
}
