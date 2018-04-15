//--------------------------------------------------------------
// NAME: Божидар Захов
// CLASS: 11Б
// NUMBER: 4
// PROBLEM: #1
// FILE NAME: B_04_Bojidar_Zahov.c
// FILE PURPOSE:
// Тази програма изпечатва последните десет реда от файл,
//--------------------------------------------------------------

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int tail(int argc,char filename[]){
   //-----------------------------------------------------------
   // FUNCTION: tail
   //Тук е цялата функционалност на програмата
   //PARAMETERS:
   //argc - копие на стандартния argc- съдържа броя на файловете
   //filename - масив с копия от имената на файловете  
   //-----------------------------------------------------------

    int i=1,j=1;
	int fd;
	char buff[2];
	int adress[200];
     fd = open(filename, O_RDONLY);
	
	if (fd < 0)
	{
		perror("tail : cannot open for reading :open()");
		return 1;
	}
	while(1) {

		int status_read = read(fd, buff,1);
	          i++;
	          if (*buff=='\n') {
	             	j++;
	             	adress[j] = i;

	            //printf(">>%d>>\'\\n'\n",adress[j]);
	           }
	            //printf("J = %d\n", j);	
	            //printf("\nI = %d\n", i);
	            //printf("B = %c\n", *buff);
		if (status_read < 0) {
				perror("read()");
				return 1;
		}
		if (status_read == 0){
		     printf("<== %s ==>\n",filename);
		     const char *chars= "<==";
		     void *bb= "==>";
		     size_t sz= 3;
		     write(0,chars,sz);
		     write(1,filename,10);
		     write(0,bb,sz);
		     //printf("i = %d\n", i);
		     //printf("j = %d\n", j);
	
	     	int adr = i - (adress[j-10]);
	     	
	     		if(j<=10){
	     			off_t status_seek = lseek(fd,SEEK_SET,0);
	     			if (status_seek <= -1) {
	     				perror("lseek()");
	     				return 1;
	     			}
	     		}
	     		else if(j>10){
	     			//printf("adress[j-10] = %d\n", adress[j-10]);
	     			//printf("ADR=i-adress[j-10] %d \n",adr);
	     			//printf("(%d)\n",adr);
	     			
	     			off_t status_seek = lseek(fd,adr,SEEK_SET);
	     			if (status_seek < 0) {
	     				perror("lseek()")  ;
	     				return 1;
	     			}
	     		}
     
	     			ssize_t status_read_return=0;
	     			char buffer_new[1];
	     		     do{
	     		          status_read_return = read(fd,buffer_new,1);
                                   if(status_read_return < 0) {
	     					     perror("read()");
	     				     }				     
	     			     int status_write = write(1, buffer_new, 1);
	     			          if(status_write < 0) {
	     				     	perror("write()");
	     				     }
	     			}while(status_read_return!=0);
	     			
	     	     break;
	     	}//end of if
	     }//end while
	      
	int close_status = close(fd);
	if (close_status == -1)
	{
	  	perror("close()");
	    	return 1;
	}
  	return 0;
}

int main(int argc,char *argv[])
{
     int a;
	 if (argc>1){
	     for (a=1; a<argc; a++ ) {
	          tail(argc,argv[a]);
	     }
	 }
	 else {
	 	//...
	 	size_t n;
	 	char buffer[100];
		do{
			
       	while ((n = read(0, buffer, 1)) > 0)
         {
         	write(1, buffer, n);
		 }
		 printf("%s",buffer);
		
		}while(1);	 	
	 }
	return 0;
}
