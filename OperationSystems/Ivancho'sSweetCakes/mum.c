//----------------------------------------
// NAME: Bojidar Zahov
// CLASS: 11 Б
// NUMBER: 4
// PROBLEM: #4
// FILE NAME: mom.c
// FILE PURPOSE:
// Ivancho Starving
//-----------------------------------------
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_THREADS 2
#define MAX_NUMBER_OF_COOKIES 100
#define VARIABLE_LIMIT 5
#define SINGLE_BEAKING 1

int madeCookies = 0;
int onTable[VARIABLE_LIMIT];
int cookiesOnTable;

pthread_mutex_t count_mutex;
pthread_mutex_t onTable_mutex;
pthread_cond_t count_threshold_cv;
//pthread_cond_t mom_wait_cv;
//int current;

void* MomCooking(void *id)
//-----------------------------------------------------
// FUNCTION: momCooking()
// Compute every part of working "Day" of mom
// PARAMETERS:
// NONE
//-----------------------------------------------------
{	
    int i,current;
	pthread_mutex_lock(&count_mutex);
	for (i=0; madeCookies < MAX_NUMBER_OF_COOKIES; i++) {
		    
	    current = i % VARIABLE_LIMIT;
	  
	    printf("Mom checks if there is a cake on place %d on the table. -> %d \n", current + 1, onTable[current] == 1);
	    pthread_mutex_lock(&onTable_mutex);
	    if( onTable[current] == 0){ 
	   		printf("No, here haven't\nMom starts baking a cake on %d\n",current);
	   	 	madeCookies++;
	   	 	cookiesOnTable++;
	   	 	onTable[current] = 1;
	   	 	
	   	 	pthread_mutex_unlock(&onTable_mutex);
	   	 	pthread_mutex_unlock(&count_mutex);
	    	
	    	sleep(2); /// <------------------2-------------------------------------
	    }else {
	    	//printf("!!!!!!!!!!!!!\n");
	    	pthread_mutex_unlock(&count_mutex);
	    	pthread_cond_signal(&count_threshold_cv);
	    	//pthread_cond_signal(&count_threshold_cv);
	    	//printf("Mom signal Ivancho to eat");
	    }
	     if (current == 0 && i != 0)
	     {
	        //pthread_cond_signal(&count_threshold_cv);
	       // printf("Mom signal Ivancho to eat\n");
	        printf("Mom Watching TV %d -> %d Table Limit reached.\n", i, current);
	    	//pthread_cond_wait(&mom_wait_cv,&count_mutex);    
	    }
	    printf("Mom unlocking mutex, count = %d -> %d, \n", i , current);
		    		    	    
	   // sleep(1);
	}
	pthread_exit(NULL);
}

void* Ivancho(void *id)
//-----------------------------------------------------
// FUNCTION: Ivancho()
// Ivancho day
// PARAMETERS:
// NONE
//-----------------------------------------------------
{	int i ;
	int currenta = 1;
	int IsTableEmpty;
    while(1){
		pthread_mutex_lock(&count_mutex);
		if (madeCookies == MAX_NUMBER_OF_COOKIES)
		{
			break;
		}
		pthread_mutex_unlock(&count_mutex);
			pthread_mutex_lock(&onTable_mutex);
		for(i = 0; i < VARIABLE_LIMIT; i++) {
		    //printf("!@#!@#@!##!@#@!#@!##@\n");
		    pthread_cond_wait(&count_threshold_cv, &onTable_mutex);
		    printf(">>Ivancho checks if there is a cake on place %d on the table %d.\n", currenta , onTable[currenta]);
		    currenta = i % VARIABLE_LIMIT;
		    
		    if (onTable[0] == 0 && onTable[1] == 0 && onTable[2] == 0 && onTable[3] == 0 && onTable[4] == 0)//that is bad
		    {
		    	printf(">> Ivancho going to training");
		    	sleep(2);
		    }
		    if (onTable[currenta] == 1) // have cookie
		    {  	           		
		    	onTable[currenta] = 0;
		    	printf(">>Ivancho Eating cookie now on place-%d\n", currenta);
				
				
		   	 	cookiesOnTable--;
		   	 	pthread_mutex_unlock(&onTable_mutex);
				
				sleep(1); // <----------1---------
			}
			
			
			pthread_mutex_unlock(&onTable_mutex);
			pthread_mutex_unlock(&count_mutex);
		
		}
	}
	pthread_exit(NULL);
}
int main (int argc, char *argv[])
{
    int i;
    
    pthread_t mom;
    pthread_t son;
    pthread_attr_t attr;
    
    pthread_mutex_init(&count_mutex, NULL);
    pthread_cond_init (&count_threshold_cv, NULL);

    pthread_attr_init(&attr);
   
    
    pthread_create(&mom, &attr, Ivancho,NULL);
    pthread_create(&son, &attr, MomCooking,NULL);
   
   
    pthread_join(mom, NULL);
    pthread_join(son, NULL);
    
    printf ("Done.\n");
    
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&count_mutex);
    pthread_cond_destroy(&count_threshold_cv);
    
    return 0;
}
