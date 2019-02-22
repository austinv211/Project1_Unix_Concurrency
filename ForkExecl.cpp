#include<iostream>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
using namespace std;

int main(){

    //Declarion(s)
    pid_t pid;
    pid = fork();

    //Failed fork
    if(pid < 0){
        cout << stderr << "Fork failed exiting program...\n";
    }
    
    //Child Process
    else if (pid == 0){
        cout << "Child is starting compression...\n";

        //Execute line command usage to compress
		execl("/home/jaguil/Desktop/Cs4440/projects/project1/myCompress", 
			  "./myCompress", "source.txt", "destination.txt", NULL);
	}
    
    //Parent Prosses
    else{
        cout << "Parent is waitng in child to compress...\n";
        wait(NULL);
        cout << "Parent is now finished waiting\n";
    }

    //Return Success
    return 0;
}