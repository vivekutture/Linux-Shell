#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#define MAX_LEN 1024

int main() 
{

	pid_t pid; // process id
	char args[MAX_LEN]; // takes user input
	char *tok; // stores each seperated word
	char *arr[MAX_LEN]; // stores each seperated word
	char path[MAX_LEN]; // stores command path
	system("clear"); // clears the terminal
	printf("WELCOME!!! to My Shell\n\nMy name is Vivek Utture\n\nI've created this Linux Shell where basic Linux Commands can be executed\n\nDownload the source code from https://github.com/vivekutture/Linux-Shell.git\n\n\033[1mTo return to the Orignal Shell enter \033[3m\033[4mEXIT\033[m \n\n");
	while (1) 
	{
		printf("\033[1;32mA79 - Vivek Utture:\033[1;34m~\033[1;32m$\033[m "); // shell prompt where \033 is Esc character and ASCII 27 is followed by [, then zero or more numbers separated by ; describe the color and format to switch to from that point onwards and finally the letter m.
		fgets(args,MAX_LEN,stdin); // takes a whole line as a input untill "Enter" is pressed 
		int len=strlen(args); // calculates and stores length of the given command
		if(len==1)
		{
			continue; // even if command is not enterd and "Enter" is pressed then the execution will continue with next iteration
		}
		args[len-1]='\0'; // tells the end of the given command
		tok=strtok(args," "); // seperates each word from given command
		int i=0;
		while(tok!=NULL) // transferres each word from token to array untill token reaches to NULL 
		{
			arr[i++]=tok;
			tok=strtok(NULL," ");
		}
		arr[i]=NULL; // tells the end of the array
		if(strcmp(arr[0],"exit")==0) // if command is exit then loop will break, execution will terminate and control goes back to original shell
		{
			break;
		}
		strcpy(path,"/bin/"); // copies common path where basic Linux Commands exists 
		strcat(path,arr[0]); // merges command with path
		if(access(path,F_OK)==0) // finds command exist at specified path or not
		{
			pid=fork(); // child process creation
			if(pid==0) 
			{	
				//child process		
				if(execvp(path,arr)!=0) // checks the given command with arguments executes successfully or not if executes successfully returns 0 otherwise else
				{
					perror("\nCommand not Executed Successfully!"); // throws error
					sleep(5); // delay for a specified amount of time
					system("clear"); // clears the terminal
				}
			}
			else if(pid<0) // checks any process cretaed or not or any process exists or not
			{
				printf("\nProcess doesn't exist\nExiting...");
				break;			
			}
			else
			{
				// parent process
				wait(0); // wait for process to change state
			}
		}
		else // if command not found at specified path then this block will execute
		{
			perror("\nCommand not Found "); // throws error
			sleep(5); // delay for a specified amount of time
			system("clear"); // clears the terminal
		}
	}
	exit(0); // process termination
}

