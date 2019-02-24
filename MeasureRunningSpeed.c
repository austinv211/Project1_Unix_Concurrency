#include <time.h>
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h>

void runProgram(char* programName, char* outputName);

int main() {

    runProgram("./MyCompress", "./testFiles/measureOutput1.txt");
    runProgram("./ParFork", "./testFiles/measureOutput2.txt");
    runProgram("./ParThread", "./testFiles/measureOutput3.txt");

    return 0;
}

void runProgram(char* programName, char* outputName) {

    clock_t time;

    char* args[] = {programName, "./testFiles/testFile.txt", outputName, NULL};

    time = clock();

    //run our first output file
    if (fork() == 0) {
        printf("\n*** Program Output for Program: %s ****\n", programName);
        execvp(args[0], args);

        fprintf(stderr, "Issue calling arg\n"); 
    }
    else {
        wait(NULL);
        time = clock() - time;
        double time_taken = ((double)time)/CLOCKS_PER_SEC;

        printf("\n%s took %f seconds to execute\n", programName, time_taken);
    }
}