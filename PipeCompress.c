// C program to demonstrate use of fork() and pipe() 
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h>
#define MAX_SIZE 100000
//prototype MyCompress
void MyCompress(char[], char[]);
  
int main(int argc, char* argv[]) 
{ 

    //determine if the user entered the correct number of arguments
    if (argc < 2) {
        printf("\nARG ERROR: Must provide input FileName in arguments\n");
        return 1;
    }
    else if (argc > 2) {
        printf("\nARG ERROR: Too many arguments provided\n");
        return 1;
    }

    //We use one pipe to read from file then send and compress and write to output file
    int fd1[2];  // Used to store two ends of first pipe 

    //create a variable to save the pid
    pid_t pid;
  
    //check for pipe error
    if (pipe(fd1)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    }

    //fork a child process
    pid = fork(); 
  
    //check for fork() error
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

        // get the filename from the args
        char* fileName = argv[1];

        //open the file for a file pointer
        FILE* fp = fopen(fileName, "r");

        //create a str buffer and a max file size string
        char str[128];
        char input_str[MAX_SIZE] = "";

        //check if the file is null
        if (fp == NULL){
            printf("Could not open file %s",fileName);
            return 1;
        }

        //read from the file and add to our total file string
        while (fgets(str, 128, fp) != NULL)
            strcat(input_str, str);

        //write the read data to the pipe
        write(fd1[1], input_str, strlen(input_str)+1);

        //close the writing end of the pipe
        close(fd1[1]); 
    } 
  
    // child process 
    else
    { 
        // Close writing end of pipe
        close(fd1[1]);
  
        // Read a string using first pipe 
        char read_str[129];
        char read_sequences[MAX_SIZE];

        //read from the pipe and add to the total read string
        while (read(fd1[0], read_str, 128) > 0) {  
            strcat(read_sequences, read_str);
        }

        // get a pointer to our read string data
        char* data = read_sequences;

        //set an int for reading the separate strings from the file
        int offset;

        //get reference to output file
        FILE* op = fopen("output.txt", "w");

        // read each sequence from the data pointer and then compress the line using the
        // MyCompress() function
        while (sscanf(data, "%s%n", read_str, &offset) == 1) {
            
            //set our output str to send to MyCompress
            char output_str[128] = "";

            // move the data pointer forward
            data += offset;
            
            // compress the line
            MyCompress(read_str, output_str);

            // print the result after compression
            fprintf(op, "%s\n", output_str);
        }
  
        //close the output file
        fclose(op);
        
        // Close reading end 
        close(fd1[0]);
  
        // child process complete
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

    //loop through the sequence and sepearate sequences using the | character
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

    // set our delimeter
    char delim[] = "|";

    // get a pointer to the string up to the first delimeter
    char* ptr = strtok(result, delim);

    // while the pointer is not null, read each sequence, if the sequence is larger than 16,
    // compress it
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
    }
}
