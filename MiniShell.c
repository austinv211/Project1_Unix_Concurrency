#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_SIZE 100

int main()
{
    //create a variable to store the string typed from the command
    char cmd[MAX_SIZE];

    //create a variable to store our pid
    pid_t pid;

    while ((strcmp(cmd, "exit")) != 0) {
        
        //print "Enter a linux command" and get the result
        printf("MiniShell$ ");
        fgets(cmd, MAX_SIZE, stdin);

        //get a pointer to the position for the newline char
        char *pos;

        //define our argv to be an array of pointers;
        char* argv[2];
        
        if ((pos=strchr(cmd, '\n')) != NULL)
            *pos = '\0';

        //set our argv[0]
        argv[0] = cmd;
        
        //set the final argv pointer to point to NULL, this makes our array of pointers null terminated
        argv[1] = NULL;

        //if the cmd is not equal to exit
        if (strcmp(cmd, "exit") != 0) {

            //fork a child process
            pid = fork();

            //catch pid error condition
            if (pid < 0) {
                printf("PID Error");
            }
            //child process condition
            else if (pid == 0) {
                //call execvp with the args
                if (execvp(cmd, argv) == -1) {
                    //have an error condition
                    printf("\"%s\" is not a recognized command or file.\n", cmd);

                    return -1;
                }
            }
            //parent process, wait for child process to complete
            else {
                wait(NULL);
            }
        }

        //flush the stdout
        fflush(stdout);
    }

    return 0;
}