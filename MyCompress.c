// C program to demonstrate use of fork() and pipe() 
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
void MyCompress(char[], char[]);

int main() {
    char inputData[] = "01111111111111111111111110";

    char value[200] = "";
    MyCompress(inputData, value);

    printf("Got Value: %s\n", value);
}

void MyCompress(char inputData[], char resultReplaced[]) {
    //create a counter to keep track of the number of sequential values found in a sequence
    int counter = 1;

    printf("Input Data: %s\n", inputData);

    //to keep track of the start and end of a sequence of repeating values
    int startIndex = 0;
    int endIndex = -1;

    //result array of chars
    char result[200] = "";

    //loop through the sequence
    for (int i = 0; i < strlen(inputData); i++) {
        char currentChar = inputData[i];
        char nextChar = inputData[i + 1];

        printf("Current Char: %c\n", currentChar);

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

        printf("Result: %s\n", result);
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

    printf("%s\n", resultReplaced);
}