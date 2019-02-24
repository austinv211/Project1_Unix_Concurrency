#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//method to parse the input file
int ParseFile(FILE* fp, FILE* op, char fileName[]) {

    //if the input file is equal to NULL, exit the method
    if (fp == NULL) {
        return -1;
    }

    //initialize our sequence, count, startIndex, endIndex, and output File
    char sequence[128]; //used to store the sequence found in the input file
    int count = 0; //used to print a count of sequences found
    int startIndex = -1; //used to keep track of the start of the compression value
    int endIndex = -1; //used to keep track of the end of the compression value

    //while not at the end of the file in our input file
    while (!feof(fp)) {
        bool printed = false;

        //if we do not receive one item from the fscanf, break the loop
        if ((fscanf(fp, "%s", sequence)) != 1) {
            break;
        }

        //increase the count for display purposes
        count++;

        //loop through the sequence to get the compressed values
        for (int i = 0; i < strlen(sequence); i++) {

            //look for a plus or a minus
            if (sequence[i] == '+' || sequence[i] == '-') {

                //if our start index is not initialized, set the start
                if (startIndex == -1) {
                    startIndex = i;
                }
                //else our end index should be set to i
                else {
                    endIndex = i;
                }

                //if our end index has a non-negative 1 value, get the decimal and create the output
                if (endIndex != -1) {

                    //set a variable for our number we find
                    int dec = 0;

                    //translate the characters into an int value
                    for(int j = startIndex + 1; j < endIndex; j++) {
                        dec = dec * 10 + ( sequence[j] - '0' );
                    }
                    
                    //if the start index is a -, print the correct number of 0's
                    if (sequence[startIndex] == '-') {
                        for ( int k = 0; k < dec; k++) {
                            fprintf(op, "%s", "0");
                        }
                    }

                    //if its a plus, print the correct number of 1's
                    else if (sequence[startIndex] == '+') {
                        for ( int k = 0; k < dec; k++) {
                            fprintf(op, "%s", "1");
                        }
                    }

                    //reset the start and end index
                    endIndex = -1;
                    startIndex = -1;
                }
            }
            else { //else if the char is not a + or a -

                //if the start index and the end index are both reset, print the character
                if (startIndex == -1 && endIndex == -1) {
                    fprintf(op, "%c", sequence[i]);
                }
            }
        }
        
        // print the newline character
        fprintf(op, "\n");
    }

    //finally close our input and output file
    fclose(op);
    fclose(fp);

    //return a 0 for all is well
    return 0;

}

int main(int argc, char* argv[]) {
    //create a file pointer for input and output
    FILE* fp;
    FILE* op;

    //if we have more than 1 argc, parse the file
    if (argc == 3) {

        //get a reference to the input file
        char* fileName = argv[1];

        // get a reference to the output file
        char* outputFile = argv[2];

        //open the given file
        fp = fopen(fileName,"r");

        //open the output file
        op = fopen(outputFile, "w");

        //print the user entered the filename
        printf("INPUT: %s\n", fileName);

        //attempt to parse the file
        if (ParseFile(fp, op, fileName) == -1) {
            perror("Error Parsing File");
            return -1;
        }

        //print the path to the output file
        printf("Data outputted to: %s\n", outputFile);
    }
    else {
        perror("ARG ERROR: You must specify the input file then output file name as args\n");
        return -1;
    }

    //return 0 for all is well
    return 0;
}