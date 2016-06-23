//----------------------------------------
// NAME: Bojidar Zahov
// CLASS: 11 Б
// NUMBER: 4
// PROBLEM: #3
// FILE NAME: starcraft3.c
// FILE PURPOSE:
// Prototupe of StarCraft3
//-----------------------------------------

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t commandCentersList[200];
pthread_t workersList[200];

pthread_mutex_t mapRss_lock;
pthread_mutex_t myRss_lock;

int mapRss = 5000;
int myRss = 0;

int myCommandCenters = 0;
int myWorkers = 0;
int myTroops = 0;

//-----------------------------------------------------
// FUNCTION: workingProcess()
// Compute every part of working "Day" of employ
// PARAMETERS:
// NONE
//-----------------------------------------------------

void* workingProcess(void* a){
	int workerId = (int64_t)a;
	int trylock;	
	while(101)
	{
	int i;
	
		printf("SCV %d is mining\n",workerId +1);
		pthread_mutex_lock(&mapRss_lock);
		if(mapRss < 8)
		{
			pthread_mutex_unlock(&mapRss_lock);		
			printf("Start Map Resources: %d\n", 5000);
			printf("Your Resources: %d\n", myRss);
			int spent = 50 * (myTroops + myWorkers-5) - 400 * (myCommandCenters -1);
			printf("Spent Resources: %d\n", spent);
			printf("On Map more: %d\n",mapRss);
			return NULL;
			
		}
		mapRss = mapRss - 8;
		pthread_mutex_unlock(&mapRss_lock);
		printf("SCV %d is transporting minerals\n",workerId +1);
		sleep(2);
		while(trylock){
			for(i=0; i<myCommandCenters; i++){
				if (pthread_mutex_trylock(&commandCentersList[i])==0){
					
					pthread_mutex_lock(&myRss_lock);
					
					myRss += 8;
					printf("SCV %d delivered minerals to Command Center %d\n",
						workerId+1, i+1);
					pthread_mutex_unlock(&myRss_lock);
					pthread_mutex_unlock(&commandCentersList[i]);
					break;
				}else trylock = 1;
			}
			sleep(1);
		}
	}
}
//-----------------------------------------------------
// FUNCTION: buildCommandCenter()
// Everything for building a new Command Center
// PARAMETERS:
// NONE
//-----------------------------------------------------

void buildCommandCenter(){
	if(myCommandCenters != 0)  // Build free first command center
	{
		pthread_mutex_lock(&myRss_lock);
		if(myRss<400 ){
			printf("Not enough minerals.\n");
			pthread_mutex_unlock(&myRss_lock);
			return;
		}
		myRss -= 400;
		pthread_mutex_unlock(&myRss_lock);
		sleep(2);
	}
	
	if(pthread_mutex_init(&commandCentersList[myCommandCenters], NULL) != 0)
	{
		printf("Error with building of new CommandCenter");
		exit(1);
	}
	printf("Command Center %d created\n", ++myCommandCenters);
}

//-----------------------------------------------------
// FUNCTION: learnNewWorker()
// Everything for learning a new Command Center
// PARAMETERS:
// NONE
//-----------------------------------------------------

void learnNewWorker(){
	if(myWorkers > 4)  // Learn 1-5 free workers
	{
		pthread_mutex_lock(&myRss_lock);
		if(myRss<50){
			printf("Not enough minerals.\n");
			pthread_mutex_unlock(&myRss_lock);
			return;
		}
		if(myWorkers > 200){
			
			printf("You can't learn more Workers.\n");
			return;
		}
		myRss -= 50;
		pthread_mutex_unlock(&myRss_lock);
		sleep(1);
	}
	
	if(pthread_create(&workersList[myWorkers], NULL ,workingProcess,(void*)(int64_t)myWorkers) != 0)
	{
		printf("Error with learning new Workers\n");
		exit(1);
	}
	printf("SCV %d good to go, sir\n", ++myWorkers);
}

//-----------------------------------------------------
// FUNCTION: TrainTroop()
// Everything for training a new Troop
// PARAMETERS:
// NONE
//-----------------------------------------------------
void TrainTroop(){
	pthread_mutex_lock(&myRss_lock);
	if(myRss<50){
		printf("Not enough minerals.\n");
		pthread_mutex_unlock(&myRss_lock);
		return;
	}
	myRss -= 50;
	pthread_mutex_unlock(&myRss_lock);
	sleep(1);
	printf("You wanna piece of me, boy? I am %d \n troop", ++myTroops);
	if (myTroops == 20)
	{
		printf("Start Map Resources: %d\n", 5000);
		printf("Your Resources: %d\n", myRss);
		int spent = 50 * (myTroops + myWorkers-5) - 400 * (myCommandCenters -1);
		printf("Spent Resources: %d\n", spent);
		printf("On Map more%d\n",mapRss);
		printf("You win ;)\n");
		exit(0);
	}
}


//-----------------------------------------------------
// FUNCTION: main()
// Sequence of functions of Game
// PARAMETERS:
// NONE
//-----------------------------------------------------
int main (int argc, char *argv[])
{
	int i;
	if (pthread_mutex_init(&myRss_lock,NULL) != 0)
	{
		printf("Error with Mutex_Init");	
		exit(1);
	}
	
	if (pthread_mutex_init(&mapRss_lock,NULL) != 0)
	{
		printf("Error with Mutex_Init");
		exit(1);
	}
	buildCommandCenter(); 
	
	for (i = 0; i < 5; i += 1)
	{
		learnNewWorker(); 
	}
	
	while (1010)
	{
		char input;
		input = getchar();
		switch(input)
		{
			case 'c':
				buildCommandCenter();
				break;
			case 'm':
				TrainTroop();
				break;
			case 's':
				learnNewWorker();
				break;
			case '\n':
			/*printf(" expecting 'c' , 'm' or 's'\n ");*/
				break;
			default: 
				printf("X>%c<X is not right command!!\n",input);
		}
	}
	return 0;
}
