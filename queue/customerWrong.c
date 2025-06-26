#include<stdio.h>
#define SIZE 5
//#define INVALID -9999
int front=-1,rear=-1;

struct customer
{
	char name[30];
	int servtime;
}INVALID;

struct customer cq[10];

void enqueue(struct customer item)
{
	if(front==(rear+1)%SIZE)
		printf("circular queue full\n");
	else
	{
		if(front==-1)
			front=0;
		rear=(rear+1)%SIZE;
		cq[rear]=item;
	}
}

struct customer dequeue()
{
	struct customer item;
	if(front==-1)
	{
		printf("queue empty\n");
		INVALID.servtime=-1;
		return INVALID;
	}
	item=cq[front];
	front=(front+1)%SIZE;
	if(front==(rear+1)%SIZE)
		front=rear=-1;
	return item;
}

void display()
{
	int i;
	printf("CIRC QUEUE\n");
	printf("FRONT: \n");
	if(front<=rear)
	{
		for(i=front ; i<=rear ; i++)
		{
			printf("\nCustomer %d:\n",i+1);
			printf("name: %s\n",cq[i].name);
			printf("service time: %d minutes\n",cq[i].servtime);
		}
	}
	else
	{
		int count =1;
		for(i=front ; i<SIZE ; i++)
		{
			printf("\nCustomer %d:\n",count);
			printf("name: %s\n",cq[i].name);
			printf("service time: %d minutes\n",cq[i].servtime);
			count++;
		}
		for(i=0 ; i<=rear ; i++)
		{
			printf("\nCustomer %d:\n",count);
			printf("name: %s\n",cq[i].name);
			printf("service time: %d minutes\n",cq[i].servtime);
			count++;
		}
	}
	printf("\nREAR\n");
}

void printWaitingTime(int index)
{
	int i;
	int wait_time=0;
	for(i=front ; i!=index-1 ; i=(i+1)%SIZE)
		wait_time+=cq[i].servtime;
	printf("The waiting time of customer at index %d is %d minutes\n",index,wait_time);

}

void main()
{
	int choice,index;
	struct customer c;
	do
	{
		printf("Enter your choice:\n1)ENQUEUE\n2)DEQUEUE\n3)DISPLAY\n4)WAITING TIME\n4)EXIT\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			      printf("Enter the name of customer to be enqueued: ");
						scanf(" %[^\n]",c.name);
						printf("Enter his/her service time: ");
						scanf("%d",&c.servtime);
						enqueue(c);
						break;
			case 2:c=dequeue();
						if(c.servtime!=-1)
							printf("name of customer dequeued: %s\n",c.name);
						break;
			case 3:display();
							break;
			case 4:printf("Enter the index of the person whose waiting time is to be calculated: ");
						scanf("%d",&index);
						printWaitingTime(index);
						break;
			case 5:return ;
		}
	}while(1);
}