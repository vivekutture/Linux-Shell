#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#define MAX_LEN 100

int main() 
{
	char str[MAX_LEN]; // takes user input
	char *tok; // used to seperate and store each word from given command 
	char *args[MAX_LEN]; // stores each seperated word as arguments
	system("clear"); // clears the terminal
	printf("WELCOME!!! to My Shell\n\nMy name is Vivek Utture\n\nI've created this Linux Shell where basic Linux Commands can be executed\n\nDownload the source code from 'https://github.com/vivekutture/Linux-Shell.git'\n\n\033[1mTo return to the Orignal Shell enter \033[3m\033[4mexit\033[m \n\n"); // Here \033 is Esc character and ASCII 27 is followed by [, then zero or more numbers separated by ; describe the color and format to switch to from that point onwards and finally the letter m. (Here, '1' is for Bold,'3' is for Italic, '4' is for Underline & '\033[m' is to RESET every formatting.)
	while (1) 
	{
		memset(args,'\0',MAX_LEN); // sets the argument array with 'NULL' values simply 'Nullifies' the argument array
		printf("\033[1;32m ||| SHELL NAME ||| \033[1;34m~\033[1;32m\033[m$ "); // shell prompt where \033 is Esc character and ASCII 27 is followed by [, then zero or more numbers separated by ; describe the color and format to switch to from that point onwards and finally the letter m. (Here, '1' is for Bold,'32' is for Green Color for text, '34' is for Blue Color for text & '\033[m' is to RESET every formatting.)
		fgets(str,MAX_LEN,stdin); // takes a whole line as a input untill "Enter" is pressed 
		if(strcmp(str,"\n")==0) // even if command is not entered and "Enter" is pressed then the execution will continue with next iteration
		{
			continue;
		}
		int len=strlen(str); // calculates and stores length of the given command
		str[len-1]='\0'; // terminates the given command
		if(strcmp(str,"exit")==0) // if command is exit then loop will break, execution will terminate and control goes back to original shell
		{
			break;
		}
		tok=strtok(str," "); // seperates each word from given command
		int i=0;
		while(tok!=NULL) // transfers each word from token to array untill token reaches to NULL 
		{
			args[i++]=tok;
			tok=strtok(NULL," ");
		}
		pid_t pid=fork(); // child process creation
		if(pid==0) 
		{	
			//child process		
			if(execvp(args[0],args)!=0) // checks the given command with arguments executes successfully or not if executes successfully returns 0 otherwise else ('Syntax & Description' : int execvp(const char *file, char *const argv[]); The char *const argv[] argument is an array of pointers to null terminated strings that represent the argument list available to the new program. The first argument, by convention, should point to the file name associated with the file being executed. The array of pointers must be terminated by a null pointer.)
			{
				perror("\nCommand not Found "); // throws error
				sleep(2); // delay for a specified amount of time
				system("clear"); // clears the terminal
				exit(EXIT_FAILURE); //terminates the unsuccessful execution of a program

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
	exit(0); // program termination
}
