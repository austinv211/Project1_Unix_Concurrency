#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_SIZE 100
#define CWD_MAX_SIZE 200

int main()
{
    //create a variable to store the string typed from the command
    char cmd[MAX_SIZE];

    //create a variable to store the pid
    pid_t pid;

    while ((strcmp(cmd, "exit")) != 0) {

        //get the current working directory
        char cwd[CWD_MAX_SIZE];

        //catch error condition with the current working directory
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("Error with getting the current working directory.");
            return 1;
        }

        //get the command from the user
        printf("MoreShell:%s$ ", cwd);
        fgets(cmd, MAX_SIZE, stdin);

        //get a pointer to the position for the newline char
        char *pos;

        //if the return of the first occurence of the character is not a null pointer, set the value at the pointers address to be the terminating char
        if ((pos=strchr(cmd, '\n')) != NULL)
            *pos = ' ';

        //set our delimeter to be the whitespace
        char delim[] = " ";

        // get a pointer to the first instance of the delimeter
        char* ptr = strtok(cmd, delim);

        //define our argv to be an array of pointers;
        char* argv[11];

        //initialize a word count to 0
        int count = 0;

        //while our strtok pointer is not null, set our argv at the number of words to equal to the string represented by the break inbetween the terminating character
        while (ptr != 0) {
            //set the argv at count to equal the pointer
            argv[count] = ptr;

            //get our new pointer value from strtok's last remembered terminator point to the next delimeter
            ptr = strtok(NULL, delim);

            //increase the count
            count++;
        }
        
        //set the final argv pointer to point to NULL, this makes our array of pointers null terminated
        argv[count] = NULL;

        //if the the cmd is not equal to exit
        if (strcmp(cmd, "exit") != 0) {

            //fork a child process
            pid = fork();

            //catch PID error
            if (pid < 0) {
                printf("PID Error");
            }
            //Child process, calls the command using execvp
            else if (pid == 0) {
                //call execvp with the args
                if (execvp(cmd, argv) == -1) {

                    //have an error condition
                    printf("\"%s\" is not a recognized command or file.\n", cmd);

                    return -1;
                }
            }
            //parent process, wait for the child process to complete
            else {
                wait(NULL);
            }

        }

        //flush the stdout
        fflush(stdout);

    }

    return 0;
}