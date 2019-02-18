// C program to demonstrate use of fork() and pipe() 
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h>
void MyCompress(char[], char[]);
  
int main(int argc, char* argv[]) 
{ 
    //We use one pipe to read from file then send and compress and write to output file
    int fd1[2];  // Used to store two ends of first pipe 
  
    char input_str[] = "0111111111111111111111111";

    pid_t pid; 
  
    if (pipe(fd1)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    }

    pid = fork(); 
  
    if (pid < 0) 
    { 
        fprintf(stderr, "fork Failed" ); 
        return 1; 
    } 
  
    // Parent process 
    else if (pid > 0) 
    {
        // Close reading end of first pipe
        close(fd1[0]);

        char* fileName = argv[1];
        FILE* fp = fopen(fileName, "r");
        char str[128];
        char input_str[10000];

        if (fp == NULL){
            printf("Could not open file %s",fileName);
            return 1;
        }
        while (fgets(str, 128, fp) != NULL)
            strcat(input_str, str);

        write(fd1[1], input_str, strlen(input_str)+1);
        close(fd1[1]); 
    } 
  
    // child process 
    else
    { 
        close(fd1[1]);  // Close writing end of first pipe 
  
        // Read a string using first pipe 
        char read_str[128];

        while (read(fd1[0], read_str, 100) > 0) {  
            char output_str[128] = "";
            
            read_str[strlen(read_str)] = '\0';   // string ends with '\0'

            MyCompress(read_str, output_str);

            printf("%s\n", output_str);
        }
  
        // Close reading end 
        close(fd1[0]);
  
        exit(0); 
    }
}

void MyCompress(char inputData[], char resultReplaced[]) {
    //create a counter to keep track of the number of sequential values found in a sequence
    int counter = 1;

    //to keep track of the start and end of a sequence of repeating values
    int startIndex = 0;
    int endIndex = -1;

    //result array of chars
    char result[200] = "";

    //loop through the sequence
    for (int i = 0; i < strlen(inputData); i++) {
        char currentChar = inputData[i];
        char nextChar = inputData[i + 1];

        if (currentChar == nextChar) {
            int len = strlen(result);
            result[len++] = currentChar;
            result[len] = '\0';
        }
        else {
            char buf[3];
            sprintf(buf, "%c%c", currentChar, '|');
            strcat(result, buf);
        }
    }

    char delim[] = "|";

    char *ptr = strtok(result, delim);

    int count = 0;

    while(ptr != 0) {
        
        if (strlen(ptr) > 16) {
            char signChar = ptr[strlen(ptr) - 1];
            char buf[10];
            unsigned int len = (unsigned int)strlen(ptr);

            if (signChar == '0') {
                sprintf(buf, "-%u-", len);
            }
            else {
                sprintf(buf, "+%u+", len);  
            }
            strcat(resultReplaced, buf); 
        }
        else {
            strcat(resultReplaced, ptr);
        }


        ptr = strtok(NULL, delim);

        count++;
    }
}
