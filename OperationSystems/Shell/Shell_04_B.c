//--------------------------------------------
// NAME: Божидар Захов
// CLASS: 11Б
// NUMBER: 4
// PROBLEM: #2
// FILE NAME: shell.c
// FILE PURPOSE:
// Peaлизация на прост Shell
//<><><><><><><><><><><><><><><><><><><><><><><>
//---------------------------------------------
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

//|------------------------------|

#define MAX_TOKS 1002
#define DELIMITERS " \t" // space and tab
#define MAX_STRING 10000
//|------------------------------|

///bin/ls -l /usr/include

char** parseString(char *line){//char* line, char*** argv) {
//--------------------------------------------
// FUNCTION: parseString() 
// Вмъква в масив от стрингове всички части на
// подадения стринг, разделени по празно място 
// PARAMETERS:
// line - C string - с този стринг се работи
//----------------------------------------------
  	char** argv;
  	char* buffer;
  	int i=0,argc = 1;
  	for (i=0;;i++)
	{
    	if (line[i] == '\n' ) {
    		line[i] =  '\0';
			break;
		}
	}
	buffer = (char*) malloc(strlen(line) * sizeof(char));
  	
  	strcpy(buffer,line);
  	
  	(argv) = (char**) malloc(MAX_TOKS * sizeof(char**));
	
  	(argv)[0] = line;
	
	(argv)[argc++] = strtok(argv[0], DELIMITERS);
	while ((( (argv)[argc] = strtok(NULL, DELIMITERS)) != NULL) &&
		(argc < MAX_TOKS)) ++argc;
	
	return argv;
}
void execute(char * const ** argv){
//--------------------------------------------
// FUNCTION: еxecute()
// създава нови процеси и ги изпълнява в зависимост
// от подадения масив от C strings
// PARAMETERS:
// argv - това е подадения масив от C strings
// тук са аргументите за стартирането на програмите
//----------------------------------------------		
		int status;
		pid_t childPid, wpid;
		////////////////////
		childPid = fork();
		if( childPid < 0) { //error
      		perror("fork");
      	}
		if (childPid == 0)
		{
			
			if(execv(*argv[0], *argv) == -1) {
        		perror("execv");
        		exit(EXIT_FAILURE);
     		}
		}else
		  {
			do{
				wpid = waitpid(childPid, &status, WUNTRACED);
        	} while (!WIFEXITED(status) && !WIFSIGNALED(status) && wpid >0);
		  }
}

int main() {
//--------------------------------------------
// FUNCTION: main()
// Началната точка на програмата
//
//----------------------------------------------		
	char str[MAX_STRING];
	int  i;
	printf("Input:\n");  	
	do{
		fgets(str, sizeof(str),stdin);
 		char * const* B =parseString( str );
		if (strcmp(B[0], "exit") == 0)	break;
		if (strlen(B[0]) > 1 )
		{
			execute(&B);
		}
		for (i = 1; B[i] != '\0'; ++i) {
			//printf("\n[%d] = %s",i,B[i]);
		}
		
		printf("\nInput:\n");	
	}while(1);
	return 0;
}
