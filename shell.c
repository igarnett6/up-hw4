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

int main()
{
    while(true) {
        printf("(╯°益°)╯彡┻━┻ ");
        char command[4096];
        fgets(command, 4096, stdin);
        int len = strlen(command);
        if (command[len-1] == '\n') command[len-1] = '\0';
        if(fork() == 0){
          execlp(command, command, NULL);
          perror("Failed to exec");
          _exit(0);
        }
        else{
          pid_t cpid = wait(NULL);
        }
    }
}
