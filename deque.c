#include<stdio.h>
#define SIZE 10
#define INVALID -9999

int DQ[10],front=-1,rear=-1;

void insertRear(int item)
{
  if(rear==SIZE-1)
  {
    printf("DEQUE full at rear\n");
    return;
  }
  else
  {
    if(front==-1)
      front=0;
    rear++;
    DQ[rear]=item;
  }
}
int deleteFront()
{
  if(front==-1)
  {
    printf("DEQUE Empty..\n");
    return INVALID;
  }
  else
  {
    int item=DQ[front];
    front++;
    if(front==rear+1)
      front=rear=-1;
    return item;
  }
}
void insertFront(int item)
{
  if(front==0)
  {
    printf("DEQUE full at front\n");
    return;
  }
  else
  {
    if(rear==-1)
      rear=front=0;
    else
      front--;
    DQ[front]=item;
  }
}
int deleteRear()
{
  if(rear==-1)
  {
    printf("DQ Empty..\n");
    return INVALID;
  }
  else
  {
    int item=DQ[rear];
    rear--;
    if(rear==front-1)
      rear=front=-1;
    return item;
  }
}
void display()
{
  int i;
  printf("DEQUE:\n");
  if(front==-1)
    printf("DEQUE empty\n");
  else
  {
    for(i=front ; i<=rear ; i++)
       printf("%-5d",DQ[i]);
    printf("\n");
  }
}
void main()
{
  int n,num,i;
  char option;

  do
  {
    printf("How many elements to be added: ");
    scanf("%d",&n);
    printf("Do you want to insert at front or rear(f/r)? ");
    scanf(" %c",&option);
    printf("Enter %d numbers to be inserted at %c: ",n,option);
    if(option=='f'||option=='F')
      for(i=0 ; i<n ; i++)
      {
        scanf("%d",&num);
        insertFront(num);
      }
    else if(option=='r'||option=='R')
          {
            for(i=0 ; i<n ; i++)
            {
              scanf("%d",&num);
              insertRear(num);
            }
          }
    display();

    printf("How many elements to be deleted? ");
    scanf("%d",&n);
    printf("Do you want to delete from front or rear(f/r)? ");
    scanf(" %c",&option);
    if(option=='f'||option=='F')
      for(i=0 ; i<n ; i++)
      {
          num=deleteFront();
          if(num!=INVALID)
            printf("%d th dequeued element: %d\n",i+1,num);
      }
      else if(option=='r'||option=='R')
        for(i=0 ; i<n ; i++)
        {
          num=deleteRear();
          if(num!=INVALID)
            printf("%d th dequeued element: %d\n",i+1,num);
        }

    display();

    printf("Do you want to repeat(y/n)? ");
    scanf(" %c",&option);
  }
  while(option=='y'||option=='Y');
  
}