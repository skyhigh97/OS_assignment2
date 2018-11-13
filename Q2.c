#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include</usr/include/semaphore.h>
#include<unistd.h>

unsigned int units_a,units_b,units_c,units_d,k;
//processes currently using each resources
unsigned int cur_usingA=0, cur_usingB=0,cur_usingC=0,cur_usingD=0;
int count[8] ={0};	//count no. of times process has run

const int num_process = 8, num_resources = 4;

double probabilityA = 2/3.0;	//probability of releasing
double probabilityB = 3/4.0;
double probabilityC = 3/5.0;
double probabilityD = 2/3.0;

// semaphores for resources
sem_t sem_resourceA, sem_resourceB, sem_resourceC, sem_resourceD;  
sem_t sem_main; 	// semaphores for processes

void display_resources()
{
	printf("Resources Remaining : ");
	printf("A: %u   B: %u  C: %u  D: %u\n",units_a,units_b,units_c,units_d);
}

void *process1_function(void *num)	//needs resources A,B,C
{
  
	sem_wait(&sem_main);

	if(units_a>=1 && units_b>=1 && units_c>=1)
	{
		//wait for a resource
		sem_wait(&sem_resourceA);
		//update units remaining and process using the unit
		units_a--;	cur_usingA++;

		sem_wait(&sem_resourceB);
		units_b--;	cur_usingB++;

		sem_wait(&sem_resourceC);
		units_c--;	cur_usingC++;

		printf("Process 1 running....\n");
		display_resources();
		printf("Process 1 ending....\n");

		int tmp = rand()%10;
		double probability = tmp/10.0;
		if(probability<=probabilityA)	//relaease A
		{
			sem_post(&sem_resourceA);	units_a++;
		}
		if(probability<=probabilityB)	
		{
			sem_post(&sem_resourceB);	units_b++;
		}
		if(probability<=probabilityC)	
		{
			sem_post(&sem_resourceC);	units_c++;
		}

		count[0]++;
		cur_usingA--;	cur_usingB--;	cur_usingC--;
	}

	else
	{
		printf("Process 1 failed to execute...\n");
	}

	if((cur_usingA==0 && units_a==0) ||(cur_usingB==0 && units_b==0)|| (cur_usingC==0 && units_c==0))
		pthread_exit(NULL);

	if(count[0]<k)
		process1_function(NULL);
}

void *process2_function(void *num)	//needs resources B,C,D
{
  
	sem_wait(&sem_main);

	if(units_b>=1 && units_c>=1 && units_d>=1)
	{
		
		sem_wait(&sem_resourceB);
		units_b--;	cur_usingB++;

		sem_wait(&sem_resourceC);
		units_c--;	cur_usingC++;

		sem_wait(&sem_resourceD);
		units_d--;	cur_usingD++;

		printf("Process 2 running....\n");
		display_resources();
		printf("Process 2 ending....\n");

		int tmp = rand()%10;
		double probability = tmp/10.0;
		if(probability<=probabilityB)	
		{
			sem_post(&sem_resourceB);	units_b++;
		}
		if(probability<=probabilityC)	
		{
			sem_post(&sem_resourceC);	units_c++;
		}
		if(probability<=probabilityD)	
		{
			sem_post(&sem_resourceD);	units_d++;
		}

		count[1]++;
		cur_usingB--;	cur_usingC--;	cur_usingD--;
	}

	else
	{
		printf("Process 2 failed to execute...\n");
	}

	if((cur_usingD==0 && units_d==0) ||(cur_usingB==0 && units_b==0)|| (cur_usingC==0 && units_c==0))
		pthread_exit(NULL);

	if(count[1]<k)
		process2_function(NULL);
}


void *process3_function(void *num)	//needs resources A,C,D
{
  
	sem_wait(&sem_main);

	if(units_a>=1 && units_c>=1 && units_d>=1)
	{
		
		sem_wait(&sem_resourceA);
		units_a--;	cur_usingA++;

		sem_wait(&sem_resourceC);
		units_c--;	cur_usingC++;

		sem_wait(&sem_resourceD);
		units_d--;	cur_usingD++;

		printf("Process 3 running....\n");
		display_resources();
		printf("Process 3 ending....\n");

		int tmp = rand()%10;
		double probability = tmp/10.0;
		if(probability<=probabilityA)	
		{
			sem_post(&sem_resourceA);	units_a++;
		}
		if(probability<=probabilityC)	
		{
			sem_post(&sem_resourceC);	units_c++;
		}
		if(probability<=probabilityD)	
		{
			sem_post(&sem_resourceD);	units_d++;
		}

		count[2]++;
		cur_usingA--;	cur_usingC--;	cur_usingD--;
	}

	else
	{
		printf("Process 3 failed to execute...\n");
	}

	if((cur_usingA==0 && units_a==0) ||(cur_usingD==0 && units_d==0)|| (cur_usingC==0 && units_c==0))
		pthread_exit(NULL);

	if(count[2]<k)
		process3_function(NULL);
}

void *process4_function(void *num)	//needs resources A,B,D
{
  
	sem_wait(&sem_main);

	if(units_a>=1 && units_b>=1 && units_d>=1)
	{
		
		sem_wait(&sem_resourceA);
		units_a--;	cur_usingA++;

		sem_wait(&sem_resourceB);
		units_b--;	cur_usingB++;

		sem_wait(&sem_resourceD);
		units_d--;	cur_usingD++;

		printf("Process 4 running....\n");
		display_resources();
		printf("Process 4 ending....\n");

		int tmp = rand()%10;
		double probability = tmp/10.0;
		if(probability<=probabilityA)	//relaease A
		{
			sem_post(&sem_resourceA);	units_a++;
		}
		if(probability<=probabilityB)	
		{
			sem_post(&sem_resourceB);	units_b++;
		}
		if(probability<=probabilityD)	
		{
			sem_post(&sem_resourceD);	units_d++;
		}

		count[3]++;
		cur_usingA--;	cur_usingB--;	cur_usingD--;
	}

	else
	{
		printf("Process 4 failed to execute...\n");
	}

	if((cur_usingA==0 && units_a==0) ||(cur_usingB==0 && units_b==0)|| (cur_usingD==0 && units_d==0))
		pthread_exit(NULL);

	if(count[3]<k)
		process4_function(NULL);
}

void *process5_function(void *num)	//needs resources A
{
  
	sem_wait(&sem_main);

	if(units_a>=1)
	{
		
		sem_wait(&sem_resourceA);
		units_a--;	cur_usingA++;

		printf("Process 5 running....\n");
		display_resources();
		printf("Process 5 ending....\n");

		int tmp = rand()%10;
		double probability = tmp/10.0;
		if(probability<=probabilityA)	//relaease A
		{
			sem_post(&sem_resourceA);	units_a++;
		}
		
		count[4]++;
		cur_usingA--;
	}

	else
	{
		printf("Process 5 failed to execute...\n");
	}

	if(cur_usingA==0 && units_a==0)
		pthread_exit(NULL);

	if(count[4]<k)
		process5_function(NULL);
}

void *process6_function(void *num)	//needs resources B
{
  
	sem_wait(&sem_main);

	if(units_b>=1)
	{
		
		sem_wait(&sem_resourceB);
		units_b--;	cur_usingB++;

		printf("Process 6 running....\n");
		display_resources();
		printf("Process 6 ending....\n");

		int tmp = rand()%10;
		double probability = tmp/10.0;
		if(probability<=probabilityB)	
		{
			sem_post(&sem_resourceB);	units_b++;
		}
		
		count[5]++;
		cur_usingB--;
	}

	else
	{
		printf("Process 6 failed to execute...\n");
	}

	if(cur_usingB==0 && units_b==0)
		pthread_exit(NULL);

	if(count[5]<k)
		process6_function(NULL);
}

void *process7_function(void *num)	//needs resources C
{
  
	sem_wait(&sem_main);

	if(units_c>=1)
	{
		
		sem_wait(&sem_resourceC);
		units_c--;	cur_usingC++;

		printf("Process 7 running....\n");
		display_resources();
		printf("Process 7 ending....\n");

		int tmp = rand()%10;
		double probability = tmp/10.0;
		if(probability<=probabilityC)	
		{
			sem_post(&sem_resourceC);	units_c++;
		}
		
		count[6]++;
		cur_usingC--;
	}

	else
	{
		printf("Process 7 failed to execute...\n");
	}

	if(cur_usingC==0 && units_c==0)
		pthread_exit(NULL);

	if(count[6]<k)
		process7_function(NULL);
}

void *process8_function(void *num)	//needs resources D
{
  
	sem_wait(&sem_main);

	if(units_d>=1)
	{
		
		sem_wait(&sem_resourceD);
		units_d--;	cur_usingD++;

		printf("Process 8 running....\n");
		display_resources();
		printf("Process 8 ending....\n");

		int tmp = rand()%10;
		double probability = tmp/10.0;
		if(probability<=probabilityD)	
		{
			sem_post(&sem_resourceD);	units_d++;
		}
		
		count[6]++;
		cur_usingD--;
	}

	else
	{
		printf("Process 8 failed to execute...\n");
	}

	if(cur_usingD==0 && units_d==0)
		pthread_exit(NULL);


	if(count[7]<k)
		process8_function(NULL);
}

int main()
{
  	int i,j;
	srand(time(0)) ;	//create seed
	printf("Enter k : ");
	scanf("%u",&k);

	pthread_t tID[k][8];	//create threads

	printf("Enter units of A : ");	scanf("%u",&units_a);
	printf("Enter units of B : ");	scanf("%u",&units_b);
	printf("Enter units of C : ");	scanf("%u",&units_c);
	printf("Enter units of D : ");	scanf("%u",&units_d);

	//Semaphores for resources
	sem_init(&sem_resourceA, 0, units_a);
	sem_init(&sem_resourceB, 0, units_b);
	sem_init(&sem_resourceC, 0, units_c);
	sem_init(&sem_resourceD, 0, units_d);

	//Semaphores for processes
	sem_init(&sem_main, 0, 1);

	

	//create threads and assign them functions
	for(i=0;i<k;i++)
	{
		pthread_create(&tID[i][0],NULL,process1_function,&i);
		pthread_create(&tID[i][1],NULL,process2_function,&i);
		pthread_create(&tID[i][2],NULL,process3_function,&i);
		pthread_create(&tID[i][3],NULL,process4_function,&i);
		pthread_create(&tID[i][4],NULL,process5_function,&i);
		pthread_create(&tID[i][5],NULL,process6_function,&i);
		pthread_create(&tID[i][6],NULL,process7_function,&i);
		pthread_create(&tID[i][7],NULL,process8_function,&i);
	}
	
	//join all threads
	for(i=0;i<k;i++)
	{
		for(j=0; j<num_process; j++)
		{
			pthread_join(tID[i][j],NULL);
		}

	}

	return 0;
}