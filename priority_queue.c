#include<stdio.h>
#define SIZE 5
#define NIL -999
#define INVALID -9999

int pq[SIZE][SIZE],front[SIZE],rear[SIZE];

void initialize()
{
  int i,j;
  for(i= 0 ; i<SIZE ; i++)
  {
    front[i]=rear[i]=-1;
  }
  for(i=0 ; i<SIZE ; i++)
    for(j=0 ; j<SIZE ; j++)
      pq[i][j]=NIL;
}

void insert()
{
  int num,p;

  printf("Enter the num: ");
  scanf("%d",&num);
  printf("Enter its priority level(b/w 1 and %d): ",SIZE);
  scanf("%d",&p);
  p--;

  if(rear[p]==SIZE-1)  
    printf("%d level of queue full\n",p+1);
  else
  {
    if(front[p]==-1)
      front[p]=0;
    rear[p]++;
    pq[p][rear[p]]=num;
  }
}

int delete()
{
  int p,j;
  for(p=0 ; p<SIZE ; p++)
  {
    if(front[p]!=-1)
    {
      int item=pq[p][front[p]];
      pq[p][front[p]]=NIL;
      front[p]++;
      if(front[p]==rear[p]+1)
        front[p]=rear[p]=-1;
      return item;
    }
  }
  return INVALID;
}

void display()
{
  int i,j;
  printf("p_lvl   priority queue\n");
  printf("-----   -----------------------\n");
  for(i=0 ; i<SIZE ; i++)
  {
    printf("  %d   ",i+1);
    for(j=0 ; j<SIZE ; j++)
    {
      if(pq[i][j]==NIL)
        printf("  -  ");
      else
        printf("%-5d",pq[i][j]);
    }
    printf("\n");
  }
  printf("-----    -------------------\n\n");
}

void main()
{
  int choice,num;
  initialize();
  do{
    printf("Enter your choice: \n1)INSERT\n2)DELETE\n3)DISPLAY\n4)EXIT\n");
    scanf("%d",&choice);
    switch(choice)
    {
      case 1: insert();
              display();
              break;
      case 2: 
              num=delete();
              if(num!=INVALID)
                printf("deleted num is %d\n",num);
              display();
              break;
      case 3: display();
              break;
      case 4:return;
    }
  }while(1);
}