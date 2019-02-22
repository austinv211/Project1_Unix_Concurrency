#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//define our max size and current working directory max size
#define MAX_SIZE 100
#define CWD_MAX_SIZE 200

//define a struct to represent a command to pass to execvp
struct command
{
    char **argv;
};

// method for spawning processes, takes an input and output file descriptor, and a cmd struct
int create_process(int in, int out, struct command *cmd)
{
    // get a variable to keep track of the pid
    pid_t pid;

    //fork a child process
    pid = fork();

    //catch pid error condition
    if (pid < 0) {
        perror("Fork Error");
        return 1;
    }
    //child process
    else if (pid == 0)
    {
        //if the input file descriptor is not the std_in make the std_in our in file descriptor with dup2
        if (in != STDIN_FILENO)
        {
            dup2(in, STDIN_FILENO);

            //close the in file descriptor since not needed
            close(in);
        }

        // if the output file descriptor is not the std_out make the std_out our out file descriptor with dup2
        if (out != STDOUT_FILENO)
        {
            dup2(out, STDOUT_FILENO);

            //close the out file descriptor since not needed
            close(out);
        }

        // call execvp on our cmd, use the arrow operator to get that argv from the struct cmd points to
        execvp(cmd->argv[0], cmd->argv);

        perror(cmd->argv[0]);

        return -1;
    }
    else {
        //parent process
        wait(NULL);

        //return 0
        return 0;
    }

    // return 1 for an error condition
    return -1;
}

//fork_pipes function to take a number n (pipes_to_produce) and a structure (cmds to run)
int fork_pipes(int n, struct command *cmd)
{
    //get an integer i for looping and keeping track of end
    int i;

    // define in to keep track of the reading end for children spawned
    int in;

    //define a fd array to use for piping
    int fd[2];

    //set in for the first process to be the original file descriptor
    in = 0;

    //loop through and create pipes, and spawn processes
    for (i = 0; i < n - 1; ++i)
    {
        //create a pipe from our file descriptor
        pipe(fd);

        // spawn a process with the input from the previous iteration and the writing end of the pipe
        // this will call the next command in the list using cmd + i
        create_process(in, fd[1], cmd + i);

        // close the writing end of the pipe
        close(fd[1]);

        //set in to be the reading end of the pipe for the next child to use
        in = fd[0];
    }

    //set stdin to be the read end of the previous pipe, and the output to be the original file descriptor
    if (in != 0)
        dup2(in, 0);

    // call the last command using the current process, this should be the child process created in our main method
    execvp(cmd[i].argv[0], cmd[i].argv);
        
    perror(cmd[i].argv[0]);

    return -1;
}

int main()
{
    //create a variable to store the string typed from the command
    char cmd[MAX_SIZE];

    //create a variable to store the pid for starting our fork_pipes process
    pid_t pid;

    while ((strcmp(cmd, "exit")) != 0)
    {

        //get the current working directory
        char cwd[CWD_MAX_SIZE];

        //catch error condition with the current working directory
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            perror("Error with getting the current working directory.");
            return -1;
        }

        //get the command from the user
        printf("DupShell:%s$ ", cwd);
        fgets(cmd, MAX_SIZE, stdin);

        //get a pointer to the position for the newline char
        char *pos;

        //if the return of the first occurence of the character is not a null pointer, set the value at the pointers address to be the terminating char
        if ((pos = strchr(cmd, '\n')) != NULL)
            *pos = '\0';

        //get delimeters for the whitespace and the bar character
        char delim[] = " ";
        char bar[] = "|";

        // get a pointer to the first instance of the delimeter
        char *bar_ptr = strtok(cmd, bar);

        //define our argv to be an array of pointers;
        char *bar_split[11];
        char *args[2][10];

        //initialize a counter to keep track of the splits from the "|" tokenize
        int pipe_count = 0;

        //while our strtok pointer is not null, set our argv at the number of words to equal to the string represented by the break inbetween the terminating character
        while (bar_ptr != 0)
        {

            //add the ptr for the string into the bar split array
            bar_split[pipe_count] = bar_ptr;

            //get our new pointer value from strtok's last remembered terminator point to the next delimeter
            bar_ptr = strtok(NULL, bar);

            //increase the count
            pipe_count++;
        }

        //set the end of the bar_split to be null based on input recieved
        bar_split[pipe_count] = NULL;

        //for each string after splitting by the '|' character
        for (int i = 0; i < pipe_count; i++)
        {

            //initialize a counter
            int count = 0;

            //get a pointer to the first string up to a whitespace char
            char *ptr = strtok(bar_split[i], delim);

            //while the pointer is not null
            while (ptr != 0)
            {

                //fill our args with the string
                args[i][count] = ptr;

                //increment the pointer
                ptr = strtok(NULL, delim);

                //increase the count
                count++;
            }

            //set the end of the args to be null for passing to execvp
            args[i][count] = NULL;
        }

        //if the cmd given does not equal "exit"
        if (strcmp(cmd, "exit") != 0)
        {

            // fork a child process to run fork_pipes
            pid = fork();

            //catch a fork error
            if (pid < 0)
            {
                perror("Fork Error");
                return 1;
            }
            //child process
            if (pid == 0)
            {

                //define our structure array to store our commands
                struct command cmd[pipe_count];

                //fill the structure with the generated args
                for (int i = 0; i < pipe_count; i++)
                {
                    cmd[i].argv = args[i];
                }

                //call fork_pipes with the cmd array, and the number of pipes we need to make
                if (fork_pipes(pipe_count, cmd) == -1) {
                    break;
                }
            }
            //parent process, wait for child to complete
            else
            {
                wait(NULL);
            }
        }
    }

    return 0;
}
