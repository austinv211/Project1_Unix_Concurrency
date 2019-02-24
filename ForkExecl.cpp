#include<iostream>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
using namespace std;

int main (int argc, char* argv[]) 
{

    //get representations for the commandline args
    char* fileName;
    char* outputFileName;

    //get the number of args
    if (argc == 3) {
        fileName = argv[1];
        outputFileName = argv[2];
    }
    else {
        cout << stderr << "You must specify an input file name then output file name as commandline args\n";
    }
    
    //Declarion(s)
    pid_t pid;
    pid = fork();

    //Failed fork
    if(pid < 0)
    {
        cout << stderr << "Fork failed exiting program...\n";
    }
    
    //Child Process
    else if (pid == 0)
    {
        cout << "Child is starting compression...\n";

        //Execute line command usage to compress
		execl("./MyCompress", "./MyCompress",  fileName, outputFileName);
	}
    
    //Parent Prosses
    else
    {
        cout << "Parent is waitng in child to compress...\n";
        wait(NULL);
        cout << "Parent is now finished waiting\n";
    }

    //Return Success
    return 0;
}