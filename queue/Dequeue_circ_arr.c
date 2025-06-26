#include<stdio.h>
#define SIZE 10
#define INVALID -9999

int Q[SIZE],f=-1,r=-1;

void insertRear(int item)
{
  if(f==(r+1)%SIZE){
    printf("dequeue full\n");
    return;
  }
  else if(f==-1)
          f=r=0;
        else if(r==SIZE-1)
                r=0;
              else
                r=r+1;
    Q[r]=item;
}

void insertFront(int item)
{
  if(f==(r+1)%SIZE)
  {
    printf("queue full\n");
    return;
  }
  if(f==-1)
    f=r=0;
  else if(f==0)
          f=SIZE-1;
        else
          f=f-1;
  Q[f]=item;
}

int deleteFront()
{
  if(f==-1)
    printf("queue empty\n");
  else 
  {
    int item=Q[f];
    if(f==SIZE-1)
      f=0;
    else
      f=f+1;
    if(f==(r+1)%SIZE)
      f=r=-1;
    return item;
  }
}

int deleteRear()
{
  if(f==-1)
    printf("queue empty\n");
  else
  {
    int item=Q[r];
    if(r==0)
      r=SIZE-1;
    else
      r=r-1;
    if(f==(r+1)%SIZE)
      f=r=-1;
    return item;
  }
}

void display()
{
  int i;
  if(f==-1){
    printf("deque empty\n");
    return;
  }
  printf("Front:   ");
  for(i=f ; i!=r ; i=(i+1)%SIZE)
    printf("%-4d",Q[i]);
  printf("%-4d:rear\n\n",Q[i]);
}

void main()
{
  int choice,item;

  do{
      printf("Enter your choice: \n1)InsertRear\n2)InsertFront\n3)DleteFront\n4)DeleteRear\n5)Display\n6)Exit\n");
      scanf("%d",&choice);

      switch(choice)
      {
        case 1: printf("Enter the item to be insreted: ");
                scanf("%d",&item);
                insertRear(item);
                display();
                break;
        case 2: printf("Enter the item to be insreted: ");
                scanf("%d",&item);
                insertFront(item);
                display();
                break;
        case 3: item=deleteFront();
                if(item!=INVALID)
                  printf("dequeued item is %d\n",item);
                display();
                break;
        case 4: item=deleteRear();
                if(item!=INVALID)
                  printf("dequeued item is %d\n",item);
                display();
                break;
      }
  }while(1);
}