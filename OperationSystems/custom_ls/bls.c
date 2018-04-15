//--------------------------------------------------------------
// NAME: Божидар Захов
// CLASS: 11Б
// NUMBER: 4
// PROBLEM: #4
// FILE NAME: bls.c
// FILE PURPOSE:
// Реализация на ls  
//--------------------------------------------------------------


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

int FileList[100]; // can be 0 - options, 1 - received file and 2+ - defaut - current directory

int IsHiddenOn = 0;
int IsDetailOn = 0;
int IsRecursiveOn = 0;

//-----------------------------------------------------------
// FUNCTION: printfPrermisions()
// Принтира Достъпите
// PARAMETERS:
// mode_t mode съхраняваща данните 
//-----------------------------------------------------------
void printfPrermisions(mode_t mode){
	int i;
	
	S_ISDIR(mode) ? printf("d") : printf("-");
	
	for (i=0; i < 3; i++) {
	
		mode & (S_IREAD  >> i*3) ? printf("r") : printf("-");
        mode & (S_IWRITE >> i*3) ? printf("w") : printf("-");
        mode & (S_IEXEC  >> i*3) ? printf("x") : printf("-");
    }
}
//-----------------------------------------------------------
// FUNCTION: typeOfFile()
// Определя типа на подадения Файл
// PARAMETERS:
// mode_t mode 
//-----------------------------------------------------------
char typeOfFile(mode_t mode)
{
    switch (mode & S_IFMT) {
    	case S_IFREG:    // обикновен файл - ’-’
        	return('-');
    	case S_IFDIR:    // директория - ’d’
    	    return('d');
    	case S_IFBLK:	 // блоково устройство - ’b’	
    	    return('b');
    	case S_IFCHR:    // символно устройство - ’c’
    	    return('c');
    	case S_IFIFO:    // програмен поток - ’p’
    	    return('p');
    	case S_IFLNK:    // символна връзка - ’l’
    	    return('l');
    	case S_IFSOCK:   // Socket - 's'
    	    return('s');
    }
    return('?');
}
//-----------------------------------------------------------
// FUNCTION: ls()
// Основната Функционалност на програмата
// PARAMETERS:
// mode_t mode 
//-----------------------------------------------------------
void ls(const char name[]){
    DIR *dp = NULL;
    struct dirent *dptr = NULL;
    struct stat file_info;
    unsigned int count = 0;
	char buf[256];
    
    dp = opendir(name);
    if(dp == NULL)
    {
        printf("\n ERROR : Could not open the working directory\n");
        exit(-1);
    }
	
	for(count = 0; (dptr = readdir(dp)) != NULL ; count++)
    {
        if (IsHiddenOn != 1 && dptr->d_name[0] == '.'){ //if is not hidden      is ok now
            count--;
            continue;
        }
        
   		snprintf(buf, sizeof buf, "%s/%s", name, dptr->d_name);
   			
   		//printf("\n%s\n",buf);
   		if ( (stat(buf, &file_info) ) != 0 ){
        	printf("Permission Denied\n");
        	continue;
       	}
         
        if (IsDetailOn){ // if found -l
        	printfPrermisions(file_info.st_mode); 
        	
    
        	printf(" %s\n",dptr->d_name);
        	
        }else {
        	printf("%c %s \n",typeOfFile(file_info.st_mode),dptr->d_name);
        }
        
        if (IsRecursiveOn && S_ISDIR(file_info.st_mode)){
        	char new[256];
			        	
        	ls(new);
        }
    }
    printf("\nTotal: %u \n", count);
}

//-----------------------------------------------------------
// FUNCTION: Options()
// Вдига флаговете за различните Опции
// PARAMETERS:
// argc
// argv
//-----------------------------------------------------------
void Options(int argc,char *argv[]){
    int i,j;
    for (i = 1; i < argc; i++) // up flags ! 
    {
        if (argv[i][0] == '-' ){ //if start with -
            if (i == argc-1 && argc < 3){
            	FileList[i] = 2; // to current directory, if haven't given directory	
            }else{
	            FileList[i] = 0; // only options
            }
            for (j  = 0; argv[i][j] != '\0'; j ++) // looking for commands
            {
                //printf(">%c " ,argv[i][j]);
                if (argv[i][j] == 'a'){
                    IsHiddenOn = 1;
                    //printf("(%d)",IsHiddenOn);
                }
                if (argv[i][j] == 'R' || argv[i][j] == 'r'){
                    IsRecursiveOn = 1;
                }
                if (argv[i][j] == 'l'){
                    IsDetailOn = 1;
                }
            }
            
        }else{
            FileList[i] = 1;
        }
    }
    printf("Recursive: %d, Hidden: %d, Detail: %d \n",IsRecursiveOn, IsHiddenOn, IsDetailOn );
}
 
//-----------------------------------------------------------
// FUNCTION: main()
// Извиква Основните Функции 
// PARAMETERS:
// argc
// argv
//----------------------------------------------------------- 
int main(int argc,char *argv[])
{       int i;
        Options(argc,argv);
        printf("\n");
        
        for (i = 0; i < argc; i ++)
        {
        	if (FileList[i] == 1){
        		printf("Directory - %s:\n",argv[i]);
        		ls(argv[i]);
        	}else if (FileList[i] || argc < 2) { // same as FileList[i] == 2 || argc < 2
        		printf("Directory - %s:\n",argv[i]);
        		ls(".");
       		}
		}
	return 0;
}
