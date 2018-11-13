#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include</usr/include/semaphore.h>
#include<unistd.h>

unsigned int units_a,units_b,units_c,units_d,k;
int count1,count2,count3,count4,count5,count6,count7,count8;
const int num_process = 8, num_resources = 4;

sem_t sem_resource[4];  // semaphores for resources
sem_t sem_process[8]; 	// semaphores for processes

void display_resources()
{
	printf("Resources Remaining : ");
	printf("A: %u   B: %u  C: %u  D: %u\n",units_a,units_b,units_c,units_d);
}

void *process1_function(void *num)	//needs resources A,B,C
{
  
	int *i = num;
	int number1,number2,number3;

	sem_wait(&sem_process[0]);
	int resource1_collected, resource2_collected, resource3_collected;
	resource1_collected=0;
	resource2_collected=0;
	resource3_collected=0;

	printf("Process 1 is waiting to enter critical section\n");
	sem_wait(&sem_resource[0]);
	//printf("Process 1 collected resource A\n");

	sem_wait(&sem_resource[1]);
	//printf("Process 1 collected resource B\n");

	sem_wait(&sem_resource[2]);
	//printf("Process 1 collected resource C\n");
	
	printf("Process 1 is running...\n");
	sem_post(&sem_process[0]);

	display_resources();

	while(resource1_collected==0)
	{
		number1 = rand( ) % 1000 + 1;
		if(number1<=666)
		{
			sem_post(&sem_resource[0]);
			//printf("Process 1 has released A\n");
			resource1_collected=1;
		}
	}

	while(resource2_collected==0)
	{
		number2 = rand( ) % 1000 + 1;
		if(number2<=750)
		{
			sem_post(&sem_resource[1]);
			//printf("Process 1 has released B\n");
			resource2_collected=1;
		}
	}

	while(resource3_collected==0)
	{
		number3 =  rand() % 1000 + 1;
		if(number3<=600)
		{
			sem_post(&sem_resource[2]);
			//printf("Process 1 has released C\n");
			resource3_collected=1;
		}
	}


	count1++;
		printf("Process 1 has occured %d times till now. \n",count1);
  
}

void *process2_function(void *num)	//needs resources B,C,D
{
  
	int *i = num;
	int number1,number2,number3;

	sem_wait(&sem_process[1]);
	int resource2_collected, resource3_collected, resource4_collected;
	resource2_collected=0;
	resource3_collected=0;
	resource4_collected=0;

	//printf("Process 2 is waiting to enter critical section\n");
	sem_wait(&sem_resource[1]);
	//printf("Process 2 collected B\n");

	sem_wait(&sem_resource[2]);
	//printf("Process 2 collected C\n");

	sem_wait(&sem_resource[3]);
	//printf("Process 2 collected D\n");

	printf("Process 2 is running...\n");
	display_resources();
	sem_post(&sem_process[1]);

	while(resource2_collected==0)
	{
		number1 = rand( ) % 1000 + 1;
		if(number2<=750)
		{
			sem_post(&sem_resource[1]);
			resource2_collected=1;
			//printf("Process 2 has released B\n");
		}
	}

	while(resource3_collected==0)
	{
		number2 =  rand( ) % 1000 + 1;
		if(number2<=600)
		{
			sem_post(&sem_resource[2]);
			resource3_collected=1;
			//printf("Process 2 has released C\n");
		}
	}

	while(resource4_collected==0)
	{
		number3 =  rand( ) % 1000 + 1;
		if(number3<=666)
		{
			sem_post(&sem_resource[3]);
			resource4_collected=1;
			//printf("Process 2 has released D");
		}
	}


	count2++;
	printf("Process 2 has occured %d times.\n",count2);

}

void *process3_function(void *num)	//needs resources A,C,D
{

	int *i = num;
	int number1,number2,number3;
	sem_wait(&sem_process[2]);
	int resource1_collected, resource3_collected, resource4_collected;
	resource1_collected=0;
	resource3_collected=0;
	resource4_collected=0;

	//printf("Process 3 is waiting to enter critical section\n");
	sem_wait(&sem_resource[0]);
	//printf("Process 3 collected A\n");

	sem_wait(&sem_resource[2]);
	//printf("Process 3 collected C\n");

	sem_wait(&sem_resource[3]);
	//printf("Process 3 collected D\n");

	printf("Process 3 is running...\n");
	display_resources();
	sem_post(&sem_process[2]);

	while(resource1_collected==0)
	{
		number1 = rand( ) % 1000 + 1;
		if(number2<=666)
		{
			sem_post(&sem_resource[0]);
			resource1_collected=1;
			//printf("Process 3 has released A\n");
		}
	}

	while(resource3_collected==0)
	{
		number2 =  rand( ) % 1000 + 1;
		if(number2<=600)
		{
			sem_post(&sem_resource[2]);
			resource3_collected=1;
			//printf("Process 3 has released C\n");
		}
	}

	while(resource4_collected==0)
	{
		number3 =  rand( ) % 1000 + 1;
		if(number3<=666)
		{
			sem_post(&sem_resource[3]);
			resource4_collected=1;
			//printf("Process 3 has released D\n");
		}
	}


	count3++;
	printf("Process 3 has occured %d times.\n",count3);
  
}

void *process4_function(void *num)	//needs resources A,B,D
{
  
	int *i = num;
	int number1, number2,number3;

	sem_wait(&sem_process[3]);
	int resource1_collected, resource2_collected, resource4_collected;
	resource1_collected=0;
	resource2_collected=0;
	resource4_collected=0;

	//printf("Process 4 is waiting to enter critical section\n");
	sem_wait(&sem_resource[0]);
	//printf("Process 4 collected A\n");

	sem_wait(&sem_resource[1]);
	//printf("Process 4 collected B\n");

	sem_wait(&sem_resource[3]);
	//printf("Process 4 collected D\n");

	printf("Process 4 is running...\n");
	display_resources();
	sem_post(&sem_process[3]);

	while(resource1_collected==0)
	{
		number1 = rand( ) % 1000 + 1;
		if(number2<=666)
		{
			sem_post(&sem_resource[0]);
			resource1_collected=1;
			//printf("Process 4 has released A\n");
		}
	}

	while(resource2_collected==0)
	{
		number2 =  rand( ) % 1000 + 1;
		if(number2<=750)
		{
			sem_post(&sem_resource[1]);
			resource2_collected=1;
			//printf("Process 4 has released B\n");
		}
	}

	while(resource4_collected==0)
	{
		number3 =  rand( ) % 1000 + 1;
		if(number3<=666)
		{
			sem_post(&sem_resource[3]);
			resource4_collected=1;
			//printf("Process 4 has released D\n");
		}
	}

	count4++;
	printf("Process 4 has occured %d times.\n",count4);

}

void *process5_function(void *num)	//needs resources A
{
  
	int *i = num;
	int number1;

	sem_wait(&sem_process[4]);
	int resource1_collected;
	resource1_collected=0;

	//printf("Process 5 is waiting to enter critical section\n");
	sem_wait(&sem_resource[0]);
	//printf("Process 5 collected A\n");

	printf("Process 5 is running...\n");
	display_resources();
	sem_post(&sem_process[4]);

	while(resource1_collected==0)
	{
		number1 = rand( ) % 1000 + 1;
		if(number1<=666)
		{
			sem_post(&sem_resource[0]);
			resource1_collected=1;
			//printf("Process 5 has released A\n");
		}
	}


	count5++;
	printf("Process 5 has occured %d times.\n",count5);
  
}

void *process6_function(void *num)	//needs resources B
{
  
	int *i = num;
	int number1;

	sem_wait(&sem_process[5]);
	int resource2_collected;
	resource2_collected=0;

	//printf("Process 6 is waiting to enter critical section\n");
	sem_wait(&sem_resource[1]);
	//printf("Process 6 collected B\n");

	printf("Process 6 is running...\n");
	display_resources();
	sem_post(&sem_process[5]);

	while(resource2_collected==0)
	{
		number1 =  rand( ) % 1000 + 1;
		if(number1<=750)
		{
			sem_post(&sem_resource[1]);
			resource2_collected=1;
			//printf("Process 4 has released B\n");
		}
	}


	count6++;
	printf("Process 6 has occured %d times.\n",count6);
}

void *process7_function(void *num)	//needs resources C
{
	int *i = num;
	int number1;


	sem_wait(&sem_process[6]);
	int resource3_collected;
	resource3_collected=0;

	//printf("Process 7 is waiting to enter critical section\n");
	sem_wait(&sem_resource[2]);
	//printf("Process 7 collected C\n");

	printf("Process 7 is running...\n");
	display_resources();
	sem_post(&sem_process[6]);



	while(resource3_collected==0)
	{
		number1 =  rand( ) % 1000 + 1;
		if(number1<=600)
		{
			sem_post(&sem_resource[2]);
			resource3_collected=1;
			//printf("Process 7 has released C\n");
		}
	}


	count7++;
	printf("Process 7 has occured %d times.\n",count7);

}

void *process8_function(void *num)	//needs resources D
{

	int *i = num;
	int number1;

	sem_wait(&sem_process[7]);
	int resource4_collected;
	resource4_collected=0;

	//printf("Process 8 is waiting to enter critical section\n");
	sem_wait(&sem_resource[3]);
	//printf("Process 8 collected D\n");


	printf("Process 8 is running...\n");
	display_resources();
	sem_post(&sem_process[7]);

	while(resource4_collected==0)
	{
		number1 =  rand( ) % 1000 + 1;
		if(number1<=666)
		{
			sem_post(&sem_resource[3]);
			resource4_collected=1;
			//printf("Process 8 has released D\n");
		}
	}


	count8++;
	printf("Process 8 has occured %d times.\n",count8);

}


int main()
{
  	int i,j;
	srand(time(0)) ;	//create seed
	printf("Enter k : ");
	scanf("%u",&k);

	pthread_t thread_id[k][8];	//create threads

	printf("Enter units of A : ");	scanf("%u",&units_a);
	printf("Enter units of B : ");	scanf("%u",&units_b);
	printf("Enter units of C : ");	scanf("%u",&units_c);
	printf("Enter units of D : ");	scanf("%u",&units_d);

	//Semaphores for resources
	sem_init(&sem_resource[0], 0, units_a);
	sem_init(&sem_resource[1], 0, units_b);
	sem_init(&sem_resource[2], 0, units_c);
	sem_init(&sem_resource[3], 0, units_d);

	//Semaphores for processes
	for(i=0; i<num_process; i++)
		sem_init(&sem_process[i], 0, 1);

	//create threads and assign them functions
	for(i=0;i<k;i++)
	{
		pthread_create(&thread_id[i][0],NULL,process1_function,&i);
		pthread_create(&thread_id[i][1],NULL,process2_function,&i);
		pthread_create(&thread_id[i][2],NULL,process3_function,&i);
		pthread_create(&thread_id[i][3],NULL,process4_function,&i);
		pthread_create(&thread_id[i][4],NULL,process5_function,&i);
		pthread_create(&thread_id[i][5],NULL,process6_function,&i);
		pthread_create(&thread_id[i][6],NULL,process7_function,&i);
		pthread_create(&thread_id[i][7],NULL,process8_function,&i);
	}
	
	//join all threads
	for(i=0;i<k;i++)
	{
		for(j=0; j<num_process; j++)
		{
			pthread_join(thread_id[i][j],NULL);
		}

	}

	return 0;
}